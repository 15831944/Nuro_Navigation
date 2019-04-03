// NuroBmpZK.h: interface for the CNuroBmpZK class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NUROBMPZK_H__FD36C3A3_B566_492E_A988_5D28BC09D369__INCLUDED_)
#define AFX_NUROBMPZK_H__FD36C3A3_B566_492E_A988_5D28BC09D369__INCLUDED_

#include "../NuroDefine.h"

class CNuroBmpZK  
{
public:

#ifdef NURO_OS_WINDOWS
#pragma pack(push) 
#pragma pack(1)
#endif
    
    __ATTRIBUTE_PRE struct nutagBITMAPFILEHEADER {
        nuWORD		bfType;  /* λͼ���ļ����� BM */
        nuDWORD	    bfSize;  /* λͼ�ļ��Ĵ�С */
        nuWORD		bfReserved1;
        nuWORD		bfReserved2;
        nuDWORD	bfOffBits;   /* λͼ���ݵ���ʼλ�� */
    }__ATTRIBUTE_PACKED__;
    typedef struct nutagBITMAPFILEHEADER NURO_BITMAPFILEHEADER;
    
    __ATTRIBUTE_PRE struct nutagBITMAPINFOHEADER{
        nuDWORD	    biSize;      /* ���ṹ��ռ���ֽ��� */
        nuINT		biWidth;     /* λͼ���  */
        nuINT		biHeight;    /* λͼ�߶� */
        nuWORD		biPlanes;    /* Ŀ���豸�ļ��� */
        nuWORD		biBitCount;  /* ÿ��������ռ�õ�λ�� 1(˫ɫ) 4(16ɫ) 8(256) 24(���)*/
        nuDWORD	biCompression;   /* λͼѹ������ 0 1 2 ֮һ */
        nuDWORD	biSizeImage;     /* λͼ�Ĵ�С�����ֽ�Ϊ��λ */
        nuINT		biXPelsPerMeter;  /* λͼˮƽ�ֱ��� */
        nuINT		biYPelsPerMeter;  /* λͼ��ֱ�ֱ��� */
        nuDWORD	biClrUsed;           /* ʵ��ʹ�õ���ɫ���е���ɫ�� */
        nuDWORD	biClrImportant;      /* λͼ��ʾ�й����е���Ҫ��ɫ�� */
    }__ATTRIBUTE_PACKED__;
    typedef struct nutagBITMAPINFOHEADER NURO_BITMAPINFOHEADER;
    
    __ATTRIBUTE_PRE struct nutagRGBQUAD {
        nuBYTE    rgbBlue;    /* ��ɫ������ */
        nuBYTE    rgbGreen;   /* ��ɫ������ */
        nuBYTE    rgbRed;     /* ��ɫ������ */
        nuBYTE    rgbReserved; /* ����������Ϊ0 */
    }__ATTRIBUTE_PACKED__;
    typedef struct nutagRGBQUAD NURO_RGBQUAD;
    
    struct nutagBITMAPINFO {
        NURO_BITMAPINFOHEADER	bmiHeader;   /* λͼ��Ϣͷ */
        NURO_RGBQUAD			bmiColors[1]; /* λͼ��ɫ�� */
    }__ATTRIBUTE_PACKED__;
    typedef struct nutagBITMAPINFO NURO_BITMAPINFO; /* λͼ��Ϣ */
    
    
	/* һ��ɨ������ռ�õ��ֽ�����������4�ı���,����Ĳ��� */
#ifdef NURO_OS_WINDOWS
#pragma pack(pop) 
#endif

public:
	CNuroBmpZK();
	virtual ~CNuroBmpZK();

    nuBOOL LoadNuroBmp(const nuCHAR* ptsBmpName);
    nuBOOL LoadNuroBmp(const nuWCHAR* ptsBmpName);
	nuBOOL CreateNuroBmp(const nuWCHAR* ptsBmpName,nuLONG With,nuLONG High);
    nuVOID FreeNuroBmp();

public:
    NURO_BMP    m_bmp;
};

#endif // !defined(AFX_NUROBMPZK_H__FD36C3A3_B566_492E_A988_5D28BC09D369__INCLUDED_)
