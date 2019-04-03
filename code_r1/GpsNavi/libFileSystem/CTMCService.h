#include "FileMapBaseZ.h"
#include "CTMCCollation.h"
#ifndef DEFINE_CTMCSERVICE
	#define DEFINE_CTMCSERVICE

extern PFILESYSAPI	g_pTMCFSApi;

	class CTMCService : public CFileMapBaseZ
	{
	public:
		CTMCService();
		virtual ~CTMCService();
		nuBOOL Copy_TMC_Event_Data(nuBYTE nDWIdx);
		nuBOOL Initial_TMC_Event_Data(nuBYTE nDWIdx);//����TMCMapping�MTMCServer���
		nuVOID Release_TMC_Event_Data(nuBYTE nDWIdx);//����TMCMapping�MTMCServer���
		nuBOOL Initial_TMC_Data(nuINT iCount);
		nuVOID Release_TMC_Data();
		nuUINT GetTMCTrafficInfo(nuBYTE nDWIdx, nuUINT BlockID,nuUINT RoadID);           //���o�D����q���p
		nuUINT GetTMCTrafficInfoByNodeID(nuBYTE nDWIdx, nuUINT NodeID1,nuUINT NodeID2);  //���o�D����q���p
		nuUINT GetTMCDirInfo(nuBYTE nDWIdx, nuUINT BlockID,nuUINT RoadID);				 //���o�D����V��
		nuUINT GetTMCDirInfoByNodeID(nuBYTE nDWIdx, nuUINT NodeID1,nuUINT NodeID2);		 //���o�D����V��
		TMCRoadInfoStru* GetTMCDataInfo(nuBYTE nDWIdx, nuUINT BlockID,nuUINT RoadID);
		CTMCCollation *tmpTMCCollation;
		nuUINT *p_index;
		nuINT nCount;
	};
#endif
