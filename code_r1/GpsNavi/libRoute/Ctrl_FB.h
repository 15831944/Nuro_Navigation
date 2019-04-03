// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/18 05:52:00 $
// $Revision: 1.2 $
/* ���ɬ�FileBlock(FB)�ɪ���Ʊ����  CopyRight LouisLin 20050131 */
#ifndef Def_FBCtrl
	#define Def_FBCtrl
	#include "NuroDefine.h"

	typedef struct Tag_BlockSegmentStru//Block�q��
	{
		nuULONG FromBlockID;
		nuULONG ToBlockID;
	}BlockSegmentStru,*pBlockSegmentStru;

	class FBCtrl
	{
		public:
			FBCtrl();
			virtual ~FBCtrl();

			nuBOOL InitClass();
			nuVOID CloseClass();

			nuBOOL ReadFB();//Ū��FB�ɸ��
			nuVOID ReleaseFB();
		private:
		public:
			nuULONG SegmentCount;//�q����
			BlockSegmentStru	**BS;//Block�q��
			nuFILE *FB;
			nuTCHAR				FName[NURO_MAX_PATH];
		private:
	};

#endif