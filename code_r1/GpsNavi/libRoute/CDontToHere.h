#ifndef Def_DontToHere
	#define Def_DontToHere
	//�o�O�Ӻ޲z�� ��ت��O�ΨӶi��W�����G���޲z
	//�ثe���W���O �W����Ʊq�쥻��class�ରstruct
	//���O�쥻���Ҥ䴩���غc,�Ѻc�\�� �h��ѥ����Ӻ޲z
	//�ǥH�N ��ƥD�� �H�� ��ƺ޲z �o��ӳ�������

	#include "NuroDefine.h"
	#define	MaxDontToHereCount		20
	#define	EachTimeJoinCount		10
	#define DontToWorkingCount		1000
	#define MaxCongestionIDCount	128

	typedef struct Tag_DontToNodeID
	{
		nuULONG NodeID : 20;
		nuULONG RtBID : 12;
		nuULONG MapID : 16;
		nuULONG UseCount : 16;
		nuLONG  Index;
	}DontToNodeID,*LpDontToNodeID;

	class CDontToHere
	{
		public:
			CDontToHere();
			virtual ~CDontToHere();
			nuVOID InitConst();
			nuLONG CheckDontTo(nuULONG MapID, nuULONG RtBID, nuULONG NodeID);
			nuVOID JoinNewDontTo(nuULONG MapID, nuULONG RtBID, nuULONG NodeID, nuLONG Order);
			nuVOID SystemReRouting();

			//�먮�W������
			nuBOOL CheckCongestionID(nuDWORD NodeID);
			nuVOID JoinNewCongestionID(nuDWORD NodeID);
			nuVOID CleanCongestionID();

			nuBOOL b_CongestionRoute;

		private:
			nuLONG OrderFixWeighting(nuLONG Order);
			nuLONG OrderFixCount(nuLONG Order);
			DontToNodeID DontToPt[MaxDontToHereCount];
			nuLONG CheckCount;
			nuLONG Indexvalue;

			//�먮�W������
			nuLONG CongestionIDCount;
			nuDWORD CongestionID[MaxCongestionIDCount];
	};

#endif