
#include "AllSystemDataBase.h"

UONERDwCtrl		*g_pDB_DwCtrl = NULL;
UONEBHCtrl		*g_pUOneBH	  = NULL;

UONERtBCtrl		*g_pLocalRtB[2] = {NULL};//�_�W�IRTBlock����ƼȦs��
UONERtBCtrl		*g_pRtB_F		= NULL;
UONERtBCtrl		*g_pRtB_T		= NULL;
CDontToHere		*g_pCDTH		= NULL;
CRoutingDataCtrl*g_pCRDC		= NULL;

//CDontToHere		m_CDTH;
//CRoutingDataCtrl	m_CRDC;

MapIDtoMapIdx	m_MapIDtoMapIdx = {0};//MapID�PMapIdx�������Ȧs��

nuBOOL CheckPtCloseLU(NUROPOINT Pt1, NUROPOINT Pt2, nuLONG CloseLen)
{
	if(	Pt1.x-Pt2.x<CloseLen &&
		Pt2.x-Pt1.x<CloseLen &&
		Pt1.y-Pt2.y<CloseLen &&
		Pt2.y-Pt1.y<CloseLen )
	{
		return nuTRUE;
	}
	else
	{
		return nuFALSE;
	}
}
