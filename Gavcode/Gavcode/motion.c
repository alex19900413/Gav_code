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
  * 1.������������������ϵΪ�ο����������ģʽ��С������ϵΪ�ο�
  * 2.��ʽ����ʱ��С�����ꡢ4����������X��������ͳһˮƽ����
  ********************************************************************************/
#include <math.h>
#include "MotionDataType.h"
#include "vmarith.h"
#include "MotionAGV.h"

//extern INT16U PulseTemp[4]; // ��FPGA��PWM�м������  direction=0 (HSB=0) and period(50us by 0.1us*500 )
//extern INT16U WidthTemp[4]; // ��FPGA��PWM�м������  pulse width (8us by 0.1us*80 ) ��֪ռ�ձ�Ĭ��Ϊ 80/500=16%
INT16U PulseTemp[4]; // ��FPGA��PWM�м������  direction=0 (HSB=0) and period(50us by 0.1us*500 )
INT16U WidthTemp[4]; // ��FPGA��PWM�м������  pulse width (8us by 0.1us*80 ) ��֪ռ�ձ�Ĭ��Ϊ 80/500=16%


//++++++++++++++++++++++++++++++++++++++ ���١����ٽӿ� ++++++++++++++++++++++++++++++++++++++++++
double Angle2rad(double angleTemp) {
	//Fun:  �Ƕ�ֵת��Ϊ�����ƣ�������ת����������
	//INput�� �Ƕȣ�0 - 360.00��
	//Output: ���ȣ�0 - 2*pi
	double radTemp = 0;
	radTemp = (angleTemp / 180) * Pi;
	return radTemp;
}


AgvWwheel Vcar2Wwheel_Mecanum(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		�����ķ��*4�����١�����
	//Mode:		ȫ��
	//INput:	AgvVcar0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvWwheel0���ٲ���
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // forѭ������
	double V[4][1];
	double v[4][1];
	double R[4][4];
	double W[4][1];
	double T[4][4];
	V_car2W_wheel(AgvMotionPara0.wheelRadius, AgvMotionPara0.wheelBaseW, AgvMotionPara0.wheelBaseL, T);
	if (AgvVcar0.OrderType == 1) {
		//����ֱ��
		V[0][0] = AgvVcar0.Ord1.line_Vx;
		V[1][0] = AgvVcar0.Ord1.line_Vy;
		V[2][0] = AgvVcar0.Ord1.arc_Wz;
		V[3][0] = 1;						
		CoordConv(AgvVcar0.Ord1.Rx, 0, 0, R);
		matmul44x41(R, V, v);
		matmul44x41(T, v, W);
	}
	else if (AgvVcar0.OrderType == 2) {
		//���ֱ��
		v[0][0] = AgvVcar0.Ord2.line_vx;
		v[1][0] = AgvVcar0.Ord2.line_vy;
		v[2][0] = AgvVcar0.Ord2.arc_wz;
		v[3][0] = 1;						
		matmul44x41(T, v, W);
	}
	else if (AgvVcar0.OrderType == 3) {
		//���Լ�����ϵ
		V[0][0] = AgvVcar0.Ord3.line_V * cos(AgvVcar0.Ord3.line_Angle);
		V[1][0] = AgvVcar0.Ord3.line_V * sin(AgvVcar0.Ord3.line_Angle);
		V[2][0] = 0;
		V[3][0] = 1;						
		CoordConv(AgvVcar0.Ord3.Rx, 0, 0, R);
		matmul44x41(R, V, v);
		matmul44x41(T, v, W);
	}
	else if (AgvVcar0.OrderType == 4) {
		//��Լ�����
		v[0][0] = AgvVcar0.Ord4.line_v * cos(AgvVcar0.Ord4.line_angle);
		v[1][0] = AgvVcar0.Ord4.line_v * sin(AgvVcar0.Ord4.line_angle);
		v[2][0] = 0;
		v[3][0] = 1;						
		matmul44x41(T, v, W);
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������               
	// ���ٶȳ�����Χ���޷��˳�
	AgvWwheel0.OrderType = AgvVcar0.OrderType;
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel Vcar2Wwheel_Diff(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		��ͨ������*2��*4�����١�����
	//Mode:		ǰ�󡢲���Բ��������
	//INput:	AgvVcar0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvWwheel0���ٲ���
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // forѭ������
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 2) {
		//ֻ�����ֱ��ģʽ������ģʽ��ֱ���˶��൱��������һ���ǶȺ����ش�ֱ������ʻ
		if (AgvVcar0.Ord2.arc_wz != 0){
			//ֱ���˶�
			W[0][0] = AgvVcar0.Ord2.line_vy / AgvMotionPara0.wheelRadius;
			W[1][0] = W[0][0];
			W[2][0] = W[0][0];
			W[3][0] = W[0][0];
		}
		else {
			if (AgvVcar0.Ord2.arc_rz <= AgvMotionPara0.wheelBaseW)
				//�����˶�
				AgvVcar0.Ord2.arc_rz = 0;	
			//����Բ���˶�
			W[0][0] = AgvVcar0.Ord2.arc_wz * (AgvVcar0.Ord2.arc_rz+ (AgvMotionPara0.wheelBaseW/ 2)) / AgvMotionPara0.wheelRadius;
			W[1][0] = AgvVcar0.Ord2.arc_wz * (AgvVcar0.Ord2.arc_rz- (AgvMotionPara0.wheelBaseW / 2)) / AgvMotionPara0.wheelRadius;
		}
		
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������               
	// ���ٶȳ�����Χ���޷��˳�
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}



AgvWwheel Vcar2Wwheel_1_Helm(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		����*1�����١�����
	//Mode:		ǰ�󡢹���
	//INput:	AgvVcar0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvWwheel0���ٲ���
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // forѭ������
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 1) {
		//����ֱ��
	}
	else if (AgvVcar0.OrderType == 2) {
		//���ֱ��
	}
	else if (AgvVcar0.OrderType == 3) {
		//���Լ�����ϵ
	}
	else if (AgvVcar0.OrderType == 4) {
		//��Լ�����
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������               
	// ���ٶȳ�����Χ���޷��˳�
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel Vcar2Wwheel_2_Helm(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		����*2�����١�����
	//Mode:		ȫ��
	//INput:	AgvVcar0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvWwheel0���ٲ���
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // forѭ������
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 1) {
		//����ֱ��
	}
	else if (AgvVcar0.OrderType == 2) {
		//���ֱ��
	}
	else if (AgvVcar0.OrderType == 3) {
		//���Լ�����ϵ
	}
	else if (AgvVcar0.OrderType == 4) {
		//��Լ�����
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������               
	// ���ٶȳ�����Χ���޷��˳�
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel Vcar2Wwheel_4_Helm(AgvVcar AgvVcar0, AgvMotionPara AgvMotionPara0) {
	//Func:		����*4�����١�����
	//Mode:		ȫ��
	//INput:	AgvVcar0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvWwheel0���ٲ���
	AgvWwheel AgvWwheel0;
	unsigned char i = 0;           // forѭ������
	double V[4][1];
	double v[4][1];
	double W[4][1];
	if (AgvVcar0.OrderType == 1) {
		//����ֱ��
	}
	else if (AgvVcar0.OrderType == 2) {
		//���ֱ��
	}
	else if (AgvVcar0.OrderType == 3) {
		//���Լ�����ϵ
	}
	else if (AgvVcar0.OrderType == 4) {
		//��Լ�����
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������               
	// ���ٶȳ�����Χ���޷��˳�
	AgvWwheel0.W1 = W[0][0];
	AgvWwheel0.W2 = W[1][0];
	AgvWwheel0.W3 = W[2][0];
	AgvWwheel0.W4 = W[3][0];
	return AgvWwheel0;
}


AgvWwheel StopAgv(void) {
	//Func:  AGV��ͣ
	//INput�� void
	//Output: AgvWwheel0�������ٲ���
	AgvWwheel AgvWwheel0;
	AgvWwheel0.W1 = 0;
	AgvWwheel0.W2 = 0;
	AgvWwheel0.W3 = 0;
	AgvWwheel0.W4 = 0;
	return AgvWwheel0;
}


AgvPwm Wwheel2PWM(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Fun:		����ת��Ϊpwm
	//INput:	AgvWwheel0 ���ٲ�����AgvMotionPara0 ���Ͳ���
	//Output:	AgvPwm0 ����pwm���
	AgvPwm AgvPwm0;
	double W[4][1];						// ��챽��ٶ���ʱ����
	INT8U i;							// forѭ����������
	W[0][0] = AgvWwheel0.W1;
	W[1][0] = AgvWwheel0.W2;
	W[2][0] = AgvWwheel0.W3;
	W[3][0] = AgvWwheel0.W4;
	for (i = 0; i < 4; i++) {
		AgvPwm0.Freq[i] = 1000;          // Ĭ��1000Hz
		if (W[i][0] < 0) {
			AgvPwm0.Dir[i] = 0;
			AgvPwm0.Duty[i] = (INT8U)(((-W[i][0]) / AgvMotionPara0.wheelWMax) * 100);
		}
		else {
			AgvPwm0.Dir[i] = 1;
			AgvPwm0.Duty[i] = (INT8U)((W[i][0] / AgvMotionPara0.wheelWMax) * 100);
		}
		if (AgvPwm0.Duty[i] > 100)
			AgvPwm0.Duty[i] = 100;        // ռ�ձ������100�޷�
		else;
	}
	for (i = 0; i < 4; i++) {
		WidthTemp[i] = AgvPwm0.Duty[i] * 10;
		if (AgvPwm0.Dir[i] == 0)          // ��ת
			PulseTemp[i] = AgvPwm0.Freq[i] + 32768;
		else
			PulseTemp[i] = AgvPwm0.Freq[i];
	}
	return AgvPwm0;
}


AgvPls Wwheel2PLS(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Fun:		����ת��Ϊ�������
	//INput:	AgvWwheel0 ���ٲ�����AgvMotionPara0 ���Ͳ���
	//Output:	AgvPls �����������
	//AgvPls AgvPls0;

	//return AgvPls0;
}





//++++++++++++++++++++++++++++++++++++++ ���١����ٽӿ� ++++++++++++++++++++++++++++++++++++++++++
AgvWwheel Optc2Wwheel(AgvOptc AgvOptc0, AgvMotionPara AgvMotionPara0) {
	//Fun:		������������ת��Ϊ����
	//INput:	AgvOptc ��������������AgvMotionPara0 ���Ͳ���
	//Output:	AgvWwheel0 �������ٹ���
	//AgvWwheel AgvWwheel0;

	//return AgvWwheel0;
}

AgvWwheel Hall2Wwheel(AgvHall AgvHall0, AgvMotionPara AgvMotionPara0) {
	//Fun:		��������������ת��Ϊ����
	//INput:	AgvHall0 ����������������AgvMotionPara0 ���Ͳ���
	//Output:	AgvWwheel0 �������ٹ���
	//AgvWwheel AgvWwheel0;

	//return AgvWwheel0;
}


AgvVcar Wwheel2Vcar_Mecanum(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Func:		ȫ��- �����ķ��*4�����١�����
	//INput:	AgvWwheel0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvVcar0���ٲ���
	AgvVcar AgvVcar0;
	unsigned char i = 0;           // forѭ������
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
		//����ֱ��
		matmul44x41(T, W, v);
		CoordConv2(AgvWwheel0.Rx, 0, 0, R);
		matmul44x41(R, v, V);
		
		AgvVcar0.Ord1.line_Vx = V[0][0];
		AgvVcar0.Ord1.line_Vy = V[1][0];
		AgvVcar0.Ord1.arc_Wz  = V[2][0];
		AgvVcar0.Ord1.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 2) {
		//���ֱ��
		matmul44x41(T, W, v);
		AgvVcar0.Ord2.line_vx = v[0][0];
		AgvVcar0.Ord2.line_vy = v[1][0];
		AgvVcar0.Ord2.arc_wz  = v[2][0];
		AgvVcar0.Ord2.arc_rz = 0;
	}
	else if (AgvWwheel0.OrderType == 3) {
		//���Լ�����ϵ
		matmul44x41(T, W, v);
		CoordConv2(AgvWwheel0.Rx, 0, 0, R);
		matmul44x41(R, v, V);
		AgvVcar0.Ord3.line_V = sqrt(V[0][0]* V[0][0]+V[1][0]* V[1][0]);
		AgvVcar0.Ord3.line_Angle = atan(V[1][0]/ V[0][0]);
		AgvVcar0.Ord3.arc_Wz = 0;
		AgvVcar0.Ord3.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 4) {
		//��Լ�����
		matmul44x41(T, W, v);
		AgvVcar0.Ord4.line_v = sqrt(v[0][0] * v[0][0] + v[1][0] * v[1][0]);
		AgvVcar0.Ord4.line_angle = atan(v[1][0] / v[0][0]);
		AgvVcar0.Ord4.arc_wz = 0;
		AgvVcar0.Ord4.arc_rz = 0;
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������    
	return AgvVcar0;
}


AgvVcar Wwheel2Vcar_Diff(AgvWwheel AgvWwheel0, AgvMotionPara AgvMotionPara0) {
	//Func:		ȫ��- �����ķ��*4�����١�����
	//INput:	AgvWwheel0���ٲ�����AgvMotionPara0���Ͳ���
	//Output:	AgvVcar0���ٲ���
	AgvVcar AgvVcar0;
	unsigned char i = 0;           // forѭ������
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
		//����ֱ��
	
		AgvVcar0.Ord1.line_Vx = V[0][0];
		AgvVcar0.Ord1.line_Vy = V[1][0];
		AgvVcar0.Ord1.arc_Wz = V[2][0];
		AgvVcar0.Ord1.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 2) {
		//���ֱ��
		if (AgvWwheel0.W1){
		}
		AgvVcar0.Ord2.line_vx = v[0][0];
		AgvVcar0.Ord2.line_vy = v[1][0];
		AgvVcar0.Ord2.arc_wz = v[2][0];
		AgvVcar0.Ord2.arc_rz = 0;
	}
	else if (AgvWwheel0.OrderType == 3) {
		//���Լ�����ϵ
		
		AgvVcar0.Ord3.line_V = sqrt(V[0][0] * V[0][0] + V[1][0] * V[1][0]);
		AgvVcar0.Ord3.line_Angle = atan(V[1][0] / V[0][0]);
		AgvVcar0.Ord3.arc_Wz = 0;
		AgvVcar0.Ord3.arc_Rz = 0;
	}
	else if (AgvWwheel0.OrderType == 4) {
		//��Լ�����
		
		AgvVcar0.Ord4.line_v = sqrt(v[0][0] * v[0][0] + v[1][0] * v[1][0]);
		AgvVcar0.Ord4.line_angle = atan(v[1][0] / v[0][0]);
		AgvVcar0.Ord4.arc_wz = 0;
		AgvVcar0.Ord4.arc_rz = 0;
	}
	else
		AgvWwheel0 = StopAgv(); // û����ȷ��ָ������������ʱͣ������               
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

	//mecanum���������
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
	//mecanum�ַ������
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

