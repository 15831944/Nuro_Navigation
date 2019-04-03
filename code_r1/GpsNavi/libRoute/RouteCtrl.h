// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: daniel $
// $Date: 2011/05/20 07:32:56 $
// $Revision: 1.6 $
#ifndef Def_RoutingCtrl
	#define Def_RoutingCtrl

	#include "NuroDefine.h"
	#include "ConstSet.h"
	#include "NuroEngineStructs.h"
	#include "Class_CalRouting.h"

	class RouteCtrl
	{
		public:
			RouteCtrl();
			virtual ~RouteCtrl();
			nuBOOL AddMarketPt(nuLONG CoorX, nuLONG CoorY, nuLONG Index, nuLONG FileID, nuLONG RtBlockID);//�ǤJ���I
			nuBOOL NewAddMarketPt( nuLONG Index,nuLONG Now_FileIdx, nuLONG Now_BlockIdx, nuLONG Now_RoadIdx, 
				                   NUROPOINT Now_FixPt );
			nuBOOL NewAddMarketPt_NodeID( nuLONG Index, nuLONG Now_FileIdx, nuLONG Now_BlockIdx, nuLONG CityID, 
				                          nuLONG TownID, nuLONG Now_RoadIdx, NUROPOINT Now_FixPt );
			nuLONG StartRouting(ROUTINGDATA *NaviData, nuBOOL b_MakeThr, nuLONG l_RoutingRule);//�}�l�W��
			nuVOID ReleaseNaviInfo(PROUTINGDATA NaviData);
			nuBOOL InitMapIDtoMapIdx();
			nuLONG ReRoute(ROUTINGDATA *NaviData, nuBOOL b_MakeThr, nuLONG l_RoutingRule);//���s�W��
			nuLONG CongestionRoute( ROUTINGDATA *NaviData, nuBOOL b_MakeThr, nuLONG l_RoutingRule, 
				                    nuLONG l_CongestionDis );//�먮¶��

			//nuLONG LocalRoutingU1(PNAVIRTBLOCKCLASS pNRBC,nuLONG l_RoutingRule);//�ϰ�W��
			nuLONG LocalRoutingU1(PNAVIRTBLOCKCLASS pNRBC, nuLONG l_RoutingRule, nuLONG FMapIdx, nuLONG TMapIdx);//�ϰ�W��

			nuBOOL GetMRouteData(PNAVIFROMTOCLASS pNFTC,nuLONG l_RoutingRule);

			nuBOOL GetNextCrossData( nuLONG MapID, nuLONG BlockID, nuLONG RoadID, nuLONG CarAngle, 
				                     NUROPOINT NowCoor, NUROPOINT TNodeCoor, CROSSFOLLOWED **stru_Cross );
			nuBOOL ReleaseNextCrossData();

			nuVOID SetRideAngle(nuLONG lAngle);
		#ifdef LCMM
			nuLONG LocalRoutingU1_LCMM(PNAVIRTBLOCKCLASS pNRBC, nuLONG FMapIdx, nuLONG TMapIdx);//�ϰ�W��
			nuLONG StartRouting_LCMM(ROUTINGDATA *NaviData, nuBOOL b_MakeThr, nuLONG *l_RoutingRule, nuLONG RouteCount);//�}�l�W��
			nuLONG TMCLocalRoute(NAVIFROMTOCLASS *pNFTC, PNAVIRTBLOCKCLASS pNRBC,TMC_ROUTER_DATA *TMCData, nuLONG TMCDataCount, nuLONG RouteRule);
		#endif

		public:
			Class_CalRouting	m_CalRouting;
			nuBOOL				b_UseAngle;
		private:
			PTFIXTOROADSTRU	MkPt[MAX_TARGET];//�W�e�I�Ȧs��
			nuLONG			RideAngle;
			nuLONG			m_lRouteCount;
	};

#endif
