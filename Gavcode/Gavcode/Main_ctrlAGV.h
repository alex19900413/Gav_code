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


//motion.c********************************************************************************


//----------------------------------------------------------------------------------------

//track.c ********************************************************************************
//----------------------------------------------------------------------------------------
#endif