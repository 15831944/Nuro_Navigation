#ifndef Def_RoutingDataCtrl
	#define Def_RoutingDataCtrl
	//�o�O�Ӻ޲z�� ��ت��O�ΨӶi��W�����G���޲z
	//�ثe���W���O �W����Ʊq�쥻��class�ରstruct
	//���O�쥻���Ҥ䴩���غc,�Ѻc�\�� �h��ѥ����Ӻ޲z
	//�ǥH�N ��ƥD�� �H�� ��ƺ޲z �o��ӳ�������
	#include "NuroEngineStructs.h"
	class CRoutingDataCtrl
	{
		public:
			CRoutingDataCtrl();
			virtual ~CRoutingDataCtrl();

			nuVOID Release_RoutingData(PROUTINGDATA &NaviData);


			nuBOOL Create_NaviFromToClass(PNAVIFROMTOCLASS &NaviData);
			nuVOID Release_NaviFromToClass(PNAVIFROMTOCLASS &NaviData);

			nuBOOL Create_NaviRtBlockClass(PNAVIRTBLOCKCLASS &NaviData);
			nuVOID Release_NaviRtBlockClass(PNAVIRTBLOCKCLASS &NaviData);


			nuBOOL Create_NaviSubClass(PNAVIRTBLOCKCLASS &NRBC,nuULONG Count);
			nuVOID Release_NaviSubClass(PNAVIRTBLOCKCLASS &NRBC);
			nuBOOL new_NaviSubClass(PNAVISUBCLASS &NaviData,nuLONG Count);
			nuVOID delete_NaviSubClass(PNAVISUBCLASS &NaviData);
			nuBOOL Create_NodeIDList(PNAVIRTBLOCKCLASS &NRBC,nuULONG Count);
			nuVOID Release_NodeIDList(PNAVIRTBLOCKCLASS &NRBC);

			nuBOOL Create_CrossData(NAVISUBCLASS &NSS,nuLONG Count);
			nuVOID Release_CrossData(NAVISUBCLASS &NSS);
			nuBOOL Create_ArcPt(NAVISUBCLASS &NSS,nuLONG Count);
			nuVOID Release_ArcPt(NAVISUBCLASS &NSS);
	};

#endif