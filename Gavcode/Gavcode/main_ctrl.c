/***************************************************************************
**File:		模糊自适应PID
**by:		wlqunr@163.com
**date:		2018-11-25
****************************************************************************/

#include <stdio.h>
#include "MAIN_CTRLAGV.h"
#define NB 0
#define NM 1
#define NS 2
#define ZO 3
#define PS 4
#define PM 5
#define PB 6
/*---------------------------------------------------------*/
float fuzzyKp(float e, float ec);
float fuzzyKi(float e, float ec);
float fuzzyKd(float e, float ec);
/*---------------------------------------------------------*/
float tofuzzyTrigle(float x, float a, float b, float c);
float refuzzyTrigle(float x, float a, float b, float c);
float tofuzzyLadderL(float x, float a, float b);
float refuzzyLadderL(float x, float a, float b);
float tofuzzyLadderR(float x, float a, float b);
float refuzzyLadderR(float x, float a, float b);
float smallerAB(float a, float b);
float largerAB(float a, float b);
/*---------------------------------------------------------*/
float positionPID(PosPID *PID);
float incrementPID(IncrePID *PID);
float outLimit(float input, float upper, float floor);
/*----------------------------------------------------------*/



/*--------------------------------------------------------------------------------*/
void testFunc1()
{
	float a, b, Kp, Ki, Kd;
	printf("The E is:");
	scanf_s("%f", &a);
	printf("The Ec is:");
	scanf_s("%f", &b);
	Kp = fuzzyKp(a, b);
	printf("The parameter Kp is: %f\n\n", Kp);
	Ki = fuzzyKi(a, b);
	printf("The parameter Ki is: %f\n\n", Ki);
	Kd = fuzzyKd(a, b);
	printf("The parameter Kd is: %f\n\n", Kd);
	system("pause");
}
/*
void main()
{
	testFunc1();
}
*/
/*--------------------------------------------------------------------------------*/


/*----------------------------------第一层调用------------------------------------*/
/***************************************************************************
**Func:		参数Kp模糊计算
**Input:	e:[-3,3]误差；ec:[-3,3]误差导数
**Output:	Kp:[-0.3,0.3]
****************************************************************************/
float fuzzyKp(float e, float ec)
{
	float es[7];
	float ecs[7];
	/******模糊推理规则的可信度通过取小点运算得到*****/
	float form[7][7];//(表X7)（隶属度表）
	int i, j;
	/*************求得的最大值赋给form[a][b]*********/
	int a = 0, b = 0;
	float lsd; int p;
	float  detkp;
	/*************模糊规则表*************/
	int kp[7][7] = {{PB,PB,PM,PS,PS,ZO,ZO},
					{PB,PB,PM,PS,PS,ZO,NS},
					{PM,PM,PM,PS,ZO,NS,NS},
					{PM,PM,PS,ZO,NS,NM,NM},
					{PS,PS,ZO,NS,NS,NM,NM},
					{PS,ZO,NS,NM,NM,NM,NB},
					{ZO,ZO,NM,NM,NM,NB,NB} };

	//输入模糊化
	es[NB] = tofuzzyLadderL(e, -3, -1);
	es[NM] = tofuzzyTrigle(e, -3, -2, 0);
	es[NS] = tofuzzyTrigle(e, -3, -1, 1);
	es[ZO] = tofuzzyTrigle(e, -2, 0, 2);
	es[PS] = tofuzzyTrigle(e, -1, 1, 3);
	es[PM] = tofuzzyTrigle(e, 0, 2, 3);
	es[PB] = tofuzzyLadderR(e, 1, 3);

	//输入模糊化
	ecs[NB] = tofuzzyLadderL(ec, -3, -1);
	ecs[NM] = tofuzzyTrigle(ec, -3, -2, 0);
	ecs[NS] = tofuzzyTrigle(ec, -3, -1, 1);
	ecs[ZO] = tofuzzyTrigle(ec, -2, 0, 2);
	ecs[PS] = tofuzzyTrigle(ec, -1, 1, 3);
	ecs[PM] = tofuzzyTrigle(ec, 0, 2, 3);
	ecs[PB] = tofuzzyLadderR(ec, 1, 3);

	for (i = 0; i < 7; i++)
	{
		float w, h, r;
		for (j = 0; j < 7; j++)
		{
			h = es[i];
			r = ecs[j];
			w = smallerAB(h, r);
			form[i][j] = w;
		}
	}

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (form[a][b] < form[i][j])
			{
				a = i;
				b = j;
			}
		}
	}

	lsd = form[a][b];//es和ecs最值中的最大值
	p = kp[a][b];

	//输出去模糊化
	if (p == NB)
		detkp = refuzzyLadderL(lsd, -0.3, -0.1);
	else if (p == NM)
		detkp = refuzzyTrigle(lsd, -0.3, 0.2, 0);
	else if (p == NS)
		detkp = refuzzyTrigle(lsd, -0.3, -0.1, 0.1);
	else if (p == ZO)
		detkp = refuzzyTrigle(lsd, -0.2, 0, 0.2);
	else if (p == PS)
		detkp = refuzzyTrigle(lsd, -0.1, 0.1, 0.3);
	else if (p == PM)
		detkp = refuzzyTrigle(lsd, 0, 0.2, 0.3);
	else if (p == PB)
		detkp = refuzzyLadderR(lsd, 0.1, 0.3);
	return detkp;
}

/***************************************************************************
**Func:		参数Ki模糊计算
**Input:	e:[-3,3]误差；ec:[-3,3]误差导数
**Output:	Ki:[-0.3,0.3]
****************************************************************************/
float fuzzyKi(float e, float ec)
{
	float es[7];
	float ecs[7];
	/******模糊推理规则的可信度通过取小点运算得到*****/
	float form[7][7];//(表X7)（隶属度表）
	int i, j;
	/*************求得的最大值赋给form[a][b]*********/
	int a = 0, b = 0;
	float lsd; int p;
	float  detkp;
	/*************模糊规则表*************/
	int kp[7][7] = { {NB,NB,NM,NM,NS,ZO,ZO},
					{NB,NB,NM,NS,NS,ZO,ZO},
					{NB,NM,NS,NS,ZO,PS,PS},
					{NM,NM,NS,ZO,PS,PM,PM},
					{NM,NS,ZO,PS,PS,PM,PB},
					{ZO,ZO,PS,PS,PM,PB,PB},
					{ZO,ZO,PS,PM,PM,PB,PB} };

	//输入模糊化
	es[NB] = tofuzzyLadderL(e, -3, -1);
	es[NM] = tofuzzyTrigle(e, -3, -2, 0);
	es[NS] = tofuzzyTrigle(e, -3, -1, 1);
	es[ZO] = tofuzzyTrigle(e, -2, 0, 2);
	es[PS] = tofuzzyTrigle(e, -1, 1, 3);
	es[PM] = tofuzzyTrigle(e, 0, 2, 3);
	es[PB] = tofuzzyLadderR(e, 1, 3);

	//输入模糊化
	ecs[NB] = tofuzzyLadderL(ec, -3, -1);
	ecs[NM] = tofuzzyTrigle(ec, -3, -2, 0);
	ecs[NS] = tofuzzyTrigle(ec, -3, -1, 1);
	ecs[ZO] = tofuzzyTrigle(ec, -2, 0, 2);
	ecs[PS] = tofuzzyTrigle(ec, -1, 1, 3);
	ecs[PM] = tofuzzyTrigle(ec, 0, 2, 3);
	ecs[PB] = tofuzzyLadderR(ec, 1, 3);

	for (i = 0; i < 7; i++)
	{
		float w, h, r;
		for (j = 0; j < 7; j++)
		{
			h = es[i];
			r = ecs[j];
			w = smallerAB(h, r);
			form[i][j] = w;
		}
	}

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (form[a][b] < form[i][j])
			{
				a = i;
				b = j;
			}
		}
	}

	lsd = form[a][b];//es和ecs最值中的最大值
	p = kp[a][b];

	//输出去模糊化
	if (p == NB)
		detkp = refuzzyLadderL(lsd, -0.3, -0.1);
	else if (p == NM)
		detkp = refuzzyTrigle(lsd, -0.3, 0.2, 0);
	else if (p == NS)
		detkp = refuzzyTrigle(lsd, -0.3, -0.1, 0.1);
	else if (p == ZO)
		detkp = refuzzyTrigle(lsd, -0.2, 0, 0.2);
	else if (p == PS)
		detkp = refuzzyTrigle(lsd, -0.1, 0.1, 0.3);
	else if (p == PM)
		detkp = refuzzyTrigle(lsd, 0, 0.2, 0.3);
	else if (p == PB)
		detkp = refuzzyLadderR(lsd, 0.1, 0.3);
	return detkp;
}


/***************************************************************************
**Func:		参数Kd模糊计算
**Input:	e:[-3,3]误差；ec:[-3,3]误差导数
**Output:	Kd:[-0.3,0.3]
****************************************************************************/
float fuzzyKd(float e, float ec)
{
	float es[7];
	float ecs[7];
	/******模糊推理规则的可信度通过取小点运算得到*****/
	float form[7][7];//(表X7)（隶属度表）
	int i, j;
	/*************求得的最大值赋给form[a][b]*********/
	int a = 0, b = 0;
	float lsd; int p;
	float  detkp;
	/*************模糊规则表*************/
	int kp[7][7] = { {PS,NS,NB,NB,NB,NM,PS},
					{PS,NS,NB,NM,NM,NS,ZO},
					{ZO,NS,NM,NM,NS,NS,ZO},
					{ZO,NS,NS,NS,NS,NS,ZO},
					{ZO,ZO,ZO,ZO,ZO,ZO,ZO},
					{PB,NS,PS,PS,PS,PS,PB},
					{PB,PM,PM,PM,PS,PS,PB} };

	//输入模糊化
	es[NB] = tofuzzyLadderL(e, -3, -1);
	es[NM] = tofuzzyTrigle(e, -3, -2, 0);
	es[NS] = tofuzzyTrigle(e, -3, -1, 1);
	es[ZO] = tofuzzyTrigle(e, -2, 0, 2);
	es[PS] = tofuzzyTrigle(e, -1, 1, 3);
	es[PM] = tofuzzyTrigle(e, 0, 2, 3);
	es[PB] = tofuzzyLadderR(e, 1, 3);

	//输入模糊化
	ecs[NB] = tofuzzyLadderL(ec, -3, -1);
	ecs[NM] = tofuzzyTrigle(ec, -3, -2, 0);
	ecs[NS] = tofuzzyTrigle(ec, -3, -1, 1);
	ecs[ZO] = tofuzzyTrigle(ec, -2, 0, 2);
	ecs[PS] = tofuzzyTrigle(ec, -1, 1, 3);
	ecs[PM] = tofuzzyTrigle(ec, 0, 2, 3);
	ecs[PB] = tofuzzyLadderR(ec, 1, 3);

	for (i = 0; i < 7; i++)
	{
		float w, h, r;
		for (j = 0; j < 7; j++)
		{
			h = es[i];
			r = ecs[j];
			w = smallerAB(h, r);
			form[i][j] = w;
		}
	}

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (form[a][b] < form[i][j])
			{
				a = i;
				b = j;
			}
		}
	}

	lsd = form[a][b];//es和ecs最值中的最大值
	p = kp[a][b];

	//输出去模糊化
	if (p == NB)
		detkp = refuzzyLadderL(lsd, -0.3, -0.1);
	else if (p == NM)
		detkp = refuzzyTrigle(lsd, -0.3, 0.2, 0);
	else if (p == NS)
		detkp = refuzzyTrigle(lsd, -0.3, -0.1, 0.1);
	else if (p == ZO)
		detkp = refuzzyTrigle(lsd, -0.2, 0, 0.2);
	else if (p == PS)
		detkp = refuzzyTrigle(lsd, -0.1, 0.1, 0.3);
	else if (p == PM)
		detkp = refuzzyTrigle(lsd, 0, 0.2, 0.3);
	else if (p == PB)
		detkp = refuzzyLadderR(lsd, 0.1, 0.3);
	return detkp;
}
/*-------------------------------------END----------------------------------------*/



/*----------------------------------第二层调用------------------------------------*/
/***************************************************************************
**Func:		模糊化处理（三角形隶属度）
**Input:	
**Output:	0
****************************************************************************/
float tofuzzyTrigle(float x, float a, float b, float c)
{
	if (x <= a)
		return (0);
	else if ((a < x) && (x <= b))
		return((x - a) / (b - a));
	else if ((b < x) && (x <= c))
		return((c - x) / (c - b));
	else if (x > c)
		return (0);
}

/***************************************************************************
**Func:		三角形反模糊化处理（最大隶属度法）
**Input:
**Output:	0
****************************************************************************/
float refuzzyTrigle(float x, float a, float b, float c)
{
	float y, z;
	z = (b - a)*x + a;
	y = c - (c - b)*x;
	return (y + z) / 2;
}

/***************************************************************************
**Func:		模糊化处理（左梯形隶属度）
**Input:
**Output:	0
****************************************************************************/
float tofuzzyLadderL(float x, float a, float b)
{
	if (x <= a)
		return 1;
	else if ((a < x) && (x <= b))
		return (b - x) / (b - a);
	else if (x > b)
		return 0;
}

/***************************************************************************
**Func:		左梯形反模糊化处理（最大隶属度法）
**Input:        值x，左边a，右边b
**Outpu:	0
****************************************************************************/
float refuzzyLadderL(float x, float a, float b)
{
	return b - (b - a)*x;
}

/***************************************************************************
**Func:		模糊化处理（右梯形隶属度）
**Input:
**Output:	0
****************************************************************************/
float tofuzzyLadderR(float x, float a, float b)
{
	if (x <= a)
		return 0;
	if ((a < x) && (x < b))
		return (x - a) / (b - a);
	if (x >= b)
		return 1;
} 

/***************************************************************************
**Func:		右梯形反模糊化处理（最大隶属度法）
**Input:
**Output:	0
****************************************************************************/
float refuzzyLadderR(float x, float a, float b)
{
	return (b - a)*x + a;
}

/***************************************************************************
**Func:		交集运算
**Input:	参数a、参数b
**Output:	a，b中较小值
****************************************************************************/
float smallerAB(float a, float b)
{
	return (a < b) ? a : b;
}

/***************************************************************************
**Func:		交集运算
**Input:	参数a、参数b
**Output:	a，b中较大值
****************************************************************************/
float largerAB(float a, float b)
{
	return (a < b) ? b : a;
}
/*-------------------------------------END---------------------------------------*/



/*----------------------------------PID调用------------------------------------*/
/***************************************************************************
**Func:		位置式PID 
**Input:	当前误差e0，上一误差e1, 误差累积eSum
**Output:	位置式PID输出
****************************************************************************/
float positionPID(PosPID *PID)
{
	float out = 0;
	PID->Ek = PID->valueSet - PID->valueActual;
	PID->EkSum += PID->Ek;
	out = PID->Kp * PID->Ek + (PID->Ki * PID->EkSum) + PID->Kd * (PID->Ek_1 - PID->Ek);
	PID->Ek_1 = PID->Ek;
	return out;
}


/***************************************************************************
**Func:		增量式PID
**Input:	当前误差e0，上一误差e1, 误差累积eSum
**Output:	位置式PID输出
****************************************************************************/
float incrementPID(IncrePID *PID)
{
	float out = 0;
	PID->Ek = PID->valueSet - PID->valueActual;
	out = (PID->Kp *(PID->Ek - PID->Ek_1)) + (PID->Ki * PID->Ek) + (PID->Kd * (PID->Ek - (2* PID->Ek_1) + PID->Ek_2));
	PID->Ek_1 = PID->Ek;
	return out;
}


/***************************************************************************
**Func:		限幅控制
**Input:	input输入值，upper上限，floor下限
**Output:	位置式PID输出
****************************************************************************/
float outLimit(float input, float upper, float floor)
{
	float output;
	if (input > upper)		output = upper;
	if (input < floor)		output = floor;
	else					output = input;
	return output;
}
