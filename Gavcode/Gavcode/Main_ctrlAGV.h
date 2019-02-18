#ifndef MAIN_CTRLAGV_H
#define MAIN_CTRLAGV_H

#define INT8U unsigned char
#define INT16U unsigned short


typedef struct POS_PID
{
	float Kp;			// 比例系数
	float Ki;			// 积分系数
	float Kd;			// 微分系数

	float valueSet;		// 设定值
	float valueActual;	// 实际值
	float Ek;			// 当前误差
	float Ek_1;			// 前一误差
	float EkSum;
}PosPID;

typedef struct INCRE_PID
{
	float Kp;			// 比例系数
	float Ki;			// 积分系数 
	float Kd;			// 微分系数

	float valueSet;		// 设定值
	float valueActual;	// 实际值
	float Ek;			// 当前误差
	float Ek_1;			// 前一误差
	float Ek_2;			// 再前一次误差
}IncrePID;


//motion.c********************************************************************************


//----------------------------------------------------------------------------------------

//track.c ********************************************************************************
//----------------------------------------------------------------------------------------
#endif