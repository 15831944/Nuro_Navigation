#include "FileMapBaseZ.h"
#ifndef DEFINE_TMCSERVERFILECTRL
	#define DEFINE_TMCSERVERFILECTRL

    class CTMCServerFileCtrl : public CFileMapBaseZ
	{
		public:
			CTMCServerFileCtrl();
			virtual ~CTMCServerFileCtrl();
			nuBOOL ReadTMCServerFile(nuTCHAR *tsFilePath);
			nuINT	iServerTMCFileSize;//�����U���U�Ӫ��ɮפj�p
			nuBYTE	*pTMCServerData;//�Ψ��x�sŪ���X�Ӫ����buffer
            nuBOOL ReleaseServerFileStru();
		private:
			nuBOOL bReleaseServerFileOK;
	};


#endif
