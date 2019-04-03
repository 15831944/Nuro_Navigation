#include "FileMapBaseZ.h"
#include "nuRouteData.h"
#ifndef DEFINE_CTMCCOLLATION
	#define DEFINE_CTMCCOLLATION

 
	class CTMCCollation : public CFileMapBaseZ
	{
		public:
			CTMCCollation();
			virtual ~CTMCCollation();
			nuBOOL Copy_TMC_Event_Data();
			nuBOOL LoadTMCMappingFile(nuTCHAR *tsFilePath);//����TMCMapping���
			nuBOOL LoadServerTMCFile(nuTCHAR *tsFilePath);//�U��Server�W��TMC��T
			nuBOOL CombineData();
			nuUINT GetTMCTraffic(nuUINT BlockID,nuUINT RoadID);
			nuUINT GetTMCTrafficByNodeID(nuUINT NodeID1,nuUINT NodeID2);
			nuUINT GetTMCDir(nuUINT BlockID,nuUINT RoadID);
			nuUINT GetTMCDirByNodeID(nuUINT NodeID1,nuUINT NodeID2);
			TMCRoadInfoStru* GetTMCData(nuUINT BlockID,nuUINT RoadID);
			TMCRoadInfoStru RoadInfo[2];
            nuBOOL ReleaseTMCMappingFile();
			nuBOOL ReleaseServerTMCFile();
			nuUINT tickcount;
		private:
			nuBOOL MergeData(nuINT MeshID,nuINT RoadClass,nuINT LinkID,nuINT TrafficEvent);
			nuVOID ShellSort();
			nuVOID SortRoadID();
			nuVOID SortNodeIDFT();

			nuBOOL bLoadTMCMappingOK;
			nuBOOL bLoadServerTMCOK;
			nuUINT *pRoadIDSortBuffer;//RoadID�M�αƧ�
			nuUINT *pNodeIDFTSortBuffer;//NodeID��F��T�M�αƧ�

			nuUINT *m_pUse_RoadIDSortBuffer;
			nuUINT *m_pUse_NodeIDFTSortBuffer;
			nuUINT m_nTotalNodeDataCount;
			nuBOOL m_bChangeData;
			nuBOOL m_bCopy;
	        //multimap<int,int> m_traffFindMap;
	};

#endif
