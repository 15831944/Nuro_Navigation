// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/18 05:52:00 $
// $Revision: 1.2 $
/* ���ɬ�FileBlock(FB)�ɪ���Ʊ����  CopyRight LouisLin 20050131 */
	#ifndef Def_BHCtrl
		#define Def_BHCtrl
		#include "NuroDefine.h"

		typedef struct Tag_BHHeaderStru//�ɮ״y�z��
		{
			nuBYTE Version[6];//�ϸꪩ��
			nuBYTE Reverser[8];//��l�y��
			nuBYTE Builder[8];//�ϸ�غc���mm/dd/yy
			nuBYTE MapID[6];//�ɮ��ѧO�X(��X3+�{�X2+��L1)
			nuULONG BlockCount;//�`�϶���
		}BHHeaderStru,*pBHHeaderStru;

		typedef struct Tag_BlockHeaderStru//Block�q��
		{
			BHHeaderStru m_BHH;
			nuBYTE **BHdata;//�϶��ߤ@�X
			//�D�n��ư�(�D�n�������j��:�϶��w�q,�I,�u,�I���u,�I����)
/*
			nuULONG **GlobalBlockID;//�϶��ߤ@�X

			nuLONG **POIDataAddr;//�a���I��Ʀ�m
			nuLONG **POIDataSize;//�a���I��Ƥj�p

			nuLONG **RoadDataAddr;//�D����Ʀ�m
			nuLONG **RoadAddCount;//�D���ֿn�q
			nuLONG **RoadDataSize;//�D����Ƥj�p

			nuLONG **BgLDataAddr;//�I���u��Ʀ�m
			nuLONG **BgLDataSize;//�I���u��Ƥj�p

			nuLONG **BgADataAddr;//�I������Ʀ�m
			nuLONG **BgADataSize;//�I������Ƥj�p

			NUROPOINT **BlockBaseCoor;//�϶���Ǯy��
*/
		}BlockHeaderStru,*pBlockHeaderStru;

		class UONEBHCtrl
		{
			public:
				UONEBHCtrl();
				virtual ~UONEBHCtrl();

				nuBOOL InitClass();
				nuVOID CloseClass();

				nuBOOL ReadBH();//Ū��FB�ɸ��
				nuVOID ReleaseBH();

				nuULONG GlobalBlockID(nuLONG index);//�϶��ߤ@�X
				nuLONG POIDataAddr(nuLONG index);//�a���I��Ʀ�m
				nuLONG POIDataSize(nuLONG index);//�a���I��Ƥj�p
				nuLONG RoadDataAddr(nuLONG index);//�D����Ʀ�m
				nuLONG RoadAddCount(nuLONG index);//�D���ֿn�q
				nuLONG RoadDataSize(nuLONG index);//�D����Ƥj�p
				nuLONG BgLDataAddr(nuLONG index);//�I���u��Ʀ�m
				nuLONG BgLDataSize(nuLONG index);//�I���u��Ƥj�p
				nuLONG BgADataAddr(nuLONG index);//�I������Ʀ�m
				nuLONG BgADataSize(nuLONG index);//�I������Ƥj�p
				NUROPOINT BlockBaseCoor(nuLONG index);//�϶���Ǯy��

			private:
			public:
				BlockHeaderStru	m_BH;//Block�q��
				nuFILE *p_FBH;
				nuTCHAR	FName[NURO_MAX_PATH];
				nuLONG BHFileIdx;
			#ifdef _DEBUG
				int  UoneBHAlocCount;
				int  UoneBHFreeCount;
			#endif
			private:
		};

	//	extern UONEBHCtrl			m_UOneBH;
	//extern UONEBHCtrl m_UOneBH;
	#endif
