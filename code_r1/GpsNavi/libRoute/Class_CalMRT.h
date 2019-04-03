#ifndef Def_Class_CalMRT
	#define Def_Class_CalMRT
	#include "NuroDefine.h"

	#include "RouteBase.h"
	#include "NuroEngineStructs.h"
	#include "AStar.h"
	#include "Class_Approach.h"
	#include "ConstSet.h"
	#include "Ctrl_MDW.h"
	#include "Ctrl_MRT.h"
	#include "Ctrl_Thc.h"
	#include "Ctrl_Thr.h"
	
	class Class_CalMRT
	{
		public:
			Class_CalMRT();
			virtual ~Class_CalMRT();

			nuBOOL AStar(AStarWork &m_AStar, nuULONG FMRTNodeID, nuULONG TMRTNodeID);//���|�W��
			nuVOID Astar_SRT(NUROPOINT TargetCoor, TagAStarData &m_SAVLData, AStarWork &m_AStar, nuULONG FMRTNodeID, nuULONG TMRTNodeID, WEIGHTINGSTRU BestChoose);
			nuLONG UONEGetGuessDistance(NUROPOINT Pt1,NUROPOINT PT2);//�p��w���Z��(�{�b�����P�p��Z���ۦP �p�G����n���w������ ����M�N���ܭp�⪺�覡)
			nuBOOL GetWeighting(nuLONG Class);
			nuBOOL GetNodeIDList(AStarWork &m_AStar);
			nuBOOL CreateLocalRoutingData(PNAVIRTBLOCKCLASS TmpNaviRtBlockClass);

			//Louis 081111 ���ѵ����ɱM��
			nuLONG CalMRTRouting_Coor(NUROPOINT PT_F, NUROPOINT PT_T, nuLONG &m_MRTGDis, nuLONG &m_MRTRDis);
			nuLONG CalMRTRouting_NodeID(nuLONG MRTID_F, nuLONG MRTID_T, nuLONG &m_MRTGDis, nuLONG &m_MRTRDis);
			nuVOID LeaveCalMRTRouting(AStarWork &m_AStar);

			//Louis 081111 ���ѵ�Route�i�滷�Z������
			nuLONG MRTRouting(PNAVIRTBLOCKCLASS pNRBC, nuLONG MRTID_F, nuLONG MRTID_T, nuLONG l_RoutingRule);
			nuVOID LeaveMRTRouting(AStarWork &m_AStar);

			nuBOOL LocalAStarSuccessWorkStep1(PNAVIRTBLOCKCLASS pNRBC);//�ϰ�W��(Local AStar)���\�������ƾ�z
			nuBOOL LocalAStarSuccessWorkStep2(PNAVIRTBLOCKCLASS pNRBC);//�ϰ�W��(Local AStar)���\�������ƾ�z
			nuBOOL LocalAStarSuccessWorkStep3(PNAVIRTBLOCKCLASS pNRBC);//�ϰ�W��(Local AStar)���\�������ƾ�z
			nuBOOL GetBlockRoadIdx(nuUSHORT *BlockIdx, nuUSHORT *RoadIdx, nuULONG FNodeID, nuULONG TNodeID);
			nuLONG GetDistance(NUROPOINT Pt1, NUROPOINT PT2);//�p��Z��
			nuLONG GetAngle(NUROPOINT FPt, NUROPOINT NPt, NUROPOINT TPt);

			nuBOOL LoadCalMRTRoutingData(nuLONG l_RoutingRule);
			nuBOOL FindNearEnd6Net(AStarWork &m_AStar, NUROPOINT &CLRS_T, nuLONG &Dis_Rd6, nuULONG &TMRTNodeID, nuULONG &LimitNodeID_6);
			nuVOID FreeCalMRTRoutingData();

			//��thc�ɱM��function
			nuLONG NewCalMRTRouting_NodeID(nuLONG MRTID_F, nuLONG MRTID_T, THCROUTEDATA &stuThcRouteData);

		private:
			CMDWCtrl		m_mdw;
			CMRTCtrl		m_mrt;
			nuLONG          ClassWeighting;//�����v��(���l)
			nuLONG          AveLatitude;

			nuLONG          MRTGDis;
			nuLONG          MRTRDis;
			nuLONG          TargetClass;
			AStarData		m_ApprocahAStarData;
			Class_Approach	Tmp_Approach;//Astar�W�e������d�U�Ӫ����(approach����)
			CCtrl_Thc**		ppclsThc;//�����
			Class_ThrCtrl**	ppclsGThr;//�����(thr)����ƼȦs��
	};

#endif

