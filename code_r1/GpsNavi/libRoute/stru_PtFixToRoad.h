// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/18 05:52:00 $
// $Revision: 1.2 $
#ifndef Def_Stru_PtFixToRoad
	#define Def_Stru_PtFixToRoad
	#include "NuroDefine.h"
	typedef struct Tag_PtFixToRoadStru
	{
		nuULONG   MapID;//�̪�D���Ҧb���ɮ�ID
		nuULONG   RTBID;//�̪�D���Ҧb���϶�ID
		NUROPOINT FixCoor;//�Ԧ^�y��
		nuULONG   FixNode1;//�̪�D�����`�IID1
		nuULONG   FixNode2;//�̪�D�����`�IID2
		nuLONG    FixDis;//�W���I�P�̪�D�����Z��
	}PtFixToRoadStru,*pPtFixToRoadStru;
#endif