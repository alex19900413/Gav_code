#ifndef MAIN_CTRLAGV_H
#define MAIN_CTRLAGV_H

#define INT8U unsigned char
#define INT16U unsigned short


typedef struct POS_PID
{
	float Kp;			// ����ϵ��
	float Ki;			// ����ϵ��
	float Kd;			// ΢��ϵ��

	float valueSet;		// �趨ֵ
	float valueActual;	// ʵ��ֵ
	float Ek;			// ��ǰ���
	float Ek_1;			// ǰһ���
	float EkSum;
}PosPID;

typedef struct INCRE_PID
{
	float Kp;			// ����ϵ��
	float Ki;			// ����ϵ�� 
	float Kd;			// ΢��ϵ��

	float valueSet;		// �趨ֵ
	float valueActual;	// ʵ��ֵ
	float Ek;			// ��ǰ���
	float Ek_1;			// ǰһ���
	float Ek_2;			// ��ǰһ�����
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