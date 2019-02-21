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


/*---------------------------------------------------------*/
extern float fuzzyKp(float e, float ec);
extern float fuzzyKi(float e, float ec);
extern float fuzzyKd(float e, float ec);
extern float tofuzzyTrigle(float x, float a, float b, float c);
extern float refuzzyTrigle(float x, float a, float b, float c);
extern float tofuzzyLadderL(float x, float a, float b);
extern float refuzzyLadderL(float x, float a, float b);
extern float tofuzzyLadderR(float x, float a, float b);
extern float refuzzyLadderR(float x, float a, float b);
extern float smallerAB(float a, float b);
extern float largerAB(float a, float b);
extern float positionPID(PosPID *PID);
extern float incrementPID(IncrePID *PID);
extern float outLimit(float input, float upper, float floor);

#endif