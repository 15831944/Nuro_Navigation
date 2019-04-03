	#ifndef Def_MRTCtrl
		#define Def_MRTCtrl

		#include	"Stru_StateStru.h"
		#include	"ConstSet.h"
		#include	"NuroDefine.h"

		typedef struct Tag_MRTData_Header_Stru
		{
			nuULONG	TotalNodeCount;//�`Node��
			nuULONG	TotalRoadCount;//�`Road��
			nuULONG	RtConnectStruCount;//�`�s����
			nuLONG			RtIndexStruStartAddr;//�ҥH��ư_�l��m
			nuLONG			RtConnectStruStartAddr;//�s�����c�_�l��m
		}MRTData_Header_Stru,*pMRTData_Header_Stru;
 
		typedef struct Tag_MRTData_MainData_Stru
		{
			nuULONG	ConnectStruIndex : 24;//�s����Ư��ޭ�
			nuULONG	ConnectCount : 6;//�s���`��
			nuULONG	NoTurnItem : 2;//���s�Х�
			NUROPOINT		NodeCoor;
		}MRTData_MainData_Stru,*pMRTData_MainData_Stru;

		typedef struct Tag_MRTData_Connect_Stru
		{
			nuULONG	TNodeID;//�_�lNodeID
			nuULONG	RoadLength:24;//�D������
			nuULONG	RoadClass:8;//�D������
		}MRTData_Connect_Stru,*pMRTData_Connect_Stru;

#ifdef KD
		typedef struct Tag_MRTData_Index_Stru
		{
			nuULONG		BlockIdx;//�D���N�X
			nuULONG		RoadIdx;//�D���N�X
			nuULONG 	FNodeID;//�_�lNodeID
			nuULONG 	TNodeID;//�_�lNodeID
		}MRTData_Index_Stru,*pMRTData_Index_Stru;
#else
		typedef struct Tag_MRTData_Index_Stru
		{
			nuUSHORT	BlockIdx;//�D���N�X
			nuUSHORT	RoadIdx;//�D���N�X
			nuULONG 	FNodeID;//�_�lNodeID
			nuULONG 	TNodeID;//�_�lNodeID
		}MRTData_Index_Stru,*pMRTData_Index_Stru;
#endif

		typedef struct Tag_MRTData
		{
			MRTData_Header_Stru		RtBHeader;//Rt�����Y
			pMRTData_MainData_Stru	*RtBMain;//Rt�����D���
			pMRTData_Connect_Stru	*RtBConnect;//Rt�����s�����
			pMRTData_Index_Stru		*RtBIdx;//Rt��RoadID�PNodeID���������
		}MRTData,*pMRTData;


		class CMRTCtrl : public MRTData
		{
			public:
				CMRTCtrl();
				virtual ~CMRTCtrl();
				nuBOOL	InitClass();
				nuVOID	CloseClass();
				nuBOOL	Read_Header(nuLONG StartAddr);//,FILE *RtFile);//Ū�����Y���
				nuBOOL	Read_MainData();//���ͥD����x�s�}�C
				nuBOOL	Read_Connect();//�����p�q����x�s�}�C
				nuBOOL	Read_Index();//Ū���a���I���
				nuBOOL	ReSet();//����Rt��

				nuVOID	Remove_Index();//Ū���I���u���


				nuVOID	Remove_Header();//�������Y���
				nuVOID	Remove_MainData();//�����D����x�s�}�C
				nuVOID	Remove_Connect();//�����p�q����x�s�}�C
			private:
				nuVOID	IniConst();

			public:
				nuFILE	*RtBFile;
				nuTCHAR	FName[NURO_MAX_PATH];
			#ifdef _DEBUG
				int  MRTAlocCount;
				int  MRTFreeCount;
			#endif
			private:
				nuBOOL	ReadHeaderOK;//�P�_���YŪ���P�_ �u���b�wŪ�����Y�����p�U �~�i�H�ޱ����
				nuLONG	m_StartAddr;
		};
	#endif
