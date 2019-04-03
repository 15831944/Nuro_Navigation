// Ctrl_3dp.h: interface for the CCtrl_3dp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRL_3DP_H__6D7EC155_419E_4700_9FBA_97479F88B9DB__INCLUDED_)
#define AFX_CTRL_3DP_H__6D7EC155_419E_4700_9FBA_97479F88B9DB__INCLUDED_

#include "NuroDefine.h"

typedef struct Tag_StruMain3dp//�T�w�����Y
{
	NUROPOINT	FCoor;//�_�I�y��
	NUROPOINT	NCoor;//�����I�y��
	NUROPOINT	TCoor;//���I�y��
	nuLONG	    JpgName;//���ɦW��
}StruMain3dp,*pStruMain3dp;

typedef struct Tag_Stru3dp//�T�w�����Y
{
	nuULONG     TotalCnt;//�`��
	StruMain3dp **p_M3dp;
}Stru3dp,*pStru3dp;

class CCtrl_3dp : Stru3dp
{
	public:
		CCtrl_3dp();
		virtual ~CCtrl_3dp();
		nuTCHAR	FName[NURO_MAX_PATH];
		nuFILE	*f3dp;

		nuBOOL InitClass();
		nuVOID CloseClass();

		nuBOOL ReadFile();
		nuVOID ReleaseFile();
		nuLONG CheckFNTCoor(NUROPOINT FCoor, NUROPOINT NCoor, NUROPOINT TCoor);
	#ifdef _DEBUG
		nuINT  PicAlocCount;
		nuINT  PicFreeCount;
	#endif
	private:
		nuVOID	InitConst();
};

#endif // !defined(AFX_CTRL_3DP_H__6D7EC155_419E_4700_9FBA_97479F88B9DB__INCLUDED_)
