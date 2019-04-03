#ifndef DEF_CPNGCTRL_LOUIS
	#define DEF_CPNGCTRL_LOUIS

	#include "NuroClasses.h"

	#define USEPNG

	#define PNG_DRAWMODE_LT			0x00//�HPNG���W����ø�ϭ��I(���k�U���e)	<�@��e�ϱ`�Φ��k>
	#define PNG_DRAWMODE_LC			0x01//�HPNG���䤤����ø�ϭ��I(���k�e)
	#define PNG_DRAWMODE_LB			0x02//�HPNG���U����ø�ϭ��I(���k�W���e)
	#define PNG_DRAWMODE_CT			0x03//�HPNG�W�䤤����ø�ϭ��I(���U�e)
	#define PNG_DRAWMODE_CC			0x04//�HPNG������ø�ϭ��I				<2D POI�`�Φ��k>
	#define PNG_DRAWMODE_CB			0x05//�HPNG�U�䤤����ø�ϭ��I(���W�e)	<3D POI�`�Φ��k>
	#define PNG_DRAWMODE_RT			0x06//�HPNG�k�W����ø�ϭ��I(�����U���e)	
	#define PNG_DRAWMODE_RC			0x07//�HPNG�k�䤤����ø�ϭ��I(�����e)
	#define PNG_DRAWMODE_RB			0x08//�HPNG���U����ø�ϭ��I(���k�W���e)

	#define MEMDCCOLORTYPE_16_565	0x00//16�줸�� RGBA�t�m��5650
	#define MEMDCCOLORTYPE_24_888	0x01//24�줸�� RGBA�t�m��8880
	#define MEMDCCOLORTYPE_32_8888	0x02//32�줸�� RGBA�t�m��8888

	#define nuGet565BValue(rgb)     ( (unsigned int)((rgb)&0x001f) )
	#define nuGet565GValue(rgb)     ( (unsigned int)((rgb)&0x07D0)>>5 ) 
	#define nuGet565RValue(rgb)     ( (unsigned int)((rgb))>>11 )
//	#define nu565RGB(r,g,b)          ((nuCOLORREF)(((nuBYTE)(r)>>3|((nuWORD)(((nuBYTE)(g))>>2)<<5))|(((nuDWORD)(nuBYTE)(b)>>3)<<11)))
	#define nu565RGB(r,g,b)          ((nuCOLORREF)(((nuBYTE)(b)|((nuWORD)(((nuBYTE)(g)))<<5))|(((nuDWORD)(nuBYTE)(r))<<11)))

	#define PNG_BYTES_TO_CHECK 4
	
	//#ifdef ANDROID
 #if (defined ANDROID) || (defined NURO_OS_LINUX)
	#define GetRValue(rgb)      (nuLOBYTE(rgb))
	#define GetGValue(rgb)      (nuLOBYTE(((nuWORD)(rgb)) >> 8))
	#define GetBValue(rgb)      (nuLOBYTE((rgb)>>16))
	#define RGB(r,g,b)          ((nuCOLORREF)(((nuBYTE)(r)|((nuWORD)((nuBYTE)(g))<<8))|(((nuDWORD)(nuBYTE)(b))<<16)))
	#endif

	class CPngCtrlLU   
	{
		public:
			CPngCtrlLU();
			virtual ~CPngCtrlLU();

			//PNG File Control
			nuBOOL	InitPngCtrl(nuINT PngBufferCount);//��l��PNG Ctrl���Ҧ����e
			nuVOID	RelPngCtrl();//�Ѻc�O����

			nuINT		check_if_png(nuTCHAR *file_name, nuFILE **fp);
			nuBOOL	load_png(nuTCHAR *file_name,nuINT &PngIndex,nuINT PngID);//PngID�i�H�ΨӶi����w�j�M,���ϥΪ��ܪ�����-1�Y�i
			nuBOOL	Clean_Png(nuINT PngIndex,nuBOOL bCleanAll);
			nuVOID	Draw_PNG_EX(nuINT PngIndex,nuBYTE *MemBuffer,NURORECT Targetrect,nuINT DrawX,nuINT DrawY,nuINT PNGDrawMode);
			nuVOID	Draw_PNG(nuINT PngIndex,nuBYTE *MemBuffer,NURORECT Targetrect,nuINT DrawX,nuINT DrawY);
			nuVOID	SetMemDCColorType(nuINT ColorType);
			nuBOOL	Get_PngData_idx(nuINT PngIndex,PPNGCTRLSTRU &p_png);//���o��ƪ��覡 �ϥ�index
			nuBOOL	Get_PngData_id(nuINT PngID,PPNGCTRLSTRU &p_png);//���o��ƪ��覡 �ϥ�ID
			nuVOID	Draw_PNG_EX2(PPNGCTRLSTRU p_png,nuBYTE *MemBuffer,NURORECT Targetrect,nuINT DrawX,nuINT DrawY,nuINT PNGDrawMode);
		public:
			PNGCTRLSTRU *pBufferPng;
			nuINT nBufferPngCount;
			nuBOOL bInitPngCtrl;
			nuINT nMemDCColorType;
		private:
			nuBOOL	nuPtInRect(nuINT x,nuINT y, NURORECT rect);

	};

#endif