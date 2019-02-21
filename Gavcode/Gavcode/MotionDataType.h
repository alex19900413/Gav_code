/******************************************************************************
  FileName: MotionDataType.h
  Platform: DSP 32-bit TMS320C6713
  Version: 1.0
  Date:  2009-11-18
  Description:  统一数据类型定义
  History:
	  <author>   <time>   <version >  <desc>
  W.G   2009/11/18  1.00      build this file
  W.G   2010-4-6   1.10     Modify long long/long double
******************************************************************************/
#ifndef MOTION_DATA_TYPE_H__
#define MOTION_DATA_TYPE_H__
#ifdef __cplusplus
extern "C" {
#endif

	typedef unsigned char  INT8U;    //8-bit unsigned integer
	typedef signed char   INT8S;    //8-bit signed integer
	typedef INT8S    INT8;    //for backward compatibility
	typedef unsigned short  INT16U;    //16-bit unsigned integer
	typedef signed short  INT16S;    //16-bit signed integer
	typedef INT16S    INT16;    //for backward compatibility
	typedef unsigned int  INT32U;    //32-bit unsigned integer
	typedef signed int   INT32S;    //32-bit signed integer
	//typedef enum    INT32EM;   //32-bit enum
	typedef float    FLOAT32;   //32-bit floating-point numbers
	typedef INT32S    INT32;    //for backward compatibility
	typedef unsigned long  INT40U;    //40-bit unsigned integer
	typedef signed long   INT40S;    //40-bit signed integer
	typedef INT40S    INT40;    //for backward compatibility
	typedef long long   INT64S;    //64-bit long long integer
	typedef unsigned long long INT64U;    //64-bit unsigned long long integer
	typedef long double   DOUBLE64;   //64-bit long double floating numbers
	typedef double    FLOAT64;   //64-bit double floating numbers
	typedef INT8U    BOOL;    //boolean type
#ifndef TRUE
#define TRUE                1
#endif
#ifndef FALSE
#define FALSE               0
#endif
#ifndef SUCCESS
#define SUCCESS    TRUE 
#endif
#ifndef FAILED 
#define FAILED    FALSE
#endif 
#ifndef IN_PI
#define IN_PI  3.1415926535897932384626433832795
#endif
#define Pi 3.1415926535897932384626433832795  // 弧度制
#define d2r(d)   ((d)*IN_PI/180.0)
#define r2d(d)   ((d)*180.0/IN_PI)
//------------0->360转-180->180------------------------
#define changeangle(angle)  angle = angle>180? (angle-360):angle
//====================== 16bit Data bit define ===============
#define BIT0_16    0x0001
#define BIT1_16    0x0002
#define BIT2_16    0x0004
#define BIT3_16    0x0008
#define BIT4_16    0x0010
#define BIT5_16    0x0020
#define BIT6_16    0x0040
#define BIT7_16    0x0080
#define BIT8_16    0x0100
#define BIT9_16    0x0200
#define BIT10_16   0x0400
#define BIT11_16   0x0800
#define BIT12_16   0x1000
#define BIT13_16   0x2000
#define BIT14_16   0x4000
#define BIT15_16   0x8000
#define _BIT0_16   0xfffe
#define _BIT1_16   0xfffd
#define _BIT2_16   0xfffb
#define _BIT3_16   0xfff7
#define _BIT4_16   0xffef
#define _BIT5_16   0xffdf
#define _BIT6_16   0xffbf
#define _BIT7_16   0xff7f
#define _BIT8_16   0xfeff
#define _BIT9_16   0xfdff
#define _BIT10_16  0xfbff
#define _BIT11_16  0xf7ff
#define _BIT12_16  0xefff
#define _BIT13_16  0xdfff
#define _BIT14_16  0xbfff
#define _BIT15_16  0x7fff
//====================== 32 bit Data bit define ===============
#define BIT0_32    0x00000001
#define BIT1_32    0x00000002
#define BIT2_32    0x00000004
#define BIT3_32    0x00000008
#define BIT4_32    0x00000010
#define BIT5_32    0x00000020
#define BIT6_32    0x00000040
#define BIT7_32    0x00000080
#define BIT8_32    0x00000100
#define BIT9_32    0x00000200
#define BIT10_32   0x00000400
#define BIT11_32   0x00000800
#define BIT12_32   0x00001000
#define BIT13_32   0x00002000
#define BIT14_32   0x00004000
#define BIT15_32   0x00008000
#define BIT16_32   0x00010000
#define BIT17_32   0x00020000
#define BIT18_32   0x00040000
#define BIT19_32   0x00080000
#define BIT20_32   0x00100000
#define BIT21_32   0x00200000
#define BIT22_32   0x00400000
#define BIT23_32   0x00800000
#define BIT24_32   0x01000000
#define BIT25_32   0x02000000
#define BIT26_32   0x04000000
#define BIT27_32   0x08000000
#define BIT28_32   0x10000000
#define BIT29_32   0x20000000
#define BIT30_32   0x40000000
#define BIT31_32   0x80000000
#define _BIT0_32   0xfffffffe
#define _BIT1_32   0xfffffffd
#define _BIT2_32   0xfffffffb
#define _BIT3_32   0xfffffff7
#define _BIT4_32   0xffffffef
#define _BIT5_32   0xffffffdf
#define _BIT6_32   0xffffffbf
#define _BIT7_32   0xffffff7f
#define _BIT8_32   0xfffffeff
#define _BIT9_32   0xfffffdff
#define _BIT10_32  0xfffffbff
#define _BIT11_32  0xfffff7ff
#define _BIT12_32  0xffffefff
#define _BIT13_32  0xffffdfff
#define _BIT14_32  0xffffbfff
#define _BIT15_32  0xffff7fff
#define _BIT16_32  0xfffeffff
#define _BIT17_32  0xfffdffff
#define _BIT18_32  0xfffbffff
#define _BIT19_32  0xfff7ffff
#define _BIT20_32  0xffefffff
#define _BIT21_32  0xffdfffff
#define _BIT22_32  0xffbfffff
#define _BIT23_32  0xff7fffff
#define _BIT24_32  0xfeffffff
#define _BIT25_32  0xfdffffff
#define _BIT26_32  0xfbffffff
#define _BIT27_32  0xf7ffffff
#define _BIT28_32  0xefffffff
#define _BIT29_32  0xdfffffff
#define _BIT30_32  0xbfffffff
#define _BIT31_32  0x7fffffff
//================  16bits Data bit set =================
#define SetBit0_16(a)   a|=BIT0_16
#define SetBit1_16(a)   a|=BIT1_16
#define SetBit2_16(a)   a|=BIT2_16
#define SetBit3_16(a)   a|=BIT3_16
#define SetBit4_16(a)   a|=BIT4_16
#define SetBit5_16(a)   a|=BIT5_16
#define SetBit6_16(a)   a|=BIT6_16
#define SetBit7_16(a)   a|=BIT7_16
#define SetBit8_16(a)   a|=BIT8_16
#define SetBit9_16(a)   a|=BIT9_16
#define SetBit10_16(a)  a|=BIT10_16
#define SetBit11_16(a)  a|=BIT11_16
#define SetBit12_16(a)  a|=BIT12_16
#define SetBit13_16(a)  a|=BIT13_16
#define SetBit14_16(a)  a|=BIT14_16
#define SetBit15_16(a)  a|=BIT15_16
//================  16bits Data bit clr =================
#define ClrBit0_16(a)   a&=_BIT0_16
#define ClrBit1_16(a)   a&=_BIT1_16
#define ClrBit2_16(a)   a&=_BIT2_16
#define ClrBit3_16(a)   a&=_BIT3_16
#define ClrBit4_16(a)   a&=_BIT4_16
#define ClrBit5_16(a)   a&=_BIT5_16
#define ClrBit6_16(a)   a&=_BIT6_16
#define ClrBit7_16(a)   a&=_BIT7_16
#define ClrBit8_16(a)   a&=_BIT8_16
#define ClrBit9_16(a)   a&=_BIT9_16
#define ClrBit10_16(a)  a&=_BIT10_16
#define ClrBit11_16(a)  a&=_BIT11_16
#define ClrBit12_16(a)  a&=_BIT12_16
#define ClrBit13_16(a)  a&=_BIT13_16
#define ClrBit14_16(a)  a&=_BIT14_16
#define ClrBit15_16(a)  a&=_BIT15_16
//================  16bits Data bit cpl =================
#define CplBit0_16(a)   a^=BIT0_16
#define CplBit1_16(a)   a^=BIT1_16
#define CplBit2_16(a)   a^=BIT2_16
#define CplBit3_16(a)   a^=BIT3_16
#define CplBit4_16(a)   a^=BIT4_16
#define CplBit5_16(a)   a^=BIT5_16
#define CplBit6_16(a)   a^=BIT6_16
#define CplBit7_16(a)   a^=BIT7_16
#define CplBit8_16(a)   a^=BIT8_16
#define CplBit9_16(a)   a^=BIT9_16
#define CplBit10_16(a)  a^=BIT10_16
#define CplBit11_16(a)  a^=BIT11_16
#define CplBit12_16(a)  a^=BIT12_16
#define CplBit13_16(a)  a^=BIT13_16
#define CplBit14_16(a)  a^=BIT14_16
#define CplBit15_16(a)  a^=BIT15_16
//========== 16bits Data bit if ==============
#define ifBit0_16(a)   ((a)&BIT0_16)
#define ifBit1_16(a)   ((a)&BIT1_16)
#define ifBit2_16(a)   ((a)&BIT2_16)
#define ifBit3_16(a)   ((a)&BIT3_16)
#define ifBit4_16(a)   ((a)&BIT4_16)
#define ifBit5_16(a)   ((a)&BIT5_16)
#define ifBit6_16(a)   ((a)&BIT6_16)
#define ifBit7_16(a)   ((a)&BIT7_16)
#define ifBit8_16(a)   ((a)&BIT8_16)
#define ifBit9_16(a)   ((a)&BIT9_16)
#define ifBit10_16(a)  ((a)&BIT10_16)
#define ifBit11_16(a)  ((a)&BIT11_16)
#define ifBit12_16(a)  ((a)&BIT12_16)
#define ifBit13_16(a)  ((a)&BIT13_16)
#define ifBit14_16(a)  ((a)&BIT14_16)
#define ifBit15_16(a)  ((a)&BIT15_16)
//================  32bits Data bit set =================
#define SetBit0_32(a)   a|=BIT0_32
#define SetBit1_32(a)   a|=BIT1_32
#define SetBit2_32(a)   a|=BIT2_32
#define SetBit3_32(a)   a|=BIT3_32
#define SetBit4_32(a)   a|=BIT4_32
#define SetBit5_32(a)   a|=BIT5_32
#define SetBit6_32(a)   a|=BIT6_32
#define SetBit7_32(a)   a|=BIT7_32
#define SetBit8_32(a)   a|=BIT8_32
#define SetBit9_32(a)   a|=BIT9_32
#define SetBit10_32(a)  a|=BIT10_32
#define SetBit11_32(a)  a|=BIT11_32
#define SetBit12_32(a)  a|=BIT12_32
#define SetBit13_32(a)  a|=BIT13_32
#define SetBit14_32(a)  a|=BIT14_32
#define SetBit15_32(a)  a|=BIT15_32
#define SetBit16_32(a)  a|=BIT16_32
#define SetBit17_32(a)  a|=BIT17_32
#define SetBit18_32(a)  a|=BIT18_32
#define SetBit19_32(a)  a|=BIT19_32
#define SetBit20_32(a)  a|=BIT20_32
#define SetBit21_32(a)  a|=BIT21_32
#define SetBit22_32(a)  a|=BIT22_32
#define SetBit23_32(a)  a|=BIT23_32
#define SetBit24_32(a)  a|=BIT24_32
#define SetBit25_32(a)  a|=BIT25_32
#define SetBit26_32(a)  a|=BIT26_32
#define SetBit27_32(a)  a|=BIT27_32
#define SetBit28_32(a)  a|=BIT28_32
#define SetBit29_32(a)  a|=BIT29_32
#define SetBit30_32(a)  a|=BIT30_32
#define SetBit31_32(a)  a|=BIT31_32
//================  32bits Data bit clr =================
#define ClrBit0_32(a)   a&=_BIT0_32
#define ClrBit1_32(a)   a&=_BIT1_32
#define ClrBit2_32(a)   a&=_BIT2_32
#define ClrBit3_32(a)   a&=_BIT3_32
#define ClrBit4_32(a)   a&=_BIT4_32
#define ClrBit5_32(a)   a&=_BIT5_32
#define ClrBit6_32(a)   a&=_BIT6_32
#define ClrBit7_32(a)   a&=_BIT7_32
#define ClrBit8_32(a)   a&=_BIT8_32
#define ClrBit9_32(a)   a&=_BIT9_32
#define ClrBit10_32(a)  a&=_BIT10_32
#define ClrBit11_32(a)  a&=_BIT11_32
#define ClrBit12_32(a)  a&=_BIT12_32
#define ClrBit13_32(a)  a&=_BIT13_32
#define ClrBit14_32(a)  a&=_BIT14_32
#define ClrBit15_32(a)  a&=_BIT15_32
#define ClrBit16_32(a)  a&=_BIT16_32
#define ClrBit17_32(a)  a&=_BIT17_32
#define ClrBit18_32(a)  a&=_BIT18_32
#define ClrBit19_32(a)  a&=_BIT19_32
#define ClrBit20_32(a)  a&=_BIT20_32
#define ClrBit21_32(a)  a&=_BIT21_32
#define ClrBit22_32(a)  a&=_BIT22_32
#define ClrBit23_32(a)  a&=_BIT23_32
#define ClrBit24_32(a)  a&=_BIT24_32
#define ClrBit25_32(a)  a&=_BIT25_32
#define ClrBit26_32(a)  a&=_BIT26_32
#define ClrBit27_32(a)  a&=_BIT27_32
#define ClrBit28_32(a)  a&=_BIT28_32
#define ClrBit29_32(a)  a&=_BIT29_32
#define ClrBit30_32(a)  a&=_BIT30_32
#define ClrBit31_32(a)  a&=_BIT31_32
//================  32bits Data bit Cpl =================
#define CplBit0_32(a)   a^=BIT0_32
#define CplBit1_32(a)   a^=BIT1_32
#define CplBit2_32(a)   a^=BIT2_32
#define CplBit3_32(a)   a^=BIT3_32
#define CplBit4_32(a)   a^=BIT4_32
#define CplBit5_32(a)   a^=BIT5_32
#define CplBit6_32(a)   a^=BIT6_32
#define CplBit7_32(a)   a^=BIT7_32
#define CplBit8_32(a)   a^=BIT8_32
#define CplBit9_32(a)   a^=BIT9_32
#define CplBit10_32(a)  a^=BIT10_32
#define CplBit11_32(a)  a^=BIT11_32
#define CplBit12_32(a)  a^=BIT12_32
#define CplBit13_32(a)  a^=BIT13_32
#define CplBit14_32(a)  a^=BIT14_32
#define CplBit15_32(a)  a^=BIT15_32
#define CplBit16_32(a)  a^=BIT16_32
#define CplBit17_32(a)  a^=BIT17_32
#define CplBit18_32(a)  a^=BIT18_32
#define CplBit19_32(a)  a^=BIT19_32
#define CplBit20_32(a)  a^=BIT20_32
#define CplBit21_32(a)  a^=BIT21_32
#define CplBit22_32(a)  a^=BIT22_32
#define CplBit23_32(a)  a^=BIT23_32
#define CplBit24_32(a)  a^=BIT24_32
#define CplBit25_32(a)  a^=BIT25_32
#define CplBit26_32(a)  a^=BIT26_32
#define CplBit27_32(a)  a^=BIT27_32
#define CplBit28_32(a)  a^=BIT28_32
#define CplBit29_32(a)  a^=BIT29_32
#define CplBit30_32(a)  a^=BIT30_32
#define CplBit31_32(a)  a^=BIT31_32
//================  32bits Data bit if =================
#define ifBit0_32(a)   ((a)&BIT0_32)
#define ifBit1_32(a)   ((a)&BIT1_32)
#define ifBit2_32(a)   ((a)&BIT2_32)
#define ifBit3_32(a)   ((a)&BIT3_32)
#define ifBit4_32(a)   ((a)&BIT4_32)
#define ifBit5_32(a)   ((a)&BIT5_32)
#define ifBit6_32(a)   ((a)&BIT6_32)
#define ifBit7_32(a)   ((a)&BIT7_32)
#define ifBit8_32(a)   ((a)&BIT8_32)
#define ifBit9_32(a)   ((a)&BIT9_32)
#define ifBit10_32(a)  ((a)&BIT10_32)
#define ifBit11_32(a)  ((a)&BIT11_32)
#define ifBit12_32(a)  ((a)&BIT12_32)
#define ifBit13_32(a)  ((a)&BIT13_32)
#define ifBit14_32(a)  ((a)&BIT14_32)
#define ifBit15_32(a)  ((a)&BIT15_32)
#define ifBit16_32(a)  ((a)&BIT16_32)
#define ifBit17_32(a)  ((a)&BIT17_32)
#define ifBit18_32(a)  ((a)&BIT18_32)
#define ifBit19_32(a)  ((a)&BIT19_32)
#define ifBit20_32(a)  ((a)&BIT20_32)
#define ifBit21_32(a)  ((a)&BIT21_32)
#define ifBit22_32(a)  ((a)&BIT22_32)
#define ifBit23_32(a)  ((a)&BIT23_32)
#define ifBit24_32(a)  ((a)&BIT24_32)
#define ifBit25_32(a)  ((a)&BIT25_32)
#define ifBit26_32(a)  ((a)&BIT26_32)
#define ifBit27_32(a)  ((a)&BIT27_32)
#define ifBit28_32(a)  ((a)&BIT28_32)
#define ifBit29_32(a)  ((a)&BIT29_32)
#define ifBit30_32(a)  ((a)&BIT30_32)
#define ifBit31_32(a)  ((a)&BIT31_32)
//--------------------------------------
/*字节定义*/
	typedef struct {
#ifdef __BIG_ENDIAN
		INT32U bit07 : 1;
		INT32U bit06 : 1;
		INT32U bit05 : 1;
		INT32U bit04 : 1;
		INT32U bit03 : 1;
		INT32U bit02 : 1;
		INT32U bit01 : 1;
		INT32U bit00 : 1;
#else
		INT32U bit00 : 1;
		INT32U bit01 : 1;
		INT32U bit02 : 1;
		INT32U bit03 : 1;
		INT32U bit04 : 1;
		INT32U bit05 : 1;
		INT32U bit06 : 1;
		INT32U bit07 : 1;
#endif
	}Bit8Struct;
	typedef union MMemBit8 {
		Bit8Struct bit;
		INT8U cValue;
		INT8S sValue;
	}MMEMBIT8;
	/*单字定义*/
	typedef struct {
#ifdef __BIG_ENDIAN
		INT32U bit15 : 1;
		INT32U bit14 : 1;
		INT32U bit13 : 1;
		INT32U bit12 : 1;
		INT32U bit11 : 1;
		INT32U bit10 : 1;
		INT32U bit09 : 1;
		INT32U bit08 : 1;
		INT32U bit07 : 1;
		INT32U bit06 : 1;
		INT32U bit05 : 1;
		INT32U bit04 : 1;
		INT32U bit03 : 1;
		INT32U bit02 : 1;
		INT32U bit01 : 1;
		INT32U bit00 : 1;
#else
		INT32U bit00 : 1;
		INT32U bit01 : 1;
		INT32U bit02 : 1;
		INT32U bit03 : 1;
		INT32U bit04 : 1;
		INT32U bit05 : 1;
		INT32U bit06 : 1;
		INT32U bit07 : 1;
		INT32U bit08 : 1;
		INT32U bit09 : 1;
		INT32U bit10 : 1;
		INT32U bit11 : 1;
		INT32U bit12 : 1;
		INT32U bit13 : 1;
		INT32U bit14 : 1;
		INT32U bit15 : 1;
#endif
	}Bit16Struct;
	typedef union MMemBit16 {
		Bit16Struct bit;
		INT8U  cValue[2];
		INT16U wValue;
		INT16S sValue;

	}MMEMBIT16;
	/*双字定义*/
	typedef struct {
#ifdef __BIG_ENDIAN
		INT32U bit31 : 1;
		INT32U bit30 : 1;
		INT32U bit29 : 1;
		INT32U bit28 : 1;
		INT32U bit27 : 1;
		INT32U bit26 : 1;
		INT32U bit25 : 1;
		INT32U bit24 : 1;
		INT32U bit23 : 1;
		INT32U bit22 : 1;
		INT32U bit21 : 1;
		INT32U bit20 : 1;
		INT32U bit19 : 1;
		INT32U bit18 : 1;
		INT32U bit17 : 1;
		INT32U bit16 : 1;
		INT32U bit15 : 1;
		INT32U bit14 : 1;
		INT32U bit13 : 1;
		INT32U bit12 : 1;
		INT32U bit11 : 1;
		INT32U bit10 : 1;
		INT32U bit09 : 1;
		INT32U bit08 : 1;
		INT32U bit07 : 1;
		INT32U bit06 : 1;
		INT32U bit05 : 1;
		INT32U bit04 : 1;
		INT32U bit03 : 1;
		INT32U bit02 : 1;
		INT32U bit01 : 1;
		INT32U bit00 : 1;
#else
		INT32U bit00 : 1;
		INT32U bit01 : 1;
		INT32U bit02 : 1;
		INT32U bit03 : 1;
		INT32U bit04 : 1;
		INT32U bit05 : 1;
		INT32U bit06 : 1;
		INT32U bit07 : 1;
		INT32U bit08 : 1;
		INT32U bit09 : 1;
		INT32U bit10 : 1;
		INT32U bit11 : 1;
		INT32U bit12 : 1;
		INT32U bit13 : 1;
		INT32U bit14 : 1;
		INT32U bit15 : 1;
		INT32U bit16 : 1;
		INT32U bit17 : 1;
		INT32U bit18 : 1;
		INT32U bit19 : 1;
		INT32U bit20 : 1;
		INT32U bit21 : 1;
		INT32U bit22 : 1;
		INT32U bit23 : 1;
		INT32U bit24 : 1;
		INT32U bit25 : 1;
		INT32U bit26 : 1;
		INT32U bit27 : 1;
		INT32U bit28 : 1;
		INT32U bit29 : 1;
		INT32U bit30 : 1;
		INT32U bit31 : 1;
#endif
	}Bit32Struct;
	typedef union MMemBit32 {
		Bit32Struct bit;
		INT8U   cValue[4];
		INT16U wfValue[2];
		INT32U  dwValue;
		INT32S dsValue;
		FLOAT32 fValue;
	}MMEMBIT32;
	/*双字半定义*/
	typedef struct {
#ifdef __BIG_ENDIAN
		INT32U bit39 : 1;
		INT32U bit38 : 1;
		INT32U bit37 : 1;
		INT32U bit36 : 1;
		INT32U bit35 : 1;
		INT32U bit34 : 1;
		INT32U bit33 : 1;
		INT32U bit32 : 1;
		INT32U bit31 : 1;
		INT32U bit30 : 1;
		INT32U bit29 : 1;
		INT32U bit28 : 1;
		INT32U bit27 : 1;
		INT32U bit26 : 1;
		INT32U bit25 : 1;
		INT32U bit24 : 1;
		INT32U bit23 : 1;
		INT32U bit22 : 1;
		INT32U bit21 : 1;
		INT32U bit20 : 1;
		INT32U bit19 : 1;
		INT32U bit18 : 1;
		INT32U bit17 : 1;
		INT32U bit16 : 1;
		INT32U bit15 : 1;
		INT32U bit14 : 1;
		INT32U bit13 : 1;
		INT32U bit12 : 1;
		INT32U bit11 : 1;
		INT32U bit10 : 1;
		INT32U bit09 : 1;
		INT32U bit08 : 1;
		INT32U bit07 : 1;
		INT32U bit06 : 1;
		INT32U bit05 : 1;
		INT32U bit04 : 1;
		INT32U bit03 : 1;
		INT32U bit02 : 1;
		INT32U bit01 : 1;
		INT32U bit00 : 1;
#else
		INT32U bit00 : 1;
		INT32U bit01 : 1;
		INT32U bit02 : 1;
		INT32U bit03 : 1;
		INT32U bit04 : 1;
		INT32U bit05 : 1;
		INT32U bit06 : 1;
		INT32U bit07 : 1;
		INT32U bit08 : 1;
		INT32U bit09 : 1;
		INT32U bit10 : 1;
		INT32U bit11 : 1;
		INT32U bit12 : 1;
		INT32U bit13 : 1;
		INT32U bit14 : 1;
		INT32U bit15 : 1;
		INT32U bit16 : 1;
		INT32U bit17 : 1;
		INT32U bit18 : 1;
		INT32U bit19 : 1;
		INT32U bit20 : 1;
		INT32U bit21 : 1;
		INT32U bit22 : 1;
		INT32U bit23 : 1;
		INT32U bit24 : 1;
		INT32U bit25 : 1;
		INT32U bit26 : 1;
		INT32U bit27 : 1;
		INT32U bit28 : 1;
		INT32U bit29 : 1;
		INT32U bit30 : 1;
		INT32U bit31 : 1;
		INT32U bit32 : 1;
		INT32U bit33 : 1;
		INT32U bit34 : 1;
		INT32U bit35 : 1;
		INT32U bit36 : 1;
		INT32U bit37 : 1;
		INT32U bit38 : 1;
		INT32U bit39 : 1;
#endif
	}Bit40Struct;
	typedef union MMemBit40 {
		Bit40Struct bit;
		INT40U twValue;
		INT40S tsValue;
	}MMEMBIT40;
	/*四字定义*/
	typedef struct {
#ifdef __BIG_ENDIAN
		INT32U bit63 : 1;
		INT32U bit62 : 1;
		INT32U bit61 : 1;
		INT32U bit60 : 1;
		INT32U bit59 : 1;
		INT32U bit58 : 1;
		INT32U bit57 : 1;
		INT32U bit56 : 1;
		INT32U bit55 : 1;
		INT32U bit54 : 1;
		INT32U bit53 : 1;
		INT32U bit52 : 1;
		INT32U bit51 : 1;
		INT32U bit50 : 1;
		INT32U bit49 : 1;
		INT32U bit48 : 1;
		INT32U bit47 : 1;
		INT32U bit46 : 1;
		INT32U bit45 : 1;
		INT32U bit44 : 1;
		INT32U bit43 : 1;
		INT32U bit42 : 1;
		INT32U bit41 : 1;
		INT32U bit40 : 1;
		INT32U bit39 : 1;
		INT32U bit38 : 1;
		INT32U bit37 : 1;
		INT32U bit36 : 1;
		INT32U bit35 : 1;
		INT32U bit34 : 1;
		INT32U bit33 : 1;
		INT32U bit32 : 1;
		INT32U bit31 : 1;
		INT32U bit30 : 1;
		INT32U bit29 : 1;
		INT32U bit28 : 1;
		INT32U bit27 : 1;
		INT32U bit26 : 1;
		INT32U bit25 : 1;
		INT32U bit24 : 1;
		INT32U bit23 : 1;
		INT32U bit22 : 1;
		INT32U bit21 : 1;
		INT32U bit20 : 1;
		INT32U bit19 : 1;
		INT32U bit18 : 1;
		INT32U bit17 : 1;
		INT32U bit16 : 1;
		INT32U bit15 : 1;
		INT32U bit14 : 1;
		INT32U bit13 : 1;
		INT32U bit12 : 1;
		INT32U bit11 : 1;
		INT32U bit10 : 1;
		INT32U bit09 : 1;
		INT32U bit08 : 1;
		INT32U bit07 : 1;
		INT32U bit06 : 1;
		INT32U bit05 : 1;
		INT32U bit04 : 1;
		INT32U bit03 : 1;
		INT32U bit02 : 1;
		INT32U bit01 : 1;
		INT32U bit00 : 1;
#else
		INT32U bit00 : 1;
		INT32U bit01 : 1;
		INT32U bit02 : 1;
		INT32U bit03 : 1;
		INT32U bit04 : 1;
		INT32U bit05 : 1;
		INT32U bit06 : 1;
		INT32U bit07 : 1;
		INT32U bit08 : 1;
		INT32U bit09 : 1;
		INT32U bit10 : 1;
		INT32U bit11 : 1;
		INT32U bit12 : 1;
		INT32U bit13 : 1;
		INT32U bit14 : 1;
		INT32U bit15 : 1;
		INT32U bit16 : 1;
		INT32U bit17 : 1;
		INT32U bit18 : 1;
		INT32U bit19 : 1;
		INT32U bit20 : 1;
		INT32U bit21 : 1;
		INT32U bit22 : 1;
		INT32U bit23 : 1;
		INT32U bit24 : 1;
		INT32U bit25 : 1;
		INT32U bit26 : 1;
		INT32U bit27 : 1;
		INT32U bit28 : 1;
		INT32U bit29 : 1;
		INT32U bit30 : 1;
		INT32U bit31 : 1;
		INT32U bit32 : 1;
		INT32U bit33 : 1;
		INT32U bit34 : 1;
		INT32U bit35 : 1;
		INT32U bit36 : 1;
		INT32U bit37 : 1;
		INT32U bit38 : 1;
		INT32U bit39 : 1;
		INT32U bit40 : 1;
		INT32U bit41 : 1;
		INT32U bit42 : 1;
		INT32U bit43 : 1;
		INT32U bit44 : 1;
		INT32U bit45 : 1;
		INT32U bit46 : 1;
		INT32U bit47 : 1;
		INT32U bit48 : 1;
		INT32U bit49 : 1;
		INT32U bit50 : 1;
		INT32U bit51 : 1;
		INT32U bit52 : 1;
		INT32U bit53 : 1;
		INT32U bit54 : 1;
		INT32U bit55 : 1;
		INT32U bit56 : 1;
		INT32U bit57 : 1;
		INT32U bit58 : 1;
		INT32U bit59 : 1;
		INT32U bit60 : 1;
		INT32U bit61 : 1;
		INT32U bit62 : 1;
		INT32U bit63 : 1;
#endif
	}Bit64Struct;
	typedef union MMemBit64 {

		Bit64Struct bit;
		INT8U   cValue[8];
		INT16U  cfValue[4];
		INT32U  dwValue[2];
		INT64U fwValue;
		INT64S fsValue;
		FLOAT64 dfValue;
		DOUBLE64 ddValue;

	}MMEMBIT64;

#ifdef __cplusplus
}
#endif
#endif
/******************************************************************************\
* End of MotionDataType.h
\******************************************************************************/
