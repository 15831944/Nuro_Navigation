#include "FileMapBaseZ.h"
#ifndef DEFINE_KDTMCCTRL
	#define DEFINE_KDTMCCTRL

	typedef struct tagKDTMCFileHeaderStruct
	{
		nuUINT DataCnt;
		nuUINT NodeDataAddr;
		nuBYTE Reserve[92];
	}KDTMCFileHeaderStruct,*pKDTMCFileHeaderStruct;

	typedef struct tagKDTMCFileMainDataStruct
	{
		nuUINT MeshID:24;
		nuUINT RoadClass:8;
		nuUINT LinkID:16;
		nuUINT LocationCodeNum:16;
		nuUINT LocationVertexAddr;  //Ū����n�]�k��˦��_�lIndex ���M�����H��Ʈw���覡�ާ@
	}KDTMCFileMainDataStruct,*pKDTMCFileMainDataStruct;

	typedef struct tagKDTMCFileNodeIDDataStruct
	{
		nuUINT NameAddr;
		nuUINT StartNode;
		nuUINT EndNode;
		nuUINT BlockID;
		nuUINT RoadID;
		nuUINT Dir:8;
		nuUINT TrafficEvent:24;  //Reserve ��o�@�X���Ӹ˶�D����q���p
	}KDTMCFileNodeIDDataStruct,*pKDTMCFileNodeIDDataStruct;

	typedef struct tagKDTMCFileStruct
	{
		KDTMCFileHeaderStruct		KDTMCHeader;
		KDTMCFileMainDataStruct		*pKDTMCMain;
		KDTMCFileNodeIDDataStruct	*pKDTMCNode;
	}KDTMCFileStruct,*pKDTMCFileStruct;

	class CKDTMCFileCtrl : public CFileMapBaseZ 
	{
		public:
			CKDTMCFileCtrl();
			virtual ~CKDTMCFileCtrl();
			nuBOOL ReadTMCFile(nuTCHAR *tsFilePath);
			nuVOID CopyTMCStru();
			KDTMCFileStruct	TMCStru;
			KDTMCFileStruct	TMCStru2;
			nuUINT TotalNodeDataCount;
			nuUINT TotalNodeDataCount2;
			nuBOOL ReleaseTMCStru();
			nuVOID ReleaseTMCStru2();
			nuBOOL m_bUseTMC;
		private:
			nuBOOL bReleaseTMCFileOK;
			
	};

#endif
