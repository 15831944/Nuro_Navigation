// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/25 05:25:45 $
// $Revision: 1.4 $
#ifndef Def_AStar
	#define Def_AStar
	#include "ConstSet.h"
	#include "Class_CtrlAVLTree.h"

	class AStarWork
	{
		public:
			AStarWork();
			virtual ~AStarWork();
			nuLONG lUsedCloseCount;//�ϥα���close�ƶq
			#ifdef _DEBUG
				nuLONG lUsedOpenCount;//�ϥα���Open�ƶq
				nuLONG lCallCloseCount;//Open->Close���I�s����
				nuLONG lCallOpenCount;//���->Open���I�s����
				nuLONG Count_SRT;//�{���qOpen���`��
				nuLONG Count_STHR;//�{���qClose���`��
				nuLONG Count_THC;//�{���qClose���`��
				nuLONG Count_TTHR;//�{���qClose���`��
				nuLONG Count_TRT;//�{���qClose���`��
			#endif

			nuBOOL IniData();
			nuBOOL AddToOpen(AStarData m_AStarData, nuLONG STE_ID, WEIGHTINGSTRU NewWeighting);//�[�JOpen��C

			nuBOOL GetBestOpenToClose(LpAVLTree &m_SAVLTree, WEIGHTINGSTRU &BestChoose);
			nuBOOL GetGivenData(AStarData m_AStarData, LpAVLTree &m_SAVLTree, nuLONG STE_ID);

			CtrlAVLTree m_AVLTree;

		private:
			nuVOID InitConst();
			nuVOID ReleaseCloseStru();//�M��Close�ݸ��

	};
#endif