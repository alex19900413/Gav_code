//-----------------------------------------------------------------------------
/*******************************************************
 * 向量、矩阵运算函数
 * 2013.04.01
 *******************************************************/
#ifndef _vmarith_h_
#define _vmarith_h_
#ifndef FRPTC
typedef double(*matp)[4];
typedef double(*matpp)[1];
#endif
//--------(三维)-------------------------------------------------------- 
// 向量相加
extern double* vadd(double A[3], double B[3], double R[3]);
extern double* vsub(double A[3], double B[3], double R[3]);
extern double* vmul(double A[3], double c, double R[3]);
extern double norm(double A[3]);
extern double* cross(double A[3], double B[3], double R[3]);
//--------(二维)---------------------------------------------------------
// 二维向量相加
extern double* v2add(double A[2], double B[2], double R[2]);
extern double* v2sub(double A[2], double B[2], double R[2]);
extern double* v2mul(double A[2], double c, double R[2]);
extern double norm2(double A[2]);
//--------(矩阵)---------------------------------------------------------
extern matp matmul(double A[4][4], double B[4][4], double R[4][4]);
extern matp Ltranmat(double link[4], double q, double T[4][4]);
extern matp trotx(double q, double T[4][4]);
extern matp troty(double q, double T[4][4]);
extern matp trotz(double q, double T[4][4]);
extern matp matmul(double A[4][4], double B[4][4], double R[4][4]);
extern void unitmat(double T[4][4]);
extern matpp matmul44x41(double A[4][4], double B[4][1], double R[4][1]);
extern matp V_car2W_wheel(double agv_r, double agv_w, double agv_l,
	double T[4][4]);
extern matp W_wheel2V_car(double agv_r, double agv_w, double agv_l,
	double T[4][4]);
extern matp CoordConv(double RX, double XP, double YP, double T[4][4]);
#endif
