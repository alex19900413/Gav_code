#include<stdio.h>

/*******************************************************************************
 FileName: AGVmotion.c
 Platform: DSP 32-bit TMS320C6713
 Version: 1.0
 Date:  2017-7-25
 Description: AGV MOtion Function
 History:
 <author>   <time>   <version >  <desc>
 wlqunr  2017-7-25  1.00
 ********************************************************************************/
 /*******************************************************************************
  * 1.绝对坐标以世界坐标系为参考，相对坐标模式以小车坐标系为参考
  * 2.公式分析时，小车坐标、4个轮毂坐标的X轴正方向统一水平向右
  ********************************************************************************/
#include <math.h>
#include "MotionDataType.h"
#include "vmarith.h"
#include "MotionAGV.h"

//extern INT16U PulseTemp[4]; // 给FPGA的PWM中间参数：  direction=0 (HSB=0) and period(50us by 0.1us*500 )
//extern INT16U WidthTemp[4]; // 给FPGA的PWM中间参数：  pulse width (8us by 0.1us*80 ) 可知占空比默认为 80/500=16%
INT16U PulseTemp[4]; // 给FPGA的PWM中间参数：  direction=0 (HSB=0) and period(50us by 0.1us*500 )
INT16U WidthTemp[4]; // 给FPGA的PWM中间参数：  pulse width (8us by 0.1us*80 ) 可知占空比默认为 80/500=16%


//++++++++++++++++++++++++++++++++++++++ 车速》轮速接口 ++++++++++++++++++++++++++++++++++++++++++
double Angle2rad(double angleTemp) {
	//Fun:  角度值转换为弧度制，供车速转换函数调用
	//INput： 角度：0 - 360.00°
	//Output: 弧度：0 - 2*pi
	double radTemp = 0;
	radTemp = (angleTemp / 180) * Pi;
	return radTemp;
}


AgvWwheel Vcar2Wwheel_Mecanum(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		麦克纳姆轮*4：车速》轮速
	//Mode:		全向
	//INput:	AgvVcar0车速参数、AgvMotionPara0车型参数
	//Output:	AgvWwheel0轮速参数
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double R[4][4];
	double W[4][1];
	double T[4][4];
	V_car2W_wheel(AgvMotionPara0.wheelRadius, AgvMotionPara0.wheelBaseW, AgvMotionPara0.wheelBaseL, T);
	if (AgvVcar0.OrderType == 1) {
		//绝对直角
		V[0][0] = AgvVcar0.Ord1.line_Vx;
		V[1][0] = AgvVcar0.Ord1.line_Vy;
		V[2][0] = AgvVcar0.Ord1.arc_Wz;
		V[3][0] = 1;						
		CoordConv(AgvVcar0.Ord1.Rx, 0, 0, R);
		matmul44x41(R, V, v);
		matmul44x41(T, v, W);
	}
	else if (AgvVcar0.OrderType == 2) {
		//相对直角
		v[0][0] = AgvVcar0.Ord2.line_vx;
		v[1][0] = AgvVcar0.Ord2.line_vy;
		v[2][0] = AgvVcar0.Ord2.arc_wz;
		v[3][0] = 1;						
		matmul44x41(T, v, W);
	}
	else if (AgvVcar0.OrderType == 3) {
		//绝对极坐标系
		V[0][0] = AgvVcar0.Ord3.line_V * cos(AgvVcar0.Ord3.line_Angle);
		V[1][0] = AgvVcar0.Ord3.line_V * sin(AgvVcar0.Ord3.line_Angle);
		V[2][0] = 0;
		V[3][0] = 1;						
		CoordConv(AgvVcar0.Ord3.Rx, 0, 0, R);
		matmul44x41(R, V, v);
		matmul44x41(T, v, W);
	}
	else if (AgvVcar0.OrderType == 4) {
		//相对极坐标
		v[0][0] = AgvVcar0.Ord4.line_v * cos(AgvVcar0.Ord4.line_angle);
		v[1][0] = AgvVcar0.Ord4.line_v * sin(AgvVcar0.Ord4.line_angle);
		v[2][0] = 0;
		v[3][0] = 1;						
		matmul44x41(T, v, W);
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警               
	// 角速度超出范围，限幅滤除
	AgvWwheel0.OrderType = AgvVcar0.OrderType;
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel Vcar2Wwheel_Diff(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		普通动力轮*2、*4：车速》轮速
	//Mode:		前后、差速圆弧、自旋
	//INput:	AgvVcar0车速参数、AgvMotionPara0车型参数
	//Output:	AgvWwheel0轮速参数
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 2) {
		//只有相对直角模式，其他模式的直线运动相当于自旋到一定角度后，再沿垂直方向行驶
		if (AgvVcar0.Ord2.arc_wz != 0){
			//直线运动
			W[0][0] = AgvVcar0.Ord2.line_vy / AgvMotionPara0.wheelRadius;
			W[1][0] = W[0][0];
			W[2][0] = W[0][0];
			W[3][0] = W[0][0];
		}
		else {
			if (AgvVcar0.Ord2.arc_rz <= AgvMotionPara0.wheelBaseW)
				//自旋运动
				AgvVcar0.Ord2.arc_rz = 0;	
			//差速圆弧运动
			W[0][0] = AgvVcar0.Ord2.arc_wz * (AgvVcar0.Ord2.arc_rz+ (AgvMotionPara0.wheelBaseW/ 2)) / AgvMotionPara0.wheelRadius;
			W[1][0] = AgvVcar0.Ord2.arc_wz * (AgvVcar0.Ord2.arc_rz- (AgvMotionPara0.wheelBaseW / 2)) / AgvMotionPara0.wheelRadius;
		}
		
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警               
	// 角速度超出范围，限幅滤除
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}



AgvWwheel Vcar2Wwheel_1_Helm(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		舵轮*1：车速》轮速
	//Mode:		前后、拐弯
	//INput:	AgvVcar0车速参数、AgvMotionPara0车型参数
	//Output:	AgvWwheel0轮速参数
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 1) {
		//绝对直角
	}
	else if (AgvVcar0.OrderType == 2) {
		//相对直角
	}
	else if (AgvVcar0.OrderType == 3) {
		//绝对极坐标系
	}
	else if (AgvVcar0.OrderType == 4) {
		//相对极坐标
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警               
	// 角速度超出范围，限幅滤除
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel Vcar2Wwheel_2_Helm(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		舵轮*2：车速》轮速
	//Mode:		全向
	//INput:	AgvVcar0车速参数、AgvMotionPara0车型参数
	//Output:	AgvWwheel0轮速参数
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 1) {
		//绝对直角
	}
	else if (AgvVcar0.OrderType == 2) {
		//相对直角
	}
	else if (AgvVcar0.OrderType == 3) {
		//绝对极坐标系
	}
	else if (AgvVcar0.OrderType == 4) {
		//相对极坐标
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警               
	// 角速度超出范围，限幅滤除
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel Vcar2Wwheel_4_Helm(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		舵轮*4：车速》轮速
	//Mode:		全向
	//INput:	AgvVcar0车速参数、AgvMotionPara0车型参数
	//Output:	AgvWwheel0轮速参数
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 1) {
		//绝对直角
	}
	else if (AgvVcar0.OrderType == 2) {
		//相对直角
	}
	else if (AgvVcar0.OrderType == 3) {
		//绝对极坐标系
	}
	else if (AgvVcar0.OrderType == 4) {
		//相对极坐标
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警               
	// 角速度超出范围，限幅滤除
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel StopAgv(void) {
	//Func:  AGV急停
	//INput： void
	//Output: AgvWwheel0返回轮速参数
	AgvWwheel AgvWwheel0;
	AgvWwheel0.W1 = 0;
	AgvWwheel0.W2 = 0;
	AgvWwheel0.W3 = 0;
	AgvWwheel0.W4 = 0;
	return AgvWwheel0;
}


AgvPwm Wwheel2PWM(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Fun:		轮速转换为pwm
	//INput:	AgvWwheel0 轮速参数、AgvMotionPara0 车型参数
	//Output:	AgvPwm0 各轴pwm输出
	AgvPwm AgvPwm0;
	double W[4][1];						// 轮毂角速度临时变量
	INT8U i;							// for循环计数变量
	W[0][0] = AgvWwheel0.W1;
	W[1][0] = AgvWwheel0.W2;
	W[2][0] = AgvWwheel0.W3;
	W[3][0] = AgvWwheel0.W4;
	for (i = 0; i < 4; i++) {
		AgvPwm0.Freq[i] = 1000;          // 默认1000Hz
		if (W[i][0] < 0) {
			AgvPwm0.Dir[i] = 0;
			AgvPwm0.Duty[i] = (INT8U)(((-W[i][0]) / AgvMotionPara0.wheelWMax) * 100);
		}
		else {
			AgvPwm0.Dir[i] = 1;
			AgvPwm0.Duty[i] = (INT8U)((W[i][0] / AgvMotionPara0.wheelWMax) * 100);
		}
		if (AgvPwm0.Duty[i] > 100)
			AgvPwm0.Duty[i] = 100;        // 占空比输出超100限幅
		else;
	}
	for (i = 0; i < 4; i++) {
		WidthTemp[i] = AgvPwm0.Duty[i] * 10;
		if (AgvPwm0.Dir[i] == 0)          // 反转
			PulseTemp[i] = AgvPwm0.Freq[i] + 32768;
		else
			PulseTemp[i] = AgvPwm0.Freq[i];
	}
	return AgvPwm0;
}


AgvPls Wwheel2PLS(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Fun:		轮速转换为脉冲输出
	//INput:	AgvWwheel0 轮速参数、AgvMotionPara0 车型参数
	//Output:	AgvPls 各轴脉冲输出
	//AgvPls AgvPls0;

	//return AgvPls0;
}





//++++++++++++++++++++++++++++++++++++++ 轮速》车速接口 ++++++++++++++++++++++++++++++++++++++++++
AgvWwheel Optc2Wwheel(AgvOptc AgvOptc0, AgvMotionPara AgvMotionPara0) {
	//Fun:		光电编码器输入转换为轮速
	//INput:	AgvOptc 光电编码器读数、AgvMotionPara0 车型参数
	//Output:	AgvWwheel0 各轴轮速估计
	//AgvWwheel AgvWwheel0;

	//return AgvWwheel0;
}

AgvWwheel Hall2Wwheel(AgvHall AgvHall0, AgvMotionPara AgvMotionPara0) {
	//Fun:		霍尔传感器输入转换为轮速
	//INput:	AgvHall0 霍尔编码器读数、AgvMotionPara0 车型参数
	//Output:	AgvWwheel0 各轴轮速估计
	//AgvWwheel AgvWwheel0;

	//return AgvWwheel0;
}


AgvVcar Wwheel2Vcar_Mecanum(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Func:		全向- 麦克纳姆轮*4：轮速》车速
	//INput:	AgvWwheel0轮速参数、AgvMotionPara0车型参数
	//Output:	AgvVcar0车速参数
	AgvVcar AgvVcar0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double R[4][4];
	double W[4][1];
	double T[4][4];
	W[0][0] = AgvWwheel0.W1;
	W[1][0] = AgvWwheel0.W2;
	W[2][0] = AgvWwheel0.W3;
	W[3][0] = AgvWwheel0.W4;
	AgvVcar0.OrderType = AgvWwheel0.OrderType;
	W_wheel2V_car(AgvMotionPara0.wheelRadius, AgvMotionPara0.wheelBaseW, AgvMotionPara0.wheelBaseL, T);
	if (AgvWwheel0.OrderType == 1) {
		//绝对直角
		matmul44x41(T, W, v);
		CoordConv2(AgvWwheel0.Rx, 0, 0, R);
		matmul44x41(R, v, V);
		
		AgvVcar0.Ord1.line_Vx = V[0][0];
		AgvVcar0.Ord1.line_Vy = V[1][0];
		AgvVcar0.Ord1.arc_Wz  = V[2][0];
		AgvVcar0.Ord1.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 2) {
		//相对直角
		matmul44x41(T, W, v);
		AgvVcar0.Ord2.line_vx = v[0][0];
		AgvVcar0.Ord2.line_vy = v[1][0];
		AgvVcar0.Ord2.arc_wz  = v[2][0];
		AgvVcar0.Ord2.arc_rz = 0;
	}
	else if (AgvWwheel0.OrderType == 3) {
		//绝对极坐标系
		matmul44x41(T, W, v);
		CoordConv2(AgvWwheel0.Rx, 0, 0, R);
		matmul44x41(R, v, V);
		AgvVcar0.Ord3.line_V = sqrt(V[0][0]* V[0][0]+V[1][0]* V[1][0]);
		AgvVcar0.Ord3.line_Angle = atan(V[1][0]/ V[0][0]);
		AgvVcar0.Ord3.arc_Wz = 0;
		AgvVcar0.Ord3.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 4) {
		//相对极坐标
		matmul44x41(T, W, v);
		AgvVcar0.Ord4.line_v = sqrt(v[0][0] * v[0][0] + v[1][0] * v[1][0]);
		AgvVcar0.Ord4.line_angle = atan(v[1][0] / v[0][0]);
		AgvVcar0.Ord4.arc_wz = 0;
		AgvVcar0.Ord4.arc_rz = 0;
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警    
	return AgvVcar0;
}


AgvVcar Wwheel2Vcar_Diff(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Func:		全向- 麦克纳姆轮*4：轮速》车速
	//INput:	AgvWwheel0轮速参数、AgvMotionPara0车型参数
	//Output:	AgvVcar0车速参数
	AgvVcar AgvVcar0;
	unsigned char i = 0;           // for循环计数
	double V[4][1];
	double v[4][1];
	double R[4][4];
	double W[4][1];
	double T[4][4];
	W[0][0] = AgvWwheel0.W1;
	W[1][0] = AgvWwheel0.W2;
	W[2][0] = AgvWwheel0.W3;
	W[3][0] = AgvWwheel0.W4;
	AgvVcar0.OrderType = AgvWwheel0.OrderType;
	W_wheel2V_car(AgvMotionPara0.wheelRadius, AgvMotionPara0.wheelBaseW, AgvMotionPara0.wheelBaseL, T);
	if (AgvWwheel0.OrderType == 1) {
		//绝对直角
	
		AgvVcar0.Ord1.line_Vx = V[0][0];
		AgvVcar0.Ord1.line_Vy = V[1][0];
		AgvVcar0.Ord1.arc_Wz = V[2][0];
		AgvVcar0.Ord1.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 2) {
		//相对直角
		if (AgvWwheel0.W1){
		}
		AgvVcar0.Ord2.line_vx = v[0][0];
		AgvVcar0.Ord2.line_vy = v[1][0];
		AgvVcar0.Ord2.arc_wz = v[2][0];
		AgvVcar0.Ord2.arc_rz = 0;
	}
	else if (AgvWwheel0.OrderType == 3) {
		//绝对极坐标系
		
		AgvVcar0.Ord3.line_V = sqrt(V[0][0] * V[0][0] + V[1][0] * V[1][0]);
		AgvVcar0.Ord3.line_Angle = atan(V[1][0] / V[0][0]);
		AgvVcar0.Ord3.arc_Wz = 0;
		AgvVcar0.Ord3.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 4) {
		//相对极坐标
		
		AgvVcar0.Ord4.line_v = sqrt(v[0][0] * v[0][0] + v[1][0] * v[1][0]);
		AgvVcar0.Ord4.line_angle = atan(v[1][0] / v[0][0]);
		AgvVcar0.Ord4.arc_wz = 0;
		AgvVcar0.Ord4.arc_rz = 0;
	}
	else
		AgvWwheel0 = StopAgv(); // 没有正确的指令给定，误调用时停车报警               
	return AgvVcar0;
}
//---------------------------------------------END------------------------------------------------


void Func_test(){
	AgvMotionPara AgvMotionPara9;
	AgvMotionPara9.wheelBaseL = 0.52;
	AgvMotionPara9.wheelBaseW = 0.62;
	AgvMotionPara9.wheelRadius = 0.076;
	AgvMotionPara9.wheelWMax = 20;

	AgvWwheel AgvWwheel9;
	AgvVcar AgvVcar9;

	//mecanum轮正解测试
	AgvVcar9.OrderType = 2;
	AgvVcar9.Ord2.line_vx = 1;
	AgvVcar9.Ord2.line_vy = 1;
	AgvVcar9.Ord2.arc_wz = 0;
	AgvVcar9.Ord2.arc_rz = 0;
	AgvWwheel9 = Vcar2Wwheel_Mecanum(AgvVcar9, AgvMotionPara9);
	printf("OrderType: %d\n", AgvWwheel9.OrderType);
	printf("W1: %f\n", AgvWwheel9.W1);
	printf("W2: %f\n", AgvWwheel9.W2);
	printf("W3: %f\n", AgvWwheel9.W3);
	printf("W4: %f\n\n", AgvWwheel9.W4);
	//mecanum轮反解测试
	AgvVcar9 = Wwheel2Vcar_Mecanum(AgvWwheel9, AgvMotionPara9);
	printf("OrderType: %d\n", AgvVcar9.OrderType);
	printf("Vx: %f\n", AgvVcar9.Ord2.line_vx);
	printf("Vy: %f\n", AgvVcar9.Ord2.line_vy);
	printf("Wz: %f\n", AgvVcar9.Ord2.arc_wz);
	printf("Rz: %f\n\n", AgvVcar9.Ord2.arc_rz);	
	
	system("pause");
}


void main()
{
	Func_test();
}

