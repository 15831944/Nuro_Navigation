#ifndef _NURO_ROUTE_DATA_20080521
#define _NURO_ROUTE_DATA_20080521

#include "NuroDefine.h"

typedef struct tagNAVICROSSCLASS
{
	nuWORD	CrossBlockIdx;//Block index
	nuWORD	CrossRoadIdx;//Road index in block
	long	CrossRoadNameAddr;//Road Name address
	short	CrossAngle;//
	nuWORD  nFlag:4;//0:��ʼ�� 1:ȡ�ĳɹ� 2:��ȡʧ��
	nuWORD  nRoadNameLen:12;
	long	CrossVoiceType;//
	long	CrossClass;//
}NAVICROSSCLASS, *PNAVICROSSCLASS;

typedef struct tagNAVISUBCLASS
{
	nuWORD	BlockIdx;//�Ҧb��Dw�϶�
	nuWORD	RoadIdx;//�D��ID
	nuLONG	RoadNameAddr;//�D���W�٦�m
	nuDWORD	RoadLength;//�D������
	nuLONG	RoadVoiceType;//�y����������

	nuDWORD	RoadClass : 16;
	nuDWORD    SPTFlag: 1; //SignPost Flag
	nuDWORD	 LaneGuideFlag:1; //���D�T���X��
	nuDWORD    Reserve: 14; //Reserve
	nuDWORD CrossCount;//���q���I����e���f��(�i�q��)
	nuWORD	CityID;//�����X
	nuWORD	TownID;//�m��X
	NAVICROSSCLASS *NCC;//��e���f���
	NUROPOINT	StartCoor;//���q�_�I�y��
	NUROPOINT	EndCoor;//���q���I�y��
	nuLONG	Flag;//�欰�X��(�W�U���[�� �a�U�D)
	nuLONG	TurnFlag;//��V�X��(���k�� �j��)
	nuLONG	TurnAngle;//����
	nuDWORD	ArcPtCount;//�զ��D�����y���I�`��
	NURORECT	Bound;//�D�����(�e�ɯ���|�ɧP�_)
	NUROPOINT	*ArcPt;//�զ��D�����y���I
	nuLONG	Real3DPic;//3D�괺�ϼƦrIID
	nuLONG PTSNameAddr;//PTS���Qλ��
	nuLONG ShowIndex;
	nuBOOL bGPSState;
	nuBYTE	nOneWay;
	nuBYTE	nReserve[2];
}NAVISUBCLASS, *PNAVISUBCLASS;

typedef struct tagPTFIXTOROADSTRU
{
	nuDWORD		MapIdx;//�ɮ׽s��
	nuDWORD		MapID;//�̪�D���Ҧb���ɮ�ID
	nuDWORD		RTBID;//�̪�D���Ҧb���϶�ID
	NUROPOINT	FixCoor;//�Ԧ^�y��
	nuDWORD		FixNode1;//�̪�D�����`�IID1
	nuDWORD		FixNode2;//�̪�D�����`�IID2
	long		FixDis;//�W���I�P�̪�D�����Z��
}PTFIXTOROADSTRU,*PPTFIXTOROADSTRU;

typedef struct tagNAVIRTBLOCKCLASS
{
	nuDWORD NSSCount;//�W���X�Ӫ����q�`��
	long	RealDis;//�u��Z��
	long	WeightDis;//�[�v�Z��
	PTFIXTOROADSTRU FInfo;//�_�I������T
	PTFIXTOROADSTRU TInfo;//���I������T
	nuDWORD *NodeIDList;//�~�g���`�I���
	nuDWORD NodeIDCount;//�~�g���`�I�`��
	nuBYTE RTBStateFlag;//0:�w�Ѷ}��RTB 1:���Ѷ}��RTB(�~�gXXX) 2:���Ѷ}��THC(�i�J�������). 
	nuBYTE RTBWMPFixFlag;//0 :WMP��?? 1:??��. 
//	nuWORD RTBStateFlag;//0:�ѽ��_��RTB 1:δ���_��RTB(;?XXX) 2:δ���_��THC(�M��ȫ��·�W)
	nuWORD FileIdx;//�n��ID
//	long FileIdx;//�ɮ�ID
	nuDWORD RTBIdx;//Rt�϶�ID
	NAVISUBCLASS	*NSS;//�W���X�Ӫ��D���l���c
	tagNAVIRTBLOCKCLASS *NextRTB;
}NAVIRTBLOCKCLASS,*PNAVIRTBLOCKCLASS;

typedef struct tagNAVIFROMTOCLASS
{
	bool    DisPaly;
	bool	RunPass;//���q�W�������P�_
	long	Reserve:24;
	NUROPOINT	FCoor;//�X�o�a�y��
	long	FromFileID;//�X�o�a�Ҧb�ϸ�ID
	long	FromRtBID;//�_�I�Ҧb�϶�
	NUROPOINT	TCoor;//�ت��a�y��
	long	ToFileID;//�ت��a�Ҧb�ϸ�ID
	long	ToRtBID;//���I�Ҧb�϶�
	long	NRBCCount;//�W����g���϶���
	NAVIRTBLOCKCLASS	*NRBC;//Rt�϶���Ƶ��c
	tagNAVIFROMTOCLASS	*NextFT;
}NAVIFROMTOCLASS,*PNAVIFROMTOCLASS;

typedef struct tagROUTINGDATA
{
	long	NFTCCount;//�_�g�����c�`��
#ifdef LCMM
	NAVIFROMTOCLASS	*NFTC[MAX_RouteRule];	
#else
	NAVIFROMTOCLASS	*NFTC;//�_�g����Ƶ��c
#endif
}ROUTINGDATA,*PROUTINGDATA;


typedef struct tagLOCALROUTEDATA
{
	NAVIRTBLOCKCLASS*	pNRBC;
	tagLOCALROUTEDATA*	pNext;
}LOCALROUTEDATA, *PLOCALROUTEDATA;

//the result number of Route
#define ROUTE_ERROR						0
#define ROUTE_SUCESS					1
#define ROUTE_SAMEPT					2
#define ROUTE_OUTROUTELIMIT				3
#define ROUTE_NOFTPT					4
#define ROUTE_THRERROR					5//��ϳW������
#define ROUTE_THRLOCALERROR				6//��ϳW������
#define ROUTE_CLOSEERROR				7//�ϰ�W����ƾ�z����
#define ROUTE_READSRTFALSE				8//Ū���_�IRT����
#define ROUTE_READERTFALSE				9//Ū�����IRT����
#define ROUTE_READRTFALSE				10//Ū��RT�X��
#define ROUTE_READRDWFALSE				11//Ū��RDW�X��
#define ROUTE_READTHRFALSE				12//Ū��Thr����
#define ROUTE_USEALLASTARBUFFER			13//�B��q�W�LAStar����
#define ROUTE_NOFOUNDROADTOENDPOINT		14//�S�����i�q����I�����|
#define ROUTE_APPROACHFALSE				15//�^�Ҹ��|����
#define ROUTE_CREATEROUTEDATAFASLE		16//���ͳW���x�s��ƥ���
#define ROUTE_SUCCESSSTEP1				17//���\���z��ƲĤ@�B(�B�zRT)
#define ROUTE_SUCCESSSTEP2				18//���\���z��ƲĤG�B(�B�zdw)
#define ROUTE_SUCCESSSTEP3				19//�ϰ�W����ƾ�z����
#define ROUTE_NEWASTARSTRUCTFALSE		20//����AStar���c����
#define ROUTE_READMRTFALSE				21//Ū��Thc����
#define ROUTE_MRT_ASTARFALSE			22//MRT AStar False
#define ROUTE_MRT_CREATEROUTEDATAFASLE	23//���ͳW���x�s��ƥ���
#define ROUTE_MRT_APPROACHFALSE			24//���ͳW���x�s��ƥ���



/////////////////////////////////////////////////////////////////////////////////
typedef struct tagROADCROSSDATA
{
	nuDWORD	BlockIdx;//
	nuWORD	nMapIdx;
	nuWORD	RoadIdx;//
	short	RoadAngle;//
	short	RoadLength;
	nuWORD	RoadVoiceType;//
	nuWORD	RoadClass;//
	long	nNameAddr;
}ROADCROSSDATA, *PROADCROSSDATA;

typedef struct tagROADSEGDATA
{
	nuDWORD	BlockIdx;//
	nuWORD	nMapIdx;
	nuWORD	RoadIdx;//
	short	RoadLength;//
	short	RoadAngle;
	nuWORD	RoadVoiceType;//
	nuWORD	RoadClass;
	long	nNameAddr;
	nuWORD	nCrossCount;
	ROADCROSSDATA	*pRdCross;//
	NUROPOINT		EndCoor;//
}ROADSEGDATA, *PROADSEGDATA;

typedef struct tagCROSSFOLLOWED
{
	nuDWORD			nRdSegCount;
	PROADSEGDATA	pRdSegList;
}CROSSFOLLOWED, *PCROSSFOLLOWED;

//2011.05.24
typedef struct tag_TMC_INFOROUTER
{
	nuBOOL  bTMCPass;
	nuSHORT	sTMCRouteWeighting;
	nuSHORT	sTMCRouteTime;
	nuSHORT	sTMCNodeCount;
	nuSHORT sTMCEventID;
	nuLONG	lTMCLocationAddr;
}TMC_ROUTER_DATA, *PTMC_ROUTER_DATA;

typedef struct tag_TMC_Router
{
	nuINT   nCount;
	PTMC_ROUTER_DATA pPTMC_INFORouter;	 
}TMC_Info_Router;

typedef struct Strcture_KMInfoData
{
	nuLONG  lBlockIdx;
	nuLONG  lRoadIdx;
	nuBYTE  nClass;
	nuBYTE  nOneWay;
	nuWORD  KmName;
	nuLONG  X;
	nuLONG  Y;
	nuLONG	NameLen;
	nuLONG	NameAddr;
}KMInfoData;
typedef struct tagTMCRoadInfoStru
{
	nuCHAR  Traffic;
	nuCHAR  Dir;
}TMCRoadInfoStru,*pTMCRoadInfoStru;
#endif
