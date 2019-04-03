// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: daniel $
// $Date: 2010/10/21 09:54:16 $
// $Revision: 1.5 $
	#ifndef Def_UONERtBCtrl
		#define Def_UONERtBCtrl

		#include	"Stru_StateStru.h"
		#include	"ConstSet.h"
		#include	"NuroDefine.h"

		typedef struct Tag_NUROUSPOINT
		{
			nuUSHORT  x;
			nuUSHORT  y;
		}NUROUSPOINT,*pNUROUSPOINT;

		typedef struct Tag_UONEF_RtB_Header_Stru
		{
			nuULONG  TotalNodeCount;//�`Node��
			nuULONG  TotalRoadCount;//�`Road��
			nuULONG  RtConnectStruCount;//�`�s����
			nuLONG   RtIndexStruStartAddr;//�ҥH��ư_�l��m
			nuLONG   RtConnectStruStartAddr;//�s�����c�_�l��m
		}UONEF_RtB_Header_Stru,*pUONEF_RtB_Header_Stru;

#ifdef VALUE_EMGRT
		typedef struct Tag_UONEF_RtB_MainData_Stru
		{
			nuULONG   FNodeID : 20;//�_�lNodeID
			nuULONG   FRtBID : 12;
			nuULONG   ConnectStruIndex : 20;//�s����Ư��ޭ�
			nuULONG   SPTFlag : 1;    //���t�C��
			nuULONG   PTSFlag  : 1;   //���O��
			nuULONG   ARFlag   : 1;   //�۾F����
			nuULONG   Reverse  : 1;   //�O�d
			nuULONG   ConnectCount : 6;//�s���`��
			nuULONG   NoTurnItem : 1;//���s�Х�
			nuULONG   TrafficLight : 1;//����O
			NUROPOINT NodeCoor;
		}UONEF_RtB_MainData_Stru,*pUONEF_RtB_MainData_Stru;
#else
		typedef struct Tag_UONEF_RtB_MainData_Stru
		{
			nuULONG  FNodeID : 20;//�_�lNodeID
			nuULONG  FRtBID : 12;
			nuULONG  ConnectStruIndex : 20;//�s����Ư��ޭ�
			nuULONG  CoorLVX : 2;
			nuULONG  CoorLVY : 2;
			nuULONG  ConnectCount : 4;//�s���`��
			nuULONG  TrafficLight:1;//����O
			nuULONG  Reverse :1;//�O�d
			nuULONG  NoTurnItem : 1;//���s�Х�
			nuULONG  LaneGuideFlag:1;//���D�T��
			NUROUSPOINT NodeCoor;
		}UONEF_RtB_MainData_Stru,*pUONEF_RtB_MainData_Stru;
#endif

		typedef struct Tag_UONEF_RtB_Connect_Stru
		{
			nuULONG   TNodeID : 20;//�_�lNodeID
			nuULONG   TRtBID : 12;
			nuULONG   RoadLength:16;//�D������
			nuULONG   RoadClass:8;//�D������
			nuULONG   Connecttype : 2;//default:0
			nuULONG   VoiceRoadType : 6;//�y����������
		}UONEF_RtB_Connect_Stru,*pUONEF_RtB_Connect_Stru;

		typedef struct Tag_UONEF_RtB_Index_Stru
		{
			nuUSHORT  BlockIdx;//�D���N�X
			nuUSHORT  RoadIdx;//�D���N�X
			nuULONG   FNodeID : 20;//�_�lNodeID
			nuULONG   FRtBID : 12;
			nuULONG   TNodeID : 20;//�_�lNodeID
			nuULONG   TRtBID : 12;
		}UONEF_RtB_Index_Stru,*pUONEF_RtB_Index_Stru;

		typedef struct Tag_UONERtBlockData
		{
			StateStru				MyState;
			NUROPOINT					OrgCoor;
			UONEF_RtB_Header_Stru		RtBHeader;//Rt�����Y
			pUONEF_RtB_MainData_Stru	*RtBMain;//Rt�����D���
			pUONEF_RtB_Connect_Stru		*RtBConnect;//Rt�����s�����
			pUONEF_RtB_Index_Stru		*RtBIdx;//Rt��RoadID�PNodeID���������
		}UONERtBData,*pUONERtBData;

		class UONERtBCtrl : public UONERtBData
		{
			public:
				UONERtBCtrl();
				virtual ~UONERtBCtrl();
				nuBOOL	InitClass();
				nuVOID	CloseClass();
				nuBOOL	Read_Header(nuLONG StartAddr);//,FILE *RtFile);//Ū�����Y���
				nuBOOL	Read_MainData();//���ͥD����x�s�}�C
				nuBOOL	Read_Connect();//�����p�q����x�s�}�C
				nuBOOL	Read_Index();//Ū���a���I���
				nuBOOL	ReSet();//����Rt��
				nuVOID	Remove_Index();//Ū���I���u���

			private:
				nuVOID	Remove_Header();//�������Y���
				nuVOID	Remove_MainData();//�����D����x�s�}�C
				nuVOID	Remove_Connect();//�����p�q����x�s�}�C
				nuVOID	IniConst();

			public:
				nuFILE	*RtBFile;
				nuTCHAR	FName[NURO_MAX_PATH];

			#ifdef _DEBUG
				nuINT  UoneRtBAlocCount;
				nuINT  UoneRtBFreeCount;
			#endif

			private:
				nuBOOL	ReadHeaderOK;//�P�_���YŪ���P�_ �u���b�wŪ�����Y�����p�U �~�i�H�ޱ����
				nuLONG	m_StartAddr;
		};
	#endif
