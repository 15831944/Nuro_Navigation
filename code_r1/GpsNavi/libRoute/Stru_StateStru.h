// Copyright (c) 2005 PLink Corp.  All rights reserved.
// $Author: louis $
// $Date: 2009/09/18 05:52:00 $
// $Revision: 1.2 $
#ifndef Def_Stru_StateStru
	#define Def_Stru_StateStru
	typedef struct Tag_StateStru
	{
		nuULONG MapID;//�ϸ�o��ɩҽᤩ�����ޭ�
		nuLONG  MapIdx;//FileNameSystem�ҽᤩ�����ޭ�
		nuULONG RtBlockID;//�ϸ�o��ɩҽᤩ��RtBlock���ޭ�
		nuLONG  RtBlockIdx;//�B��L�{���ҽᤩ��RtBlock���ޭ�(�z�פW�|�PRtBlockID�۵�)
		nuLONG  DwBlockID;//GlobeBlockID
		nuLONG  DwBlockIdx;//�B��L�{���ҽᤩ��Block���ޭ�
	}StateStru,*pStateStru;
#endif