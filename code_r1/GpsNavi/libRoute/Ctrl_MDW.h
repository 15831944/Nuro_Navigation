	#ifndef DEF_MDWCTRL
		#define DEF_MDWCTRL

		#include "ConstSet.h"
		#include "NuroDefine.h"

		typedef struct Tag_MDWHeader//�T�w�����Y
		{
			nuULONG	m_TotalBlockCount;
			nuLONG**			p_GBlockID;//�D���_�l��m��
			nuLONG**			p_BlockRoadDataAddr;//�D���_�l��m��
			nuLONG**			p_BlockRoadAddCount;//�D���_�l��m��
			nuLONG**			p_BlockDataSize;//�D���_�l��m��
			nuULONG	m_ClassCnt;
			nuLONG**			p_BlockClassStartAddr;//�D���_�l��m��
		}MDWHeader,*pMDWHeader;

		typedef struct TagMDWRoadData
		{		
			nuULONG	VertexCount:16;//�`�I�`��
			nuULONG	StartVertexIndex_high:16;//�_�l�`�I���ޭ�
			nuULONG	StartVertexIndex_Low:8;//�_�l�`�I���ޭ�
			nuULONG	RoadClass:3;//�D���@�P��Ư��ޭ�
			nuULONG	MapID:9;
			nuULONG	RTBID:12;
		}MDWRoadData;
		typedef struct Tag_MDWBlockRoadData
		{
			nuULONG	m_RoadCount;//�D���`��
			nuULONG	m_VertexCount;//�`�I�`��
			MDWRoadData		**p_RdData;//�D�����
			NUROPOINT		**p_VertexCoor;//�`�I�y�Ц�
		}MDWBlockRoadData,*pMDWBlockRoadData;


		class CMDWCtrl
		{
			public:
				CMDWCtrl();
				virtual ~CMDWCtrl();

				nuBOOL InitClass();
				nuVOID CloseClass();

				nuBOOL	Reset();
				nuBOOL	Read_Header();//Ū�����Y���
				nuVOID	Remove_Header();//�������Y���
				nuBOOL	Read_BlockData(nuULONG Index);
				nuVOID	Remove_BlockData(nuULONG Index);			
			private:
				nuVOID	InitConst();
				nuBOOL	CreateMainStru(nuULONG Count);
				nuVOID	ReleaseMainStru();
				nuBOOL	Read_RoadData(nuULONG Index);//Ū���D�����
				nuVOID	Remove_RoadData(nuULONG Index);//�����D�����
			public:
				nuFILE				*DWFile;
				MDWHeader			Header;
				MDWBlockRoadData	**Rd;
				nuTCHAR				FName[NURO_MAX_PATH];
			#ifdef _DEBUG
				int  MDWAlocCount;
				int  MDWFreeCount;
			#endif
			private:
				nuBOOL	ReadHeaderOK;//�P�_���YŪ���P�_ �u���b�wŪ�����Y�����p�U �~�i�H�ޱ����
				nuBOOL	**ReadBlockOK;//�P�_�O�_��Ū��Block���
		};
	#endif
