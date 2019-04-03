 // Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/18 05:52:00 $
// $Revision: 1.3 $
/* ���ɬ�Draw(DW)�ɪ���Ʊ����  CopyRight LouisLin 20050131 */
	#ifndef Def_UONEDwCtrl
		#define Def_UONEDwCtrl

		#include "ConstSet.h"
		#include "NuroDefine.h"

		typedef struct Tag_UONEDWHeader//�T�w�����Y
		{
			nuULONG	ClassCnt;
			nuLONG**			BlockClassStart;//�D���_�l��m��
		}UONEDWHeader,*pUONEDWHeader;

		typedef struct TagUONERoadData
		{		
			nuUSHORT	RoadCommonIndex;//�D���@�P��Ư��ޭ�
			nuUSHORT	VertexCount;//�`�I�`��
			nuULONG	    StartVertexIndex :24;//�_�l�`�I���ޭ�
			nuDWORD		OneWay:2;
			nuDWORD		bGPSState:1;
			nuDWORD		nLevel:5;
			nuLONG		HouseNumberAddr;//���P��T��m
		}UONERoadData;
		typedef struct TagUONERoadCommonData
		{		
			nuLONG	    RoadNameAddr;//���W��m
			nuULONG	    RoadNameLen:8;//���W����
			nuULONG 	RoadType:4;//�D�����A
			nuULONG 	SpeedLimit:4;//�D�����A
			nuULONG 	CityID : 6;//�����X
			nuULONG     TownID : 10;//�m��X
		}UONERoadCommonData;

		typedef struct Tag_UONEBlockRoadData
		{
			nuULONG		RoadCount;//�D���`��
			nuULONG		RdCommCount;//�D���`��
			nuULONG		VertexCount;//�`�I�`��
			UONERoadData		**RdData;//�D�����
			UONERoadCommonData	**RdCommData;//�@�P���
			NURORECT			**RdBoundary;//�D�����
			NUROSPOINT			**VertexCoor;//�`�I�y�Ц�
		}UONEBlockRoadData,*pUONEBlockRoadData;

		class UONERDwCtrl
		{
			public:
				UONERDwCtrl();
				virtual ~UONERDwCtrl();

				nuBOOL InitClass();
				nuVOID CloseClass();

				nuBOOL	Reset();
				nuBOOL	Read_Header();//Ū�����Y���
				nuVOID	Remove_Header();//�������Y���
				nuBOOL	Read_BlockData(nuULONG Index);
				nuVOID	Remove_BlockData(nuULONG Index);	
				
				nuBOOL	GetCityTownID(nuULONG Now_BlockIdx,nuULONG Now_RoadIdx,nuULONG &NowCityID,nuULONG &NowTownID);

			private:
				nuVOID	InitConst();
				nuBOOL	CreateMainStru(nuULONG Count);
				nuVOID	ReleaseMainStru();
				nuBOOL	Read_RoadData(nuULONG Index);//Ū���D�����
				nuVOID	Remove_RoadData(nuULONG Index);//�����D�����
			public:
				nuFILE				*DWFile;
				UONEDWHeader		Header;
				UONEBlockRoadData	**Rd;
				nuTCHAR				FName[NURO_MAX_PATH];
				nuLONG				RDWFileIdx;
			#ifdef _DEBUG
				int  UoneRdwAlocCount;
				int  UoneRdwFreeCount;
			#endif
			private:
				nuBOOL	ReadHeaderOK;//�P�_���YŪ���P�_ �u���b�wŪ�����Y�����p�U �~�i�H�ޱ����
				nuBOOL	**ReadBlockOK;//�P�_�O�_��Ū��Block���
		};

	#endif
