// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: daniel $
// $Date: 2010/11/08 05:53:52 $
// $Revision: 1.14 $

#include "NuroClasses.h"

#ifndef Def_Class_CalRouting
	#define Def_Class_CalRouting
	#include "RouteBase.h"
	#include "Class_PtFixToRoad.h"

	#include "NuroEngineStructs.h"
	#include "AStar.h"
	#include "Class_Approach.h"
	#include "ConstSet.h"
	#include "Class_CalMRT.h"
	#include "Ctrl_ND6.h"
	#include "Ctrl_TTI.h"
	#include "Ctrl_CMP.h"
	
	typedef struct Tag_TmpRoutingInfo
	{
		PTFIXTOROADSTRU PtLocalRoute;
		nuLONG MapIdx;
		nuLONG RtBIdx;
		nuLONG FixDis1;
		nuLONG FixDis2;
	}TmpRoutingInfo,*pTmpRoutingInfo;

	class Class_CalRouting// : public MathTool
	{
		public:
			Class_CalRouting();
			virtual ~Class_CalRouting();
			nuBOOL InitClass();
			nuVOID CloseClass();
			//MapID�PMapIdx������������禡
			nuBOOL InitMapIDtoMapIdx();//Ū��MapID�PMapIdx��������
			nuVOID ReleaseMapIDtoMapIdx();//����MapId�PMapIdx������ҨϥΪ��O����

			nuLONG StartRouting( PTFIXTOROADSTRU &FPt, PTFIXTOROADSTRU &TPt, PNAVIFROMTOCLASS pNFTC, nuBOOL b_MakeThr, 
				                 nuLONG l_RoutingRule );//�_�W�I�W��
			
			//nuLONG LocalRouting(PNAVIRTBLOCKCLASS pNRBC,nuLONG l_RoutingRule);//RtB��ϳW��
			nuLONG LocalRouting(PNAVIRTBLOCKCLASS pNRBC, nuLONG l_RoutingRule, nuLONG FMapIdx, nuLONG TMapIdx);
			nuVOID SetAstarBase(nuBOOL b_Local);
			nuBOOL GetMRouteData(PNAVIFROMTOCLASS pNFTC, nuLONG l_RoutingRule);

			nuBOOL GetNextCrossData(PTFIXTOROADSTRU nowMkPt, NUROPOINT TNodeCoor, CROSSFOLLOWED **stru_Cross);
			nuVOID LeaveGetNextCrossData();
			nuBOOL ReleaseNextCrossData();
			CROSSFOLLOWED s_SaveCross;

		private:
			//nuBOOL ColationDataAgain(PTFIXTOROADSTRU &FPt,PTFIXTOROADSTRU &TPt,TmpRoutingInfo &CLRS_F,TmpRoutingInfo &CLRS_T,nuBOOL b_Local,nuLONG l_RoutingRule);//�Ѯy�Ч�X�W���һݰ򥻸��
			nuBOOL ColationDataAgain( PTFIXTOROADSTRU &FPt, PTFIXTOROADSTRU &TPt, TmpRoutingInfo &CLRS_F,
				                      TmpRoutingInfo &CLRS_T, nuBOOL b_Local, nuLONG l_RoutingRule, 
									  nuLONG FMapIdx, nuLONG TMapIdx );
			nuVOID ReleaseColationDataAgain(UONERtCtrl &TmpRtCtrl);//�M����CollationDataAgain�Ҳ��ͪ��O����
			nuVOID GetTwoSiteDis(UONERtBCtrl *TmpRtBCtrl,TmpRoutingInfo &CLRS);//�qRoad�h���o�̨Ϊ��_�W�W��NodeID
			nuBOOL ReadRtBIndex(UONERtBCtrl *TmpRtBCtrl);
			nuBOOL GetNaviInfo_FromRtFile(PNAVIRTBLOCKCLASS pNRBC,UONERtBCtrl *TmpRtBCtrl);//�qRt�ɨ��o�һݪ��W�����G

			nuBOOL GetBlockRoadIdx( nuUSHORT *BlockIdx, nuUSHORT *RoadIdx, nuULONG FNodeID, nuULONG TNodeID, 
				                    nuLONG *Idx, UONERtBCtrl *TmpRtBCtrl, nuUSHORT dontfindB1, nuUSHORT dontfindR1,
									nuUSHORT dontfindB2, nuUSHORT dontfindR2 );//�z�LNodeID�h���o�Ҧb��BlockID�PRoadID
			
			nuLONG UONEGetGuessDistance2(NUROPOINT Pt1, NUROPOINT PT2);//�p��w���Z��(�{�b�����P�p��Z���ۦP �p�G����n���w������ ����M�N���ܭp�⪺�覡)
			nuBOOL GetWeighting(nuLONG Class);//���o�D���[�v��
			nuLONG GetDistance(NUROPOINT Pt1, NUROPOINT PT2);//�p��Z��
			nuLONG  AveLatitude_l;

			//nuVOID GetRouteNodeID(RtBCtrl &TmpRtBCtrl,TmpRoutingInfo &CLRS,nuBOOL b_StartNode);//�qRoad�h���o�̨Ϊ��_�W�W��NodeID
			nuBOOL GetNodeIDList(AStarWork &m_AStar,TmpRoutingInfo &CLRS_F,TmpRoutingInfo &CLRS_T);//�qAStar��Close�ݨ��o�̨θ��|��NodeID
			nuBOOL CreateRoutingData(PNAVIFROMTOCLASS TmpNaviFromToClass);//�ھ�Approach�����G ���Х߭n�x�s��ƪ����c
			nuBOOL CreateLocalRoutingData(PNAVIRTBLOCKCLASS TmpNaviRtBlockClass);//�ھ�Approach�����G ���Х߭n�x�s��ƪ����c
			nuBOOL AStarSuccessWork(PNAVIFROMTOCLASS pNFTC);//AStar�W�����\�������ƾ�z
			nuBOOL LocalAStarSuccessWorkStep1(PNAVIRTBLOCKCLASS pNRBC);//�ϰ�W��(Local AStar)���\�������ƾ�z
			nuBOOL LocalAStarSuccessWorkStep2(PNAVIRTBLOCKCLASS pNRBC);//�ϰ�W��(Local AStar)���\�������ƾ�z
			nuBOOL LocalAStarSuccessWorkStep3(PNAVIRTBLOCKCLASS pNRBC);//�ϰ�W��(Local AStar)���\�������ƾ�z
			nuBOOL GetNaviInfo_FromDwFile(PNAVIRTBLOCKCLASS pNRBC);//�qDw�ɨ��X�һݪ��W�����G
			nuLONG GetAngle(NUROPOINT FPt,NUROPOINT NPt,NUROPOINT TPt);//�Ѱ_�g�W�I�p�⨤�׮t
			nuBOOL ReColFTRoad(PNAVIRTBLOCKCLASS pNRBC);//���s��z�Y����T
			nuBOOL ColTurnFlag(PNAVIRTBLOCKCLASS pNRBC);//��z��V�X��

			nuVOID LeaveStartRouting(AStarWork &m_AStar);//����StartRouteing�ҨϥΪ��O����
			nuVOID LeaveLocalRouting(AStarWork &m_AStar);//����LoaclRouting�ҨϥΪ��O����

			//Louis 20060720 
			nuBOOL FindNearEnd7Net( AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, 
				                    nuLONG &Dis_Rd7, nuULONG &LimitNodeID );
			nuBOOL PassNoTurn(nuBOOL b_TargetArea, AStarData &m_AStarData, AStarWork &m_AStar, TagAStarData &m_SAVLData);
			
			//added by Daniel for LCMM 20110614
			nuBOOL ReFindPointNodeID(TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, nuBOOL b_Local);//���s��L�ݩ�_�W�I�b�D����ݪ�Node
			nuBOOL CompareRTBIndex( PTFIXTOROADSTRU &FPt, PTFIXTOROADSTRU &TPt, TmpRoutingInfo &CLRS_F, 
				                    TmpRoutingInfo &CLRS_T, nuBOOL b_Local, nuLONG FMapIdx, nuLONG TMapIdx );//���RTBindex
			nuVOID LeaveStartRouting_ForMultiConditionRoute(AStarWork &m_AStar);
			nuVOID ReMoveThrData();

			nuVOID RTSleepTimeCtrl(nuLONG lSleepTime);
//#ifdef _USETTI
			nuVOID ReleaseTTI();
			nuBOOL ReadTTI(TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T);
			nuBOOL TTIPass(nuBOOL bTargetArea, nuLONG TTIAddr);
			nuBOOL ModePass_KD(nuSHORT Mode);
//#endif

#ifdef _DDst
			nuBOOL Dstroadsituation(nuBOOL b_TargetArea,AStarData &m_AStarData,AStarWork &m_AStar);
#endif
			
#ifdef _DTMC
			nuBOOL Tmcroadsituation(nuBOOL b_TargetArea,AStarData &m_AStarData,AStarWork &m_AStar);
#endif

#ifdef _DAR
			nuBOOL  NodeID_Compare(nuULONG FNodeID, nuULONG FRTBID, nuULONG *ReNodeID, nuULONG *ReRTBID);

			nuVOID  Astar_AR( nuBOOL &b_CloseThr, NUROPOINT TargetCoor, nuLONG EndBoundaryRange, nuDWORD LimitNodeID_7, 
				              TagAStarData &m_SAVLData, AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, 
							  TmpRoutingInfo &CLRS_T, WEIGHTINGSTRU BestChoose );
#endif
			nuVOID  Astar_SRT( nuBOOL &b_CloseThr, NUROPOINT TargetCoor, nuLONG EndBoundaryRange, nuDWORD LimitNodeID_7, 
				               TagAStarData &m_SAVLData, AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, 
							   nuBOOL &b_StartLevelCut,WEIGHTINGSTRU BestChoose,nuLONG l_RoutingRule );//�W��

			nuVOID  Astar_TRT( nuBOOL &b_CloseThr, NUROPOINT TargetCoor, nuDWORD Run8E_Dis, nuLONG EndBoundaryRange, 
				               nuDWORD LimitNodeID_7, TagAStarData &m_SAVLData, AStarWork &m_AStar, TmpRoutingInfo &CLRS_F,
							   TmpRoutingInfo &CLRS_T, nuBOOL &b_StartLevelCut, nuBOOL &b_CloseStart, 
							   WEIGHTINGSTRU BestChoose, nuLONG l_RoutingRule );//�W��

			nuVOID  Astar_STHR( nuBOOL &b_CloseThr, NUROPOINT TargetCoor, nuLONG EndBoundaryRange, nuDWORD LimitNodeID_7,
				                TagAStarData &m_SAVLData, AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, 
								TmpRoutingInfo &CLRS_T,WEIGHTINGSTRU BestChoose );//�W��

			nuVOID  Astar_TTHR( nuBOOL &b_CloseThr, NUROPOINT TargetCoor, nuLONG EndBoundaryRange, nuDWORD LimitNodeID_7,
				                TagAStarData &m_SAVLData, AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, 
								TmpRoutingInfo &CLRS_T,WEIGHTINGSTRU BestChoose );//�W��

			nuVOID  Astar_THC( nuBOOL &b_CloseThr, NUROPOINT TargetCoor, nuLONG EndBoundaryRange, nuDWORD LimitNodeID_7,
				               TagAStarData &m_SAVLData, AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, 
							   TmpRoutingInfo &CLRS_T, WEIGHTINGSTRU BestChoose );//�W��
		    #if (defined VALUE_EMGRT) || (defined ZENRIN)
				//�B�z�j�����ϳq���O�����
				nuBOOL ReadPTS(nuLONG FMapID);
				nuLONG CheckPTS(nuULONG RtBID,nuULONG NodeID);
				nuVOID ReMovePTS();
			#endif
#ifdef _USERT6
				nuBOOL bCheckRT6(PNAVIRTBLOCKCLASS pNRBC);
#endif
		public:
			//���F��thr �S�O�}��X�Ӫ�API
			nuBOOL ReadBaseData(TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, nuBOOL b_Local, nuLONG l_RoutingRule);//Ū���Y��RtBlock�Pthr�����

			//Ū���T����(�]���O����M�� ��Ыخɩһݭn���O�����z�ɶ� �bsunplus���|�ܤ[ �]���ڭ̭n��ֳo�ؾ�z���ʧ@)
			nuBOOL ReadSysNTData(TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, nuBOOL b_Local, nuLONG l_RoutingRule);//Ū���Y��RtBlock�Pthr�����
			//�����T����
			nuVOID ReMoveSysNTData();

			//Ū���Y�ɸ��p��
#ifdef _DDst
			nuBOOL ReadSysDstData(TmpRoutingInfo &CLRS_F,TmpRoutingInfo &CLRS_T,nuBOOL b_Local,nuLONG l_RoutingRule);
			nuVOID ReMoveSysDstData();
#endif

#ifdef _DTMC
			nuBOOL ReadSysTmcData(TmpRoutingInfo &CLRS_T, TMC_ROUTER_DATA *TMCData, nuLONG TMCDataCount, nuBOOL *bTMCRTB);
			nuVOID ReMoveSysTmcData();
#endif	

#ifdef _DAR
			nuBOOL ReadSysARData(TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, nuBOOL b_Local, nuLONG l_RoutingRule);
			nuVOID ReMoveSysARData();
			nuBOOL RT_Enter_AR();
#endif
			//�_�W�ϰ쪺RTB�s���P����
			nuBOOL ReadSysRTData(TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, nuBOOL b_Local, nuLONG l_RoutingRule);//Ū���Y��RtBlock�Pthr�����
			nuVOID ReMoveSysRTData();
			
			nuVOID ReMoveBaseData();//�����ҳЫت��Y��RtBlock�Pthr�����
			nuBOOL AStar(AStarWork &m_AStar, TmpRoutingInfo &CLRS_F, TmpRoutingInfo &CLRS_T, nuLONG l_RoutingRule);//���|�W��
			//UONERtBCtrl			LocalRtB[2];//�_�W�IRTBlock����ƼȦs��
//			#ifdef DEF_MAKETHRROUTE
				nuLONG ThrGDis;
				nuLONG ThrRDis;
				nuLONG TargetClass;
//			#endif
			nuLONG CarAngle;
			Class_CalMRT	m_calmrt;

			nuBOOL b_ReRouting;
		private:
			nuLONG			ClassWeighting;//�����v��(���l)
			//AStarWork		m_AStar;//AStar�B�� �֤ߪ���

			Class_Approach	Tmp_Approach;//Astar�W�e������d�U�Ӫ����(approach����)
			//Louis 20060720 �N�v�ȵ��ݩ� �����~���B�z �����w��~���]�w�ɪ��]�w�Ӱʧ@

			AStarData		m_ApprocahAStarData;
			nuLONG Renum_RoutingState;

			NUROPOINT Temp_S_DiffCoor;//�_�I�ϰ�۹�y�Юt��,���I�ϰ�۹�y�Юt��
			NUROPOINT Temp_T_DiffCoor;//�_�I�ϰ�۹�y�Юt��,���I�ϰ�۹�y�Юt��

			nuBOOL b_LocalRut;//�O�_�u�i��ϰ�W��
			nuSHORT SRTTypeCount[20];
			nuSHORT TRTTypeCount[20];
			nuBOOL b_FirstRdEffect;
//			nuBOOL b_PassTollgate;//�O�_�ư����O���q
			nuDWORD TWalkingNode;

			Class_ThrCtrl*		m_pGThr[2];//�����(thr)����ƼȦs��
			Class_ThrCtrl*		m_pThr_F;//�����(thr)����ƼȦs��
			Class_ThrCtrl*		m_pThr_T;//�����(thr)����ƼȦs��
			CCtrl_3dp*			m_pcls3dp;//3D�괺����	
			CCtrl_ECI*			m_pECI3dp;//Zenrin 3DP
			/*#ifdef VALUE_EMGRT
				CCtrl_TT*		m_pNT_F;
				CCtrl_TT*		m_pNT_T;
				CCtrl_PTS*		m_PTS_F;
				CCtrl_PTS*		m_PTS_T;
				CCtrl_TT*		m_pclsNT[2];//�j���T����
				CCtrl_PTS*		m_pclsPTS[2];//�j�����t�����W����	
			#else
				CCtrl_NT*		m_pNT_F;
				CCtrl_NT*		m_pNT_T;
				CCtrl_NT*		m_pclsNT[2];//�x�W�T����	
				
			#endif*/
			CCtrl_TT*		m_pNT_F;
			CCtrl_TT*		m_pNT_T;
			CCtrl_TT*		m_pclsNT[2];//�j���T����
	        #if (defined VALUE_EMGRT) || (defined ZENRIN)
				CCtrl_PTS*		m_PTS_F;
				CCtrl_PTS*		m_PTS_T;
				CCtrl_PTS*		m_pclsPTS[2];//�j�����t�����W����	
			#else
				//CCtrl_NT*		m_pNT_F;
				//CCtrl_NT*		m_pNT_T;
				//CCtrl_NT*		m_pclsNT[2];//�x�W�T����	
				
			#endif

			#ifdef _DTMC
				CCtrl_Tmc*		m_pclsTmc;//Tmc�M��
			#endif

			#ifdef _DDst
				CCtrl_Dst*		m_pclsDst;//�x�W�Y�ɸ��p��
			#endif
			
			#ifdef _DAR
				CCtrl_AR*		m_pclsAR;//Nearby City
				nuBOOL			m_bARFindnode;
				nuBOOL			m_bARNearbyAR;
				AStarData		m_sARData[5];
				nuINT				m_iARCount;
			#endif
			
			#ifdef _DROUTE_ERROR
				nuLONG   m_lShortestDis;
				nuULONG   m_lShortestCount;
				AStarData		m_ShortestAStarData;
				WEIGHTINGSTRU   m_ShortestChoose;
				AStarData		*m_pShortestData; 
				WEIGHTINGSTRU   *m_pShortestweight;
				nuBOOL			m_bErrorExceptionHandle;
			#endif
			NUROTIME		nuTIME;	
			CCtrl_Thc*		m_pclsThc;//�����
			nuLONG			m_lMaxRoadClassCount;
			nuLONG			m_nRTSTARTSAMECLASSROAD;
			nuLONG			m_nRTFINDRTIDX;
			nuLONG			m_nRTSleep;
			nuLONG          m_nTMCSlowWeighting;
			nuLONG			m_nTMCCrowdWeighting;
	public:
	#ifdef LCMM
			nuLONG			m_lReadBaseData;
			nuLONG			m_lRouteCount;
	#endif
	#ifdef _DTMC
			nuBOOL			m_bTMCLocalRoute;
			nuLONG			m_lTMCDataCount;
			TMC_ROUTER_DATA *m_pTMCPassData;
	#endif
#ifdef _USERT6
			nuBOOL m_bReadRt6;
#endif
	#ifdef THRNodeList
			nuBOOL GetTHRNodeIDList(nuLONG MAPID,nuLONG FNodeID, nuLONG TNodeID, nuLONG RTBID);
	#endif	
//	#ifdef _USETTI
			NUROTIME m_NowTime;
			Class_TTICtrl *m_pTTI_F;
			Class_TTICtrl *m_pTTI_T;
//	#endif

	#ifdef THC_THR_LINK
			CCMPCtrl m_CMP;
			nuLONG m_Dif_X;
			nuLONG m_Dif_Y;
	#endif
	};

#endif