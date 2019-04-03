// Object3DCtrlZK.h: interface for the CObject3DCtrlZK class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT3DCTRLZK_H__E15A07E3_A2AB_42E2_BD6B_BA5FC78534A9__INCLUDED_)
#define AFX_OBJECT3DCTRLZK_H__E15A07E3_A2AB_42E2_BD6B_BA5FC78534A9__INCLUDED_

#include "NuroDefine.h"

//// 3 / 4, 1 / 2
#define DYDS 3 / 4

//// 2, 4
#define SCALExN 2

class CObject3DCtrlZK  
{
public:
	CObject3DCtrlZK();
	virtual ~CObject3DCtrlZK();
	
	nuBOOL SetUp3D(nuINT nSW = 480, nuINT nSH = 272, nuINT nDy = 240, nuINT nDz = 10, nuINT nViewX = -1, nuINT nViewY = -1, nuINT nViewDis = 10);
	nuBOOL Screen2Dto3D(nuLONG& x, nuLONG& y, nuLONG& z);
	nuBOOL Screen3Dto2D(nuLONG& x, nuLONG& y, nuLONG& z);

	nuLONG Get3DThick(nuLONG nThick, nuLONG y);
	
public:
	nuINT		m_nVDy, m_nVDz;//���ӵ���ͶӰƽ��ƽ�е�ƽ����Y��Z��Ľ���
	nuINT		m_nTopY;//z = m_nViewZ ƽ����ͶӰƽ��Ľ���Yֵ�������ֵ�����棬������ͶӰ���ݣ�
	nuINT		m_nYmax;//y����������ֵ���任�������ᳬ����Ļ�ķ�Χ
	nuINT		m_nSkyH;
//protected:
	nuINT		m_nDy;
	nuINT		m_nDz;
	nuINT		m_nScreenH;
	nuINT		m_nScreenW;
	nuINT		m_nViewX;
	nuINT		m_nViewY;
	nuINT		m_nViewZ;
	nuINT		m_nScaleN;
	nuINT		m_nScaleC;
	nuINT		m_nScaleD;//m_nScaleN = m_nScaleD + m_nScaleC;
	nuBOOL  	m_bScale;

};

#endif // !defined(AFX_OBJECT3DCTRLZK_H__E15A07E3_A2AB_42E2_BD6B_BA5FC78534A9__INCLUDED_)
