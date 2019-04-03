// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/21 08:03:44 $
// $Revision: 1.3 $
#ifndef Def_ClassThrCtrl
	#define Def_ClassThrCtrl

	#include	"ConstSet.h"
	#include	"Stru_StateStru.h"
	#include	"NuroDefine.h"

	typedef struct Tag_F_Thr_Header_Stru
	{
		nuULONG TotalNodeCount;//�`Node��
		nuULONG RtConnectStruCount;//�`�s����
		nuLONG RtConnectStruStartAddr;//�s�����c�_�l��m
	}F_Thr_Header_Stru,*pF_Thr_Header_Stru;

	typedef struct Tag_F_Thr_MainData_Stru
	{
		nuULONG FNodeID : 20;//�_�lNodeID
		nuULONG FRtBID : 12;
		nuULONG ConnectStruIndex : 22;//�s����Ư��ޭ�
		nuULONG ConnectCount : 10;//�s���`��
		NUROPOINT NodeCoor;
	}F_Thr_MainData_Stru,*pF_Thr_MainData_Stru;

	typedef struct Tag_F_Thr_Connect_Stru
	{
		nuULONG TNodeID : 20;//�_�lNodeID
		nuULONG TRtBID : 12;
		nuULONG TMapLayer : 2;
		nuULONG Class : 2;
		nuULONG Length : 28;//�D������
		nuULONG WeightingLength;//�[�v����
	}F_Thr_Connect_Stru,*pF_Thr_Connect_Stru;

	typedef struct Tag_Stru_ThrEachMap
	{
		F_Thr_Header_Stru ThrHeader;//Rt�����Y
		F_Thr_MainData_Stru **ThrMain;//Rt�����D���
		F_Thr_Connect_Stru **ThrConnect;//Rt�����s�����
	}Stru_ThrEachMap,*pStru_ThrEachMap;

	typedef struct Tag_Stru_RTBConnectHeader
	{
		nuUSHORT	RTBID;
		nuUSHORT	RTBConnCount;
	}Stru_RTBConnectHeader,*pStru_RTBConnectHeader;

	typedef struct Tag_Stru_RTBConnect
	{
		Stru_RTBConnectHeader Connheader;
		nuULONG	**ConnnectID;
	}Stru_RTBConnect,*Stru_pRTBConnect;

	typedef struct Tag_Stru_ThrHeader
	{
		nuUSHORT MapID;
		nuUSHORT RTBCount;
	}Stru_ThrHeader,*pStru_ThrHeader;

	typedef struct Tag_Stru_Thr
	{
		Stru_ThrHeader	ThrHeader;
		Stru_RTBConnect	**RTBConnect;
		Stru_ThrEachMap	pThrEachMap;
	}Stru_Thr,*pStru_Thr;

	class Class_ThrCtrl : public Stru_Thr
	{
		public:
			Class_ThrCtrl();
			virtual ~Class_ThrCtrl();

			nuBOOL InitClass(nuLONG mapidx,nuLONG rtrule);
			nuVOID CloseClass();

			nuBOOL	Read_Header();//Ū�����Y���
			nuBOOL	Remove_Header();//�������Y���

			nuBOOL	ReSet();//����Rt��

			nuFILE	*ThrFile;
			nuTCHAR	FName[NURO_MAX_PATH];
		#ifdef _DEBUG
			int  ThrAlocCount;
			int  ThrFreeCount;
		#endif
		private:
			nuVOID	IniConst();

			nuLONG	MapIdx;
			nuLONG	l_RoutingRule;
	};

#endif