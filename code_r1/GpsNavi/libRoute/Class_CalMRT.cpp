
#include "stdAfxRoute.h"
#include "Class_CalMRT.h"
#include "Ctrl_RuleSet.h"
#include "CRoutingDataCtrl.h"
#include "AllSystemDataBase.h"

//#include "AllSystemDataBase.h"

Class_CalMRT::Class_CalMRT()
{
	ClassWeighting=0;//�����v��(���l)
	AveLatitude=0;
	MRTGDis=0;
	MRTRDis=0;
	TargetClass=0;
}

Class_CalMRT::~Class_CalMRT()
{
	ClassWeighting=0;//�����v��(���l)
	AveLatitude=0;
	MRTGDis=0;
	MRTRDis=0;
	TargetClass=0;
	Tmp_Approach.ReleaseApproach();//Astar�W�e������d�U�Ӫ����(approach����)
}

nuBOOL Class_CalMRT::AStar(AStarWork &m_AStar, nuULONG FMRTNodeID, nuULONG TMRTNodeID)//�W��
{
	LpAVLTree p_SAVLTree = NULL;
	AStarData m_AStarData = {0}, tmp_SAVLData = {0};
	NUROPOINT CLRS_F,CLRS_T = {0};
	nuLONG tmp_GuessDis = 0;
	WEIGHTINGSTRU BestChoose = {0}, NewWeighting = {0};
	nuULONG LimitNodeID_6 = -1;
	
	CLRS_F=(*m_mrt.RtBMain)[FMRTNodeID].NodeCoor;
	CLRS_T=(*m_mrt.RtBMain)[TMRTNodeID].NodeCoor;
	
	AveLatitude=nulCos(NURO_ABS((CLRS_T.y + CLRS_F.y) / 2) / _EACHDEGREECOORSIZE) * 1113 / _LONLATBASE;
/*
	if(!FindNearEnd6Net(m_AStar, CLRS_T, Dis_Rd6,TMRTNodeID,LimitNodeID_6, Class6_pass))//�����n�~�[�W�h
	{//�p�G�q���I���^�h�S����ƪ�ܿ��~�A��ܨõL�s�����I���D��
		return nuFALSE;
	}
*/
	// ��l��AStar�Ȧs��Ƶ��c
	m_AStar.IniData();
	//�_�I���NodeID�ۦP(�b���I�W)	�h�����ѳo�@�I�X��
	//�_�I���NodeID���P(�b���W)	�h����ݳq�槡�i
	m_AStarData.FMapID = 0;	m_AStarData.FRtBID = 0;	m_AStarData.FNodeID = FMRTNodeID;
	m_AStarData.NMapID = 0;	m_AStarData.NRtBID = 0;	m_AStarData.NNodeID = FMRTNodeID;
	m_AStarData.TMapID = 0;	m_AStarData.TRtBID = 0;	m_AStarData.TNodeID = FMRTNodeID;
	m_AStarData.FMapLayer = m_AStarData.NMapLayer = m_AStarData.TMapLayer   = _MAPLAYER_SRT;
	m_AStarData.Class		= _GENERALRDLEVEL;
	m_AStarData.FNoTurnFlag = 0;
	m_AStarData.NNoTurnFlag = 0;
	m_AStarData.TNoTurnFlag = 0;
	m_AStarData.RDis = 0;

	tmp_GuessDis=UONEGetGuessDistance((*m_mrt.RtBMain)[m_AStarData.TNodeID].NodeCoor,CLRS_T);
	
	NewWeighting.RealDis=0;
	m_AStarData.NowDis=0;
	m_AStarData.RDis=0;
	NewWeighting.TotalDis=tmp_GuessDis+m_AStarData.NowDis+m_AStarData.RDis;
	m_AStarData.FNoTurnFlag=0;
	m_AStarData.NNoTurnFlag=0;
	m_AStarData.TNoTurnFlag=0;
	m_AStar.AddToOpen(m_AStarData,m_AStarData.TMapLayer,NewWeighting);
	
	//�[�J�Ĥ@�����ޥ��ܭ��n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//���ѭץ�
	//�[�J�Ĥ@����ƶi�Jopen��
	while(nuTRUE)
	{
		if(b_StopRoute) return nuFALSE;
		//���o���uOpen�ݸ�� ��JClose��
		if(!m_AStar.GetBestOpenToClose(p_SAVLTree,BestChoose)){
			MRTGDis=-1;
			MRTRDis=-1;
			TargetClass=-1;
			return nuFALSE;
		}

		if( p_SAVLTree->Data.TNodeID==TMRTNodeID ){//���I�I��N����	
			nuMemcpy(&m_ApprocahAStarData,&(p_SAVLTree->Data),MappingCheckByte_l);//�ΨӨ��o�̫�@����� ��ɭԭn�Φb�^���W
			m_ApprocahAStarData.NMapLayer=p_SAVLTree->Data.NMapLayer;
			m_ApprocahAStarData.TMapLayer=p_SAVLTree->Data.TMapLayer;
			MRTGDis=BestChoose.TotalDis;
			MRTRDis=BestChoose.RealDis;
			TargetClass=p_SAVLTree->Data.Class;
			return nuTRUE;
		}
		nuMemcpy(&(tmp_SAVLData),&(p_SAVLTree->Data),sizeof(TagAStarData));
		Astar_SRT(CLRS_T,tmp_SAVLData,m_AStar,FMRTNodeID,TMRTNodeID,BestChoose);
		//�p�G�ϥγo�Ӥ覡 �h�ݭn��ƻ��U		Astar_SRT(CLRS_T,p_SAVLTree->Data,m_AStar,FMRTNodeID,TMRTNodeID);
	}
	return nuFALSE;
}

//�Ʊ���X�̪񪺤��������I(class 0~6)
nuBOOL Class_CalMRT::FindNearEnd6Net(AStarWork &m_AStar, NUROPOINT &CLRS_T, nuLONG &Dis_Rd6, nuULONG &TMRTNodeID, nuULONG &LimitNodeID_6)
{
	LpAVLTree m_SAVLTree = {0};
	AStarData m_AStarData = {0};
	nuULONG i = 0;
	nuBOOL b_GotoNext=nuTRUE;
	m_AStar.IniData();
	nuLONG tmp_GuessDis = 0, NowConnectIdx = 0;
	WEIGHTINGSTRU BestChoose = {0}, NewWeighting = {0};
	
	m_AStarData.FMapID=0;	m_AStarData.FRtBID=0;	m_AStarData.FNodeID=TMRTNodeID;
	m_AStarData.NMapID=0;	m_AStarData.NRtBID=0;	m_AStarData.NNodeID=TMRTNodeID;

	//���[�W�ⵧ��Ʊq���I�X�o
	for(i=0;i<(*m_mrt.RtBMain)[m_AStarData.NNodeID].ConnectCount;i++)
	{
		NowConnectIdx=(*m_mrt.RtBMain)[m_AStarData.NNodeID].ConnectStruIndex+i;
		m_AStarData.TMapID=0;					
		m_AStarData.TRtBID=0;
		m_AStarData.TNodeID=(*m_mrt.RtBConnect)[NowConnectIdx].TNodeID;
		if(	m_AStarData.FNodeID==m_AStarData.TNodeID ) continue;
		//�T�������Y
		m_AStarData.FMapLayer=m_AStarData.NMapLayer=m_AStarData.TMapLayer = _MAPLAYER_SRT;
		tmp_GuessDis=UONEGetGuessDistance((*m_mrt.RtBMain)[m_AStarData.TNodeID].NodeCoor,CLRS_T);

		NewWeighting.RealDis=(*m_mrt.RtBConnect)[NowConnectIdx].RoadLength;
		m_AStarData.Class=(*m_mrt.RtBConnect)[NowConnectIdx].RoadClass;
		m_AStarData.FNoTurnFlag=1;
		m_AStarData.NNoTurnFlag=1;
		m_AStarData.TNoTurnFlag=1;
		
		if(!GetWeighting(m_AStarData.Class)) continue;
		m_AStarData.NowDis = ((*m_mrt.RtBConnect)[NowConnectIdx].RoadLength*ClassWeighting) / _WEIGHTINGBASE;
		m_AStarData.RDis   = 0;

		NewWeighting.TotalDis=tmp_GuessDis+m_AStarData.NowDis+m_AStarData.RDis;
		m_AStar.AddToOpen(m_AStarData,m_AStarData.TMapLayer,NewWeighting);
	}
	//���o���uOpen�ݸ�� ��JClose��
	if(!m_AStar.GetBestOpenToClose(m_SAVLTree,BestChoose))
	{
		return nuFALSE;
	}
	if(m_SAVLTree->Data.Class <= 6)
	{
		Dis_Rd6=BestChoose.RealDis;
		LimitNodeID_6=m_SAVLTree->Data.FNodeID;
		return nuTRUE;
	}
	return nuFALSE;
}

nuVOID  Class_CalMRT::Astar_SRT(NUROPOINT TargetCoor, TagAStarData &m_SAVLData, AStarWork &m_AStar, nuULONG FMRTNodeID, nuULONG TMRTNodeID, WEIGHTINGSTRU BestChoose)
{
	nuLONG tmp_GuessDis = 0, NowConnectIdx = 0;
	nuDWORD i = 0;
	AStarData m_AStarData = {0};
	WEIGHTINGSTRU NewWeighting = {0};

	m_AStarData.FMapID=m_SAVLData.NMapID;	m_AStarData.FRtBID=m_SAVLData.NRtBID;	m_AStarData.FNodeID=m_SAVLData.NNodeID;
	m_AStarData.NMapID=m_SAVLData.TMapID;	m_AStarData.NRtBID=m_SAVLData.TRtBID;	m_AStarData.NNodeID=m_SAVLData.TNodeID;
	
	for(i=0;i<(*m_mrt.RtBMain)[m_SAVLData.TNodeID].ConnectCount;i++)
	{
		NowConnectIdx=(*m_mrt.RtBMain)[m_SAVLData.TNodeID].ConnectStruIndex+i;
		m_AStarData.TMapID=0;					
		m_AStarData.TRtBID=0;					
		m_AStarData.TNodeID=(*m_mrt.RtBConnect)[NowConnectIdx].TNodeID;
		if(	m_AStarData.FNodeID==m_AStarData.TNodeID ) continue;
		//�T�������Y
		m_AStarData.FMapLayer = m_AStarData.NMapLayer = m_AStarData.TMapLayer = _MAPLAYER_SRT;
		tmp_GuessDis=UONEGetGuessDistance((*m_mrt.RtBMain)[m_AStarData.TNodeID].NodeCoor,TargetCoor);
//		tmp_GuessDis=0;
		NewWeighting.RealDis=BestChoose.RealDis+(*m_mrt.RtBConnect)[NowConnectIdx].RoadLength;
		m_AStarData.Class=(*m_mrt.RtBConnect)[NowConnectIdx].RoadClass;

//**************************2009.12.30 daniel�]���ٹD�W�[�ӭק�***********************************************//	
		if((m_SAVLData.Class > 5) && (NewWeighting.RealDis > 500000 && tmp_GuessDis > 500000))//���k�O�]�p�_�W�I��ݦU500KM���~�i�άٹD
		{//�_�I����I500Km�A���I��_�I��500Km�̡A�~�i�άٹD�A�p�G���W�L�F500Km�F�A�h���飼�󰪵��Ū��D��
			continue;			
		}
//**************************2009.12.30 daniel�]���ٹD�W�[�ӭק�***********************************************//

		m_AStarData.FNoTurnFlag=1;
		m_AStarData.NNoTurnFlag=1;
		m_AStarData.TNoTurnFlag=1;
		//if(m_AStarData.Class==1)		GetWeighting(0);
		//else if(m_AStarData.Class==2)	GetWeighting(4);
		if(!GetWeighting(m_AStarData.Class)) continue;
		m_AStarData.NowDis = ((*m_mrt.RtBConnect)[NowConnectIdx].RoadLength * ClassWeighting) / _WEIGHTINGBASE;
		m_AStarData.RDis=m_AStarData.NowDis+m_SAVLData.RDis+1;
		NewWeighting.TotalDis=tmp_GuessDis+m_AStarData.NowDis+m_AStarData.RDis;
		m_AStar.AddToOpen(m_AStarData,m_AStarData.TMapLayer,NewWeighting);	
	}
}

nuLONG Class_CalMRT::UONEGetGuessDistance(NUROPOINT Pt1, NUROPOINT PT2)//�p��w���Z��(�{�b�����P�p��Z���ۦP �p�G����n���w������ ����M�N���ܭp�⪺�覡)
{
	nuLONG X = 0, Y = 0;
	X = NURO_ABS(Pt1.x - PT2.x);
	Y = NURO_ABS(Pt1.y - PT2.y);

	if(X > 1000000)	
	{
		X = ((X / 100) * AveLatitude / nuGetlBase()) * 100;
	}
	else	
	{
		X = X * AveLatitude / nuGetlBase();
	}

	if(Y > 1000000)
	{
		Y = (Y / 100) * 1109 / 10; // ((Y/100)*1109/1000)*100;
	}
	else		
	{
		Y = Y * 1109 / _LONLATBASE;
	}

	return nulSqrt(X,Y);
/*
	nuLONG X,Y;
	X=NURO_ABS(Pt1.x-PT2.x)*AveLatitude/1000;
	Y=NURO_ABS(Pt1.y-PT2.y)*1109/1000;
	return ((X+Y)*7)/10;
*/
}

nuBOOL Class_CalMRT::GetWeighting(nuLONG Class)
{
	if(g_pRoutingRule->l_TotalSupportCount==0)//�ϥ��¤覡
	{
		switch(Class)
		{
			case 0:	ClassWeighting=10;	break;// 110/110
			case 1:	ClassWeighting=14;	break;// 110/80
			case 2:	ClassWeighting=16;	break;// 110/70
			case 3:	ClassWeighting=16;	break;// 110/70
			case 4:	ClassWeighting=22;	break;// 110/50
			case 5:	ClassWeighting=28;	break;// 110/40
			case 6:	ClassWeighting=37;	break;// 110/30
			case 7:	ClassWeighting=37;	break;// 110/30
			case 8:	ClassWeighting=37;	break;// 110/30
			case 9:	ClassWeighting=37;	break;// 110/30
			case 10:	ClassWeighting=37;	break;// 110/30
			default:	ClassWeighting=37;	break;// 110/30
		}
	}
	else
	{
		if(Class>=g_pRoutingRule->l_TotalSupportCount)
		{
			ClassWeighting=*(g_pRoutingRule->l_Weighting)[g_pRoutingRule->l_TotalSupportCount-1];
		}
		else
		{
			ClassWeighting=*(g_pRoutingRule->l_Weighting)[Class];
		}
	}
	if(ClassWeighting==0) return nuFALSE;
	return nuTRUE;
}


nuBOOL Class_CalMRT::GetNodeIDList(AStarWork &m_AStar)
{
	nuULONG i = 0, CheckCount = 0;
	nuULONG TmpCount = 0;
	LpAVLTree p_AVLTree=NULL;
	NodeListStru **TmpList=NULL;

	/*** ��l�Ʀs�x���c ***/
	Tmp_Approach.ReleaseApproach();

	/*** ���ͦs��NodeList���L�{���c ***/
	TmpCount=0;
	if(m_AStar.lUsedCloseCount>2000){
		CheckCount=1000+m_AStar.lUsedCloseCount/2;
		TmpList=(NodeListStru**)g_pRtMMApi->MM_AllocMem(sizeof(Tag_NodeListStru)*CheckCount);
	}
	else{
		CheckCount=m_AStar.lUsedCloseCount+2;
		TmpList=(NodeListStru**)g_pRtMMApi->MM_AllocMem(sizeof(Tag_NodeListStru)*CheckCount);
	}

	if(TmpList==NULL){
		return nuFALSE;
	}

	/*** ���o�q���׺�Node����� ***/
	m_ApprocahAStarData.FNoTurnFlag=1;
	m_ApprocahAStarData.NNoTurnFlag=1;
	m_ApprocahAStarData.TNoTurnFlag=1;
	if(!m_AStar.GetGivenData(m_ApprocahAStarData,p_AVLTree,m_ApprocahAStarData.TMapLayer))
	{	g_pRtMMApi->MM_FreeMem((nuPVOID*)TmpList);	TmpList=NULL;	return nuFALSE;	}

	/*** �ɧ����ʧ@�B�z���F �N�n�}�l��z���㪺�L�{�o ***/
	(*TmpList)[TmpCount].NodeID=p_AVLTree->Data.TNodeID;	(*TmpList)[TmpCount].RtBID=p_AVLTree->Data.TRtBID;	(*TmpList)[TmpCount].MapID=p_AVLTree->Data.TMapID;	(*TmpList)[TmpCount].MapLayer=p_AVLTree->Data.TMapLayer;
	TmpCount++;
	(*TmpList)[TmpCount].NodeID=p_AVLTree->Data.NNodeID;	(*TmpList)[TmpCount].RtBID=p_AVLTree->Data.NRtBID;	(*TmpList)[TmpCount].MapID=p_AVLTree->Data.NMapID;	(*TmpList)[TmpCount].MapLayer=p_AVLTree->Data.NMapLayer;
	TmpCount++;

	while(!(p_AVLTree->Data.FNodeID==p_AVLTree->Data.NNodeID && p_AVLTree->Data.FRtBID==p_AVLTree->Data.NRtBID && p_AVLTree->Data.FMapID==p_AVLTree->Data.NMapID))
	{
		m_ApprocahAStarData.NMapID=p_AVLTree->Data.FMapID;
		m_ApprocahAStarData.NRtBID=p_AVLTree->Data.FRtBID;				m_ApprocahAStarData.NNodeID=p_AVLTree->Data.FNodeID;
		m_ApprocahAStarData.NMapLayer=p_AVLTree->Data.FMapLayer;
		m_ApprocahAStarData.TMapID=p_AVLTree->Data.NMapID;
		m_ApprocahAStarData.TRtBID=p_AVLTree->Data.NRtBID;				m_ApprocahAStarData.TNodeID=p_AVLTree->Data.NNodeID;
		m_ApprocahAStarData.TMapLayer=p_AVLTree->Data.NMapLayer;
		m_ApprocahAStarData.FNoTurnFlag=1;
		m_ApprocahAStarData.NNoTurnFlag=1;
		m_ApprocahAStarData.TNoTurnFlag=1;

		if(!m_AStar.GetGivenData(m_ApprocahAStarData,p_AVLTree,m_ApprocahAStarData.TMapLayer))
		{
			m_ApprocahAStarData.FNoTurnFlag=0;
			m_ApprocahAStarData.NNoTurnFlag=0;
			m_ApprocahAStarData.TNoTurnFlag=0;
			if(!m_AStar.GetGivenData(m_ApprocahAStarData,p_AVLTree,m_ApprocahAStarData.TMapLayer))
			{
				g_pRtMMApi->MM_FreeMem((nuPVOID*)TmpList);	TmpList=NULL;	return nuFALSE;
			}
		}

		if(CheckCount<=TmpCount){
			return nuFALSE;
		}

		(*TmpList)[TmpCount].NodeID=p_AVLTree->Data.NNodeID;
		(*TmpList)[TmpCount].RtBID=p_AVLTree->Data.NRtBID;
		(*TmpList)[TmpCount].MapID=p_AVLTree->Data.NMapID;
		(*TmpList)[TmpCount].MapLayer=p_AVLTree->Data.NMapLayer;
//		(*TmpList)[TmpCount].RunDis=p_AVLTree->Data.RealDis;
		TmpCount++;
	}

//FILE *fff;
//fff=fopen("c:\\MRTTracelog.txt","wb");
	if(nuFALSE==Tmp_Approach.CreateApproach(TmpCount-1))
	{
		g_pRtMMApi->MM_FreeMem((nuPVOID*)TmpList);	(*TmpList)=NULL;	return nuFALSE;	}

	for(i=0;i<TmpCount;i++){
		(*Tmp_Approach.p_Approach)[i].FMapID	=	(*TmpList)[TmpCount-i-1].MapID;
		(*Tmp_Approach.p_Approach)[i].FMapLayer	=	(*TmpList)[TmpCount-i-1].MapLayer;
		(*Tmp_Approach.p_Approach)[i].FRtBID	=	(*TmpList)[TmpCount-i-1].RtBID;
		(*Tmp_Approach.p_Approach)[i].FNodeID	=	(*TmpList)[TmpCount-i-1].NodeID;
		(*Tmp_Approach.p_Approach)[i].TMapID	=	(*TmpList)[TmpCount-i-2].MapID;
		(*Tmp_Approach.p_Approach)[i].TMapLayer	=	(*TmpList)[TmpCount-i-2].MapLayer;
		(*Tmp_Approach.p_Approach)[i].TRtBID	=	(*TmpList)[TmpCount-i-2].RtBID;
		(*Tmp_Approach.p_Approach)[i].TNodeID	=	(*TmpList)[TmpCount-i-2].NodeID;

//fprintf(fff,"%ld %ld\n",(*Tmp_Approach.p_Approach)[i].FNodeID,(*Tmp_Approach.p_Approach)[i].TNodeID);
	}
//fclose(fff);

	// �N�L�{��Ʋ���
	if(TmpList!=NULL)
	{
		g_pRtMMApi->MM_FreeMem((nuPVOID*)TmpList);
		TmpList=NULL;
	}
	TmpCount=0;
	return nuTRUE;
}

nuBOOL Class_CalMRT::CreateLocalRoutingData(PNAVIRTBLOCKCLASS TmpNaviRtBlockClass)
{
	nuLONG i,TmpRtBCount=0,TmpNSSCount=0;
	TmpRtBCount=0;
	TmpNSSCount=0;
	if(!g_pCRDC->Create_NaviSubClass(TmpNaviRtBlockClass,Tmp_Approach.ApproachCount)){
		g_pCRDC->Release_NaviSubClass(TmpNaviRtBlockClass);
		return nuFALSE;
	}
	if(!g_pCRDC->Create_NodeIDList(TmpNaviRtBlockClass,Tmp_Approach.ApproachCount+1)){
		g_pCRDC->Release_NodeIDList(TmpNaviRtBlockClass);
		return nuFALSE;
	}

	TmpRtBCount=0;
	TmpNSSCount=0;
	//�}�l����
	for(i=0;i<Tmp_Approach.ApproachCount;i++){
		if(i==0){
			TmpNaviRtBlockClass->FInfo.MapID = (*Tmp_Approach.p_Approach)[i].FMapID;
			TmpNaviRtBlockClass->FInfo.RTBID = (*Tmp_Approach.p_Approach)[i].FRtBID;
			TmpNaviRtBlockClass->FInfo.FixNode1 = (*Tmp_Approach.p_Approach)[i].FNodeID;
			TmpNaviRtBlockClass->FInfo.FixNode2 = (*Tmp_Approach.p_Approach)[i].TNodeID;
			TmpNaviRtBlockClass->FInfo.FixCoor.x =	(*m_mrt.RtBMain)[(*Tmp_Approach.p_Approach)[i].FNodeID].NodeCoor.x;
			TmpNaviRtBlockClass->FInfo.FixCoor.y =	(*m_mrt.RtBMain)[(*Tmp_Approach.p_Approach)[i].FNodeID].NodeCoor.y;
			TmpNaviRtBlockClass->FInfo.FixDis = 0;
				
			TmpNSSCount=0;
			TmpNaviRtBlockClass->NodeIDList[TmpNSSCount]=(*Tmp_Approach.p_Approach)[i].FNodeID;
			TmpNSSCount++;
		}
		TmpNaviRtBlockClass->TInfo.MapID = (*Tmp_Approach.p_Approach)[i].TMapID;
		TmpNaviRtBlockClass->TInfo.RTBID = (*Tmp_Approach.p_Approach)[i].TRtBID;
		TmpNaviRtBlockClass->TInfo.FixNode1 = (*Tmp_Approach.p_Approach)[i].TNodeID;
		TmpNaviRtBlockClass->TInfo.FixNode2 = (*Tmp_Approach.p_Approach)[i].FNodeID;
		TmpNaviRtBlockClass->TInfo.FixCoor.x =	(*m_mrt.RtBMain)[(*Tmp_Approach.p_Approach)[i].TNodeID].NodeCoor.x;
		TmpNaviRtBlockClass->TInfo.FixCoor.y =	(*m_mrt.RtBMain)[(*Tmp_Approach.p_Approach)[i].TNodeID].NodeCoor.y;
		TmpNaviRtBlockClass->NodeIDList[TmpNSSCount]=(*Tmp_Approach.p_Approach)[i].TNodeID;
		TmpNSSCount++;
		TmpNaviRtBlockClass->TInfo.FixDis = 0;
	}
	return nuTRUE;
}

nuBOOL Class_CalMRT::LoadCalMRTRoutingData(nuLONG l_RoutingRule)
{
	//����RoutingRule���
	if(!g_pRoutingRule->ReadRoutingRule(l_RoutingRule))
	{
		g_pRoutingRule->ReleaseRoutingRule(); 
		return nuFALSE;
	}

	//����MRT���
	#ifdef DEF_MAKETHRROUTE
		nuTcscpy(m_mrt.FName, MakeThr_MapPath);
		nuTcscat(m_mrt.FName, nuTEXT(".mrt"));
	#else
		nuTcscpy(m_mrt.FName, nuTEXT(".mrt"));
		g_pRtFSApi->FS_FindFileWholePath(-1,m_mrt.FName,NURO_MAX_PATH);
	#endif
	m_mrt.Read_Header(0);
	m_mrt.Read_MainData();
	m_mrt.Read_Connect();
	m_mrt.Read_Index();

	#ifdef DEF_MAKETHRROUTE
		nuTcscpy(m_mdw.FName, MakeThr_MapPath);
		nuTcscat(m_mdw.FName, nuTEXT(".mdw"));
	#else
		nuTcscpy(m_mdw.FName, nuTEXT(".mdw"));
		g_pRtFSApi->FS_FindFileWholePath(-1,m_mdw.FName,NURO_MAX_PATH);
	#endif
	m_mdw.Read_Header();
	for(nuDWORD i=0;i<m_mdw.Header.m_TotalBlockCount;i++)
	{
		m_mdw.Read_BlockData(i);
	}

	return nuTRUE;
}

nuVOID Class_CalMRT::FreeCalMRTRoutingData()
{
	for(nuDWORD i=0;i<m_mdw.Header.m_TotalBlockCount;i++)
	{
		m_mdw.Remove_BlockData(i);
	}
	m_mdw.Remove_Header();

	m_mrt.Remove_Connect();
	m_mrt.Remove_MainData();
	m_mrt.Remove_Header();
	g_pRoutingRule->ReleaseRoutingRule();
}

//�p���v��
nuLONG Class_CalMRT::CalMRTRouting_NodeID(nuLONG MRTID_F, nuLONG MRTID_T, nuLONG &m_MRTGDis, nuLONG &m_MRTRDis)
{
	nuULONG FMRTNodeID=0,TMRTNodeID=0;
	AStarWork		m_AStar;//AStar�B�� �֤ߪ���
	m_AStar.m_AVLTree.CreateBaseAVLTreeArray();
	m_MRTGDis=-1;
	m_MRTRDis=-1;

	if(nuFALSE==AStar(m_AStar,MRTID_F,MRTID_T)){
//		g_pRoutingRule->ReleaseRoutingRule();
		LeaveCalMRTRouting(m_AStar);
		return nuFALSE;
	}

	m_MRTGDis=MRTGDis;
	m_MRTRDis=MRTRDis;

	LeaveCalMRTRouting(m_AStar);//�o��class�n���~�ɩӱ� �����h���i��x��
	return ROUTE_SUCESS;
}


nuLONG Class_CalMRT::NewCalMRTRouting_NodeID(nuLONG MRTID_F, nuLONG MRTID_T, THCROUTEDATA &stuThcRouteData)
{
	nuLONG  i = 0;
	nuDWORD j = 0;
	nuULONG FMRTNodeID=0,TMRTNodeID=0;
	nuUSHORT TmpBlockIdx = 0, TmpRoadIdx = 0, SaveRTBIdx = 0, SaveMapIdx = 0;
	AStarWork		m_AStar;//AStar�B�� �֤ߪ���
	m_AStar.m_AVLTree.CreateBaseAVLTreeArray();
	if(nuFALSE==AStar(m_AStar,MRTID_F,MRTID_T))
	{
		LeaveCalMRTRouting(m_AStar);
		return nuFALSE;
	}
	if(!GetNodeIDList(m_AStar)){	LeaveCalMRTRouting(m_AStar);	return ROUTE_MRT_APPROACHFALSE;		}

	SaveMapIdx = _MAXUNSHORT;
	SaveRTBIdx = _MAXUNSHORT;
	stuThcRouteData.PassRTBCount=0;
	stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount].MapID=0;
	stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount].RTBID=0;
	stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount].MRTNODEID=(*Tmp_Approach.p_Approach)[0].FNodeID;
	stuThcRouteData.PassRTBCount++;
	for(i=1;i<Tmp_Approach.ApproachCount;i++)
	{
		TmpBlockIdx = _MAXUNSHORT;
		TmpRoadIdx  = _MAXUNSHORT;
		GetBlockRoadIdx(&TmpBlockIdx,&TmpRoadIdx,(*Tmp_Approach.p_Approach)[i].FNodeID,(*Tmp_Approach.p_Approach)[i].TNodeID);

		for(j=0;j<m_mdw.Header.m_TotalBlockCount;j++){
			if(TmpBlockIdx==(*m_mdw.Header.p_GBlockID)[j]){
				if(SaveRTBIdx==(*(*m_mdw.Rd)[j].p_RdData)[TmpRoadIdx].RTBID && SaveMapIdx==(*(*m_mdw.Rd)[j].p_RdData)[TmpRoadIdx].MapID)
				{
					stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount-1].MRTNODEID=(*Tmp_Approach.p_Approach)[i].TNodeID;
				}
				else
				{
					SaveRTBIdx=(*(*m_mdw.Rd)[j].p_RdData)[TmpRoadIdx].RTBID;
					SaveMapIdx=(*(*m_mdw.Rd)[j].p_RdData)[TmpRoadIdx].MapID;
					stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount].MapID=(*(*m_mdw.Rd)[j].p_RdData)[TmpRoadIdx].MapID;
					stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount].RTBID=(*(*m_mdw.Rd)[j].p_RdData)[TmpRoadIdx].RTBID;
					stuThcRouteData.stuPassRTBData[stuThcRouteData.PassRTBCount].MRTNODEID=(*Tmp_Approach.p_Approach)[i].TNodeID;
					stuThcRouteData.PassRTBCount++;
					/*if(stuThcRouteData.PassRTBCount >= 256)
					{
						stuThcRouteData.PassRTBCount=0;
						LeaveCalMRTRouting(m_AStar);
						return nuFALSE;
					}*/
				}
			}
		}
	}
	stuThcRouteData.RealDis		=	MRTRDis;
	stuThcRouteData.WeightDis	=	MRTGDis;
	LeaveCalMRTRouting(m_AStar);
	return ROUTE_SUCESS;
}


nuLONG Class_CalMRT::CalMRTRouting_Coor(NUROPOINT PT_F, NUROPOINT PT_T, nuLONG &m_MRTGDis, nuLONG &m_MRTRDis)
{
	nuULONG FMRTNodeID=900000000,TMRTNodeID=900000000, i = 0;
	nuLONG m_Dif_X = 0, m_Dif_Y = 0;
	AStarWork		m_AStar;//AStar�B�� �֤ߪ���
	m_AStar.m_AVLTree.CreateBaseAVLTreeArray();
	m_MRTGDis=-1;
	m_MRTRDis=-1;

	//�Ѯy�Ф��XMRTID
	for(i=0;i<m_mrt.RtBHeader.TotalNodeCount;i++){
		m_Dif_X=NURO_ABS((*m_mrt.RtBMain)[i].NodeCoor.x-PT_F.x);
		m_Dif_Y=NURO_ABS((*m_mrt.RtBMain)[i].NodeCoor.y-PT_F.y);
		if( 3>(m_Dif_X+m_Dif_Y) ){
			FMRTNodeID=i;
			break;
		}
	}

	for(i=0;i<m_mrt.RtBHeader.TotalNodeCount;i++){
		m_Dif_X=NURO_ABS((*m_mrt.RtBMain)[i].NodeCoor.x-PT_T.x);
		m_Dif_Y=NURO_ABS((*m_mrt.RtBMain)[i].NodeCoor.y-PT_T.y);
		if( 3>(m_Dif_X+m_Dif_Y) ){
			TMRTNodeID=i;
			break;
		}
	}

	if(FMRTNodeID==900000000 || TMRTNodeID==900000000){
		LeaveCalMRTRouting(m_AStar);
		return nuFALSE;
	}
	if(nuFALSE==AStar(m_AStar,FMRTNodeID,TMRTNodeID)){
		g_pRoutingRule->ReleaseRoutingRule();
		LeaveCalMRTRouting(m_AStar);
		return nuFALSE;
	}

	m_MRTGDis=MRTGDis;
	m_MRTRDis=MRTRDis;
	LeaveCalMRTRouting(m_AStar);//�o��class�n���~�ɩӱ� �����h���i��x��

	return ROUTE_SUCESS;
}

nuVOID Class_CalMRT::LeaveCalMRTRouting(AStarWork &m_AStar)
{
	Tmp_Approach.ReleaseApproach();
	m_AStar.IniData();
	m_AStar.m_AVLTree.RemoveBaseAVLTreeArray();//071015 Louis���C�O����ζq
}


nuLONG Class_CalMRT::MRTRouting(PNAVIRTBLOCKCLASS pNRBC, nuLONG MRTID_F, nuLONG MRTID_T, nuLONG l_RoutingRule)
{
	#ifdef	DEFNEWTHCFORMAT
		AStarWork		m_AStar;//AStar�B�� �֤ߪ���

		if(MRTID_T<2)
		{
			return ROUTE_SUCESS;
		}

		//���omrt������|
		#ifdef DEF_MAKETHRROUTE
			nuTcscpy(m_mrt.FName, MakeThr_MapPath);
			nuTcscat(m_mrt.FName, nuTEXT(".mrt"));
		#else
			nuTcscpy(m_mrt.FName, nuTEXT(".mrt"));
			g_pRtFSApi->FS_FindFileWholePath(-1,m_mrt.FName,NURO_MAX_PATH);
		#endif

		//���oMRT���
		if(!m_mrt.Read_Header(0)){	LeaveMRTRouting(m_AStar);	return ROUTE_READMRTFALSE;	}
		if(!m_mrt.Read_MainData()){	LeaveMRTRouting(m_AStar);	return ROUTE_READMRTFALSE;	}

		g_pRtMMApi->MM_CollectDataMem(1);
		ppclsThc=(CCtrl_Thc**)g_pRtMMApi->MM_AllocMem(sizeof(CCtrl_Thc));

		(*ppclsThc)->InitClass(l_RoutingRule);
		(*ppclsThc)->Read();
		(*ppclsThc)->ReadViaNodeData(MRTID_F,MRTID_T);

//		ppclsGThr=(Class_ThrCtrl**)g_pRtMMApi->MM_AllocMem(sizeof(Class_ThrCtrl));

		nuLONG i = 0, tmpmapid = 0;
		PNAVIRTBLOCKCLASS pSaveNaviRTBClass = NULL, pLastSaveNaviRTBClass = NULL, pTmpNaviRTBClass = NULL;
		tmpmapid=-1;
		pSaveNaviRTBClass=NULL;
		pLastSaveNaviRTBClass=NULL;
		pTmpNaviRTBClass=NULL;

		for(i=1;i<MRTID_T;i++)
		{
			if(pSaveNaviRTBClass==NULL)
			{
				pTmpNaviRTBClass=NULL;
				g_pCRDC->Create_NaviRtBlockClass(pTmpNaviRTBClass);
				pSaveNaviRTBClass=pTmpNaviRTBClass;
				pLastSaveNaviRTBClass=pTmpNaviRTBClass;
			}
			else
			{
				pTmpNaviRTBClass=NULL;
				g_pCRDC->Create_NaviRtBlockClass(pTmpNaviRTBClass);
				pLastSaveNaviRTBClass->NextRTB=pTmpNaviRTBClass;
				pLastSaveNaviRTBClass=pTmpNaviRTBClass;
			}
			pLastSaveNaviRTBClass->FInfo.MapID=(*(*ppclsThc)->ppstuViaNodeData)[i].MAPID;
			pLastSaveNaviRTBClass->TInfo.MapID=(*(*ppclsThc)->ppstuViaNodeData)[i].MAPID;
			pLastSaveNaviRTBClass->FInfo.RTBID=(*(*ppclsThc)->ppstuViaNodeData)[i].RTBID;
			pLastSaveNaviRTBClass->TInfo.RTBID=(*(*ppclsThc)->ppstuViaNodeData)[i].RTBID;
			pLastSaveNaviRTBClass->FInfo.FixCoor=(*m_mrt.RtBMain)[(*(*ppclsThc)->ppstuViaNodeData)[i-1].MRTNODEID].NodeCoor;
			pLastSaveNaviRTBClass->TInfo.FixCoor=(*m_mrt.RtBMain)[(*(*ppclsThc)->ppstuViaNodeData)[i].MRTNODEID].NodeCoor;
/*
			if((*(*ppclsThc)->ppstuViaNodeData)[i].MAPID!=tmpmapid)
			{
				tmpmapid=(*(*ppclsThc)->ppstuViaNodeData)[i].MAPID;
				for(j=0;j<m_MapIDtoMapIdx.MapCount;j++)
				{
					if( (*m_MapIDtoMapIdx.MapIDList)[j]==tmpmapid )
					{
						(*ppclsGThr)->ReSet();
						(*ppclsGThr)->InitClass(j,l_RoutingRule);
						(*ppclsGThr)->Read_Header();
						break;
					}
				}
			}

			for(j=0;j<(*ppclsGThr)->pThrEachMap.ThrHeader.TotalNodeCount;j++)
			{
				if(CheckPtCloseLU(pLastSaveNaviRTBClass->FInfo.FixCoor,(*(*ppclsGThr)->pThrEachMap.ThrMain)[j].NodeCoor,5))
				{
					for(k=0;k<(*(*ppclsGThr)->pThrEachMap.ThrMain)[j].ConnectCount;k++)
					{
						connectidx=k+(*(*ppclsGThr)->pThrEachMap.ThrMain)[j].ConnectStruIndex;
						if(	(*(*ppclsGThr)->pThrEachMap.ThrConnect)[connectidx].TMapLayer==2 && CheckPtCloseLU((*(*ppclsGThr)->pThrEachMap.ThrMain)[(*(*ppclsGThr)->pThrEachMap.ThrConnect)[connectidx].TNodeID].NodeCoor,pLastSaveNaviRTBClass->TInfo.FixCoor,5)	)
						{
								pLastSaveNaviRTBClass->RealDis=(*(*ppclsGThr)->pThrEachMap.ThrConnect)[connectidx].Length;
								break;
						}
					}
					break;
				}
			}
*/
			pLastSaveNaviRTBClass->NSSCount=1;
			g_pCRDC->Create_NaviSubClass(pLastSaveNaviRTBClass,pLastSaveNaviRTBClass->NSSCount);
			pLastSaveNaviRTBClass->NSS[0].ArcPtCount=2;
			g_pCRDC->Create_ArcPt(pLastSaveNaviRTBClass->NSS[0],pLastSaveNaviRTBClass->NSS[0].ArcPtCount);
			pLastSaveNaviRTBClass->NSS[0].ArcPt[0]=pLastSaveNaviRTBClass->FInfo.FixCoor;
			pLastSaveNaviRTBClass->NSS[0].ArcPt[1]=pLastSaveNaviRTBClass->TInfo.FixCoor;
			pLastSaveNaviRTBClass->NSS[0].RoadLength=pLastSaveNaviRTBClass->RealDis;
			pLastSaveNaviRTBClass->NSS[0].CityID=0;
			pLastSaveNaviRTBClass->NSS[0].TownID=0;
			pLastSaveNaviRTBClass->NSS[0].RoadNameAddr=0;
			pLastSaveNaviRTBClass->NSS[0].StartCoor=pLastSaveNaviRTBClass->FInfo.FixCoor;
			pLastSaveNaviRTBClass->NSS[0].EndCoor=pLastSaveNaviRTBClass->TInfo.FixCoor;
			
			if(pLastSaveNaviRTBClass->NSS[0].ArcPt[0].x>pLastSaveNaviRTBClass->NSS[0].ArcPt[1].x)
			{
				pLastSaveNaviRTBClass->NSS[0].Bound.left=pLastSaveNaviRTBClass->NSS[0].ArcPt[1].x;
				pLastSaveNaviRTBClass->NSS[0].Bound.right=pLastSaveNaviRTBClass->NSS[0].ArcPt[0].x;
			}
			else
			{
				pLastSaveNaviRTBClass->NSS[0].Bound.left=pLastSaveNaviRTBClass->NSS[0].ArcPt[0].x;
				pLastSaveNaviRTBClass->NSS[0].Bound.right=pLastSaveNaviRTBClass->NSS[0].ArcPt[1].x;
			}
			if(pLastSaveNaviRTBClass->NSS[0].ArcPt[0].y>pLastSaveNaviRTBClass->NSS[0].ArcPt[1].y)
			{
				pLastSaveNaviRTBClass->NSS[0].Bound.top=pLastSaveNaviRTBClass->NSS[0].ArcPt[1].y;
				pLastSaveNaviRTBClass->NSS[0].Bound.bottom=pLastSaveNaviRTBClass->NSS[0].ArcPt[0].y;
			}
			else
			{
				pLastSaveNaviRTBClass->NSS[0].Bound.top=pLastSaveNaviRTBClass->NSS[0].ArcPt[0].y;
				pLastSaveNaviRTBClass->NSS[0].Bound.bottom=pLastSaveNaviRTBClass->NSS[0].ArcPt[1].y;
			}
		}
		pTmpNaviRTBClass=pNRBC->NextRTB;
		pNRBC->NextRTB=pSaveNaviRTBClass;
		pLastSaveNaviRTBClass->NextRTB=pTmpNaviRTBClass;
//		(*ppclsGThr)->ReSet();
//		g_pRtMMApi->MM_FreeMem((nuPVOID*)ppclsGThr);
		LeaveMRTRouting(m_AStar);//�o��class�n���~�ɩӱ� �����h���i��x��
		return ROUTE_SUCESS;
	#else
		AStarWork		m_AStar;//AStar�B�� �֤ߪ���
		if(!m_AStar.m_AVLTree.CreateBaseAVLTreeArray()){	return ROUTE_NEWASTARSTRUCTFALSE;	}
		//�@�}�l�i�� ���c���ӬO�w�g�s�b�� �����c�|�H�W�������G�ӳQ���� ���i��|�ܦ��@�Ӧ�C
		if(pNRBC==NULL){	LeaveMRTRouting(m_AStar);	return ROUTE_ERROR;	}

		//���omrt������|
		#ifdef DEF_MAKETHRROUTE
			nuTcscpy(m_mrt.FName, MakeThr_MapPath);
			nuTcscat(m_mrt.FName, nuTEXT(".mrt"));
		#else
			nuTcscpy(m_mrt.FName, nuTEXT(".mrt"));
			g_pRtFSApi->FS_FindFileWholePath(-1,m_mrt.FName,NURO_MAX_PATH);
		#endif

		//���oMRT���
		if(!m_mrt.Read_Header(0)){	LeaveMRTRouting(m_AStar);	return ROUTE_READMRTFALSE;	}
		if(!m_mrt.Read_MainData()){	LeaveMRTRouting(m_AStar);	return ROUTE_READMRTFALSE;	}
		if(!m_mrt.Read_Connect()){	LeaveMRTRouting(m_AStar);	return ROUTE_READMRTFALSE;	}

		//�p����
		if(nuFALSE==AStar(m_AStar,MRTID_F,MRTID_T)){	LeaveMRTRouting(m_AStar);	return ROUTE_MRT_ASTARFALSE;		}

		if(!GetNodeIDList(m_AStar)){	LeaveMRTRouting(m_AStar);	return ROUTE_MRT_APPROACHFALSE;		}
		//���n�ޤ������ø��@��
		if(!CreateLocalRoutingData(pNRBC)){	LeaveMRTRouting(m_AStar);	return ROUTE_MRT_CREATEROUTEDATAFASLE;	}

		if(!LocalAStarSuccessWorkStep1(pNRBC)){	LeaveMRTRouting(m_AStar);	return ROUTE_ERROR;		}
		if(!LocalAStarSuccessWorkStep2(pNRBC)){	LeaveMRTRouting(m_AStar);	return ROUTE_ERROR;		}
		if(!LocalAStarSuccessWorkStep3(pNRBC)){	LeaveMRTRouting(m_AStar);	return ROUTE_ERROR;		}

		//�̫�n�d�UpNFTC����T ��L����ƭn�����M�� ��_�컪
		LeaveMRTRouting(m_AStar);//�o��class�n���~�ɩӱ� �����h���i��x��
		return ROUTE_SUCESS;
	#endif
}

nuVOID Class_CalMRT::LeaveMRTRouting(AStarWork &m_AStar)
{
	if(ppclsThc)
	{
		(*ppclsThc)->Remove();
		g_pRtMMApi->MM_FreeMem((nuPVOID*)ppclsThc);
		ppclsThc=NULL;
	}

	//remove MRT data
	m_mrt.Remove_Connect();
	m_mrt.Remove_MainData();
	m_mrt.Remove_Header();

	Tmp_Approach.ReleaseApproach();
	m_AStar.IniData();
	m_AStar.m_AVLTree.RemoveBaseAVLTreeArray();//071015 Louis���C�O����ζq
}

nuBOOL Class_CalMRT::LocalAStarSuccessWorkStep1(PNAVIRTBLOCKCLASS pNRBC)//AStar�W�����\���ʧ@
{
	nuULONG i = 0, j = 0;
	nuLONG TmpConnectIdx = 0;
	nuUCHAR WeightingClass = {0};
	//���o���q�_�WNode�y�� �è��oToNode���e����(���]�t�_�W�o�@�q��)
	for(i=0;i<pNRBC->NSSCount;i++){
		pNRBC->NSS[i].StartCoor.x=(*m_mrt.RtBMain)[pNRBC->NodeIDList[i]].NodeCoor.x;
		pNRBC->NSS[i].StartCoor.y=(*m_mrt.RtBMain)[pNRBC->NodeIDList[i]].NodeCoor.y;
		pNRBC->NSS[i].EndCoor.x=(*m_mrt.RtBMain)[pNRBC->NodeIDList[i+1]].NodeCoor.x;
		pNRBC->NSS[i].EndCoor.y=(*m_mrt.RtBMain)[pNRBC->NodeIDList[i+1]].NodeCoor.y;
		g_pCRDC->Create_CrossData(pNRBC->NSS[i],0);
	}
		
	//�û`����|���q�Υ�e���f�����שM���A
	for(i=0;i<pNRBC->NSSCount;i++)
	{
		WeightingClass			 = 0;
		pNRBC->NSS[i].RoadLength = _ROUTEDATABASERDLEN;
		//���o���Ī�(�_�W�I�۲�)�̵u����|���
		for(j=0;j<(*m_mrt.RtBMain)[pNRBC->NodeIDList[i]].ConnectCount;j++)
		{
			TmpConnectIdx=(*m_mrt.RtBMain)[pNRBC->NodeIDList[i]].ConnectStruIndex+j;
			if((*m_mrt.RtBConnect)[TmpConnectIdx].TNodeID==pNRBC->NodeIDList[i+1])
			{
				if(	pNRBC->NSS[i].RoadLength > (*m_mrt.RtBConnect)[TmpConnectIdx].RoadLength)
				{
					pNRBC->NSS[i].RoadLength	=	(*m_mrt.RtBConnect)[TmpConnectIdx].RoadLength;
					pNRBC->NSS[i].RoadVoiceType =	0;
					WeightingClass				=	(*m_mrt.RtBConnect)[TmpConnectIdx].RoadClass;
				}
			}
		}
		if(i!=0 && i!=(pNRBC->NSSCount-1)){//�p��[�v
			if(!GetWeighting(WeightingClass)) continue;
			pNRBC->WeightDis +=	pNRBC->NSS[i].RoadLength * ClassWeighting / _WEIGHTINGBASE;
		}
	}
	m_mrt.Remove_Connect();
	m_mrt.Remove_MainData();

	if(!m_mrt.Read_Index()) return nuFALSE;
	//���o���qRoadID
	for(i=0;i<pNRBC->NSSCount;i++)
	{
		//�Ѱ_�WNodeID�o��RoadID
		pNRBC->NSS[i].BlockIdx = _MAXUNSHORT;	
		pNRBC->NSS[i].RoadIdx  = _MAXUNSHORT;
		GetBlockRoadIdx(&(pNRBC->NSS[i].BlockIdx),&(pNRBC->NSS[i].RoadIdx),pNRBC->NodeIDList[i],pNRBC->NodeIDList[i+1]);
	}
	m_mrt.Remove_Index();
	return nuTRUE;
}

nuBOOL Class_CalMRT::LocalAStarSuccessWorkStep2(PNAVIRTBLOCKCLASS pNRBC)//�ϰ�W��(Local AStar)���\�������ƾ�z
{
	#ifdef DEF_MAKETHRROUTE
		nuTcscpy(m_mdw.FName, MakeThr_MapPath);
		nuTcscat(m_mdw.FName, nuTEXT(".mdw"));
	#else
		nuTcscpy(m_mdw.FName, nuTEXT(".mdw"));
		g_pRtFSApi->FS_FindFileWholePath(-1,m_mdw.FName,NURO_MAX_PATH);
	#endif
	//���n�]�k���omdw�W��
	if(!m_mdw.Read_Header()){	m_mdw.Remove_Header();	return nuFALSE;	}
	nuDWORD i = 0, k = 0, TmpSaveVertexCount = 0;
	nuUSHORT j = 0;
	nuLONG TmpSaveCount = 0;
	MDWRoadData RD  = {0};
	NUROPOINT tempPt = {0};
	nuLONG m_TmpStartIdx = 0;
	//�z�LBlockID��XBlockIdx
	for(i=0;i<pNRBC->NSSCount;i++){
		for(j=0;j<m_mdw.Header.m_TotalBlockCount;j++){
			if(pNRBC->NSS[i].BlockIdx==(*m_mdw.Header.p_GBlockID)[j]){
				pNRBC->NSS[i].BlockIdx=j;
				break;
			}
		}
	}
	//�g��BlockID ,RoadID ���o���W��m ���q�y���I�� ���q�y���I ���(RoadNameAddr ArcPtCount Bound ArcPt)
	for(i=0;i<pNRBC->NSSCount;i++){
		TmpSaveCount=0;
		TmpSaveVertexCount=100000;

		if(!m_mdw.Read_BlockData(pNRBC->NSS[i].BlockIdx)){
			return nuFALSE;
		}
			RD=(*(*m_mdw.Rd)[pNRBC->NSS[i].BlockIdx].p_RdData)[pNRBC->NSS[i].RoadIdx];

			if(TmpSaveVertexCount>RD.VertexCount){
				TmpSaveVertexCount=RD.VertexCount;
				pNRBC->NSS[i].BlockIdx=pNRBC->NSS[i].BlockIdx;
				pNRBC->NSS[i].RoadIdx=pNRBC->NSS[i].RoadIdx;
				pNRBC->NSS[i].CityID=0;
				pNRBC->NSS[i].TownID=0;
				pNRBC->NSS[i].RoadNameAddr=0;
				//Louis081117 �W�[��ƨӫO�s�ϰ��T
				pNRBC->NSS[i].TownID=RD.MapID;
				pNRBC->NSS[i].RoadNameAddr=RD.RTBID;

				pNRBC->NSS[i].RoadClass=RD.RoadClass;
				g_pCRDC->Create_ArcPt(pNRBC->NSS[i],RD.VertexCount);

				m_TmpStartIdx=RD.StartVertexIndex_high+RD.StartVertexIndex_Low*_COORLEVELNUM;
				tempPt.x = (*(*m_mdw.Rd)[pNRBC->NSS[i].BlockIdx].p_VertexCoor)[m_TmpStartIdx].x;
				tempPt.y = (*(*m_mdw.Rd)[pNRBC->NSS[i].BlockIdx].p_VertexCoor)[m_TmpStartIdx].y;

				pNRBC->NSS[i].Bound.left=tempPt.x;
				pNRBC->NSS[i].Bound.top=tempPt.y;
				pNRBC->NSS[i].Bound.right=tempPt.x;
				pNRBC->NSS[i].Bound.bottom=tempPt.y;


				if(3>GetDistance(tempPt,pNRBC->NSS[i].StartCoor)){//�P�w���q�D���Y�@���I�O�_�P�e�@�D���۳s��
					for(k=0;k<RD.VertexCount;k++){
						pNRBC->NSS[i].ArcPt[k]=(*(*m_mdw.Rd)[pNRBC->NSS[i].BlockIdx].p_VertexCoor)[m_TmpStartIdx+k];
						if(pNRBC->NSS[i].Bound.left>pNRBC->NSS[i].ArcPt[k].x)	pNRBC->NSS[i].Bound.left=pNRBC->NSS[i].ArcPt[k].x;
						if(pNRBC->NSS[i].Bound.top>pNRBC->NSS[i].ArcPt[k].y)	pNRBC->NSS[i].Bound.top=pNRBC->NSS[i].ArcPt[k].y;
						if(pNRBC->NSS[i].Bound.right<pNRBC->NSS[i].ArcPt[k].x)	pNRBC->NSS[i].Bound.right=pNRBC->NSS[i].ArcPt[k].x;
						if(pNRBC->NSS[i].Bound.bottom<pNRBC->NSS[i].ArcPt[k].y)	pNRBC->NSS[i].Bound.bottom=pNRBC->NSS[i].ArcPt[k].y;
					}
				}
				else{
					for(k=0;k<RD.VertexCount;k++){
						pNRBC->NSS[i].ArcPt[k]=(*(*m_mdw.Rd)[pNRBC->NSS[i].BlockIdx].p_VertexCoor)[m_TmpStartIdx+RD.VertexCount-1-k];
						if(pNRBC->NSS[i].Bound.left>pNRBC->NSS[i].ArcPt[k].x)	pNRBC->NSS[i].Bound.left=pNRBC->NSS[i].ArcPt[k].x;
						if(pNRBC->NSS[i].Bound.top>pNRBC->NSS[i].ArcPt[k].y)	pNRBC->NSS[i].Bound.top=pNRBC->NSS[i].ArcPt[k].y;
						if(pNRBC->NSS[i].Bound.right<pNRBC->NSS[i].ArcPt[k].x)	pNRBC->NSS[i].Bound.right=pNRBC->NSS[i].ArcPt[k].x;
						if(pNRBC->NSS[i].Bound.bottom<pNRBC->NSS[i].ArcPt[k].y)	pNRBC->NSS[i].Bound.bottom=pNRBC->NSS[i].ArcPt[k].y;
					}
				}
			}
	}
	//�z�L�y�� ������f������
	NUROPOINT Pt[3] = {0};
	for(i=0;i<(pNRBC->NSSCount-1);i++)
	{
		Pt[1]=pNRBC->NSS[i].EndCoor;
		for(j=1;j<pNRBC->NSS[i].ArcPtCount;j++)
		{
			Pt[0]=pNRBC->NSS[i].ArcPt[pNRBC->NSS[i].ArcPtCount-1-j];
			if((NURO_ABS(Pt[0].x - Pt[1].x) + NURO_ABS(Pt[0].y - Pt[1].y)) > _TURNFLAGDIFFDIS)
			{
				break;
			}
		}
		for(j = 1; j < pNRBC->NSS[i+1].ArcPtCount; j++)
		{
			Pt[2] = pNRBC->NSS[i+1].ArcPt[j];
			if((NURO_ABS(Pt[2].x - Pt[1].x) + NURO_ABS(Pt[2].y - Pt[1].y)) > _TURNFLAGDIFFDIS)
			{
				break;
			}
		}
		pNRBC->NSS[i].TurnAngle = GetAngle(Pt[0],Pt[1],Pt[2]);
	}
	pNRBC->NSS[pNRBC->NSSCount-1].TurnAngle = 0;

	m_mdw.Reset();
	return nuTRUE;
}

nuBOOL Class_CalMRT::LocalAStarSuccessWorkStep3(PNAVIRTBLOCKCLASS pNRBC)//�ϰ�W��(Local AStar)���\�������ƾ�z
{
	//�]�k���o�Ǹ�Ư୫�s�غc�ۤv��RTB
	//�ݸɧ������e��
	//nuLONG	RealDis;//�u��Z��
	//nuLONG	WeightDis;//�[�v�Z��
	//PTFIXTOROADSTRU FInfo;//�_�I������T
	//PTFIXTOROADSTRU TInfo;//���I������T
	//tagNAVIRTBLOCKCLASS *NextRTB;
	//�S�O�n�O�� FInfo,TInfo �o�̭���NodeID�@�w�n��0 �o�ˤ~��Ұʦ۰ʷj�M�\��
	//���O�ٻݭn�`�N
	nuLONG MapID = 0, RTBID = 0, SaveIndex = 0;
	nuDWORD i = 0;
	PNAVIRTBLOCKCLASS pSaveNaviRTBClass = NULL, pLastSaveNaviRTBClass = NULL, pTmpNaviRTBClass = NULL;
	MapID=-1;
	RTBID=-1;
	pSaveNaviRTBClass=NULL;
	pLastSaveNaviRTBClass=NULL;
	pTmpNaviRTBClass=NULL;
	for(i=0;i<pNRBC->NSSCount;i++){	
		if( pNRBC->NSS[i].TownID==MapID && pNRBC->NSS[i].RoadNameAddr==RTBID ){
			pLastSaveNaviRTBClass->NSSCount++;
			pLastSaveNaviRTBClass->TInfo.FixCoor=pNRBC->NSS[i].EndCoor;
		}
		else{
			MapID=pNRBC->NSS[i].TownID;
			RTBID=pNRBC->NSS[i].RoadNameAddr;
			if(pSaveNaviRTBClass==NULL){
				pTmpNaviRTBClass=NULL;
				g_pCRDC->Create_NaviRtBlockClass(pTmpNaviRTBClass);
				pSaveNaviRTBClass=pTmpNaviRTBClass;
				pLastSaveNaviRTBClass=pTmpNaviRTBClass;
				pLastSaveNaviRTBClass->NSSCount=1;

				pLastSaveNaviRTBClass->FInfo.MapID=pNRBC->NSS[i].TownID;
				pLastSaveNaviRTBClass->TInfo.MapID=pNRBC->NSS[i].TownID;
				pLastSaveNaviRTBClass->FInfo.RTBID=pNRBC->NSS[i].RoadNameAddr;
				pLastSaveNaviRTBClass->TInfo.RTBID=pNRBC->NSS[i].RoadNameAddr;
				pLastSaveNaviRTBClass->FInfo.FixCoor=pNRBC->NSS[i].StartCoor;
				pLastSaveNaviRTBClass->TInfo.FixCoor=pNRBC->NSS[i].EndCoor;
			}
			else{
				pTmpNaviRTBClass=NULL;
				g_pCRDC->Create_NaviRtBlockClass(pTmpNaviRTBClass);
				pLastSaveNaviRTBClass->NextRTB=pTmpNaviRTBClass;
				pLastSaveNaviRTBClass=pTmpNaviRTBClass;
				pLastSaveNaviRTBClass->NSSCount=1;

				pLastSaveNaviRTBClass->FInfo.MapID=pNRBC->NSS[i].TownID;
				pLastSaveNaviRTBClass->TInfo.MapID=pNRBC->NSS[i].TownID;
				pLastSaveNaviRTBClass->FInfo.RTBID=pNRBC->NSS[i].RoadNameAddr;
				pLastSaveNaviRTBClass->TInfo.RTBID=pNRBC->NSS[i].RoadNameAddr;
				pLastSaveNaviRTBClass->FInfo.FixCoor=pNRBC->NSS[i].StartCoor;
				pLastSaveNaviRTBClass->TInfo.FixCoor=pNRBC->NSS[i].EndCoor;
			}
		}
	}

	pTmpNaviRTBClass=pSaveNaviRTBClass;
	while(pTmpNaviRTBClass!=NULL){
		g_pCRDC->Create_NaviSubClass(pTmpNaviRTBClass,pTmpNaviRTBClass->NSSCount);
		pTmpNaviRTBClass=pTmpNaviRTBClass->NextRTB;
	}
	pTmpNaviRTBClass=NULL;

	//�n�`�N�y�Ъ��K�[�n���B�z
	MapID=-1;
	RTBID=-1;
	pLastSaveNaviRTBClass=NULL;
	for(i=0;i<pNRBC->NSSCount;i++){	
		if( pNRBC->NSS[i].TownID==MapID && pNRBC->NSS[i].RoadNameAddr==RTBID ){
			SaveIndex++;
			pLastSaveNaviRTBClass->NSS[SaveIndex]=pNRBC->NSS[i];
			pLastSaveNaviRTBClass->RealDis+=pNRBC->NSS[i].RoadLength;
			g_pCRDC->Create_ArcPt(pLastSaveNaviRTBClass->NSS[SaveIndex],pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPtCount);
			nuMemcpy(pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPt,pNRBC->NSS[i].ArcPt,pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPtCount*sizeof(NUROPOINT));
		}
		else{
			MapID=pNRBC->NSS[i].TownID;
			RTBID=pNRBC->NSS[i].RoadNameAddr;
			if(pLastSaveNaviRTBClass==NULL){
				pLastSaveNaviRTBClass=pSaveNaviRTBClass;
				SaveIndex=0;
				pLastSaveNaviRTBClass->NSS[SaveIndex]=pNRBC->NSS[i];
				pLastSaveNaviRTBClass->RealDis=pNRBC->NSS[i].RoadLength;
				g_pCRDC->Create_ArcPt(pLastSaveNaviRTBClass->NSS[SaveIndex],pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPtCount);
				nuMemcpy(pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPt,pNRBC->NSS[i].ArcPt,pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPtCount*sizeof(NUROPOINT));
			}
			else{
				pLastSaveNaviRTBClass=pLastSaveNaviRTBClass->NextRTB;
				SaveIndex=0;
				pLastSaveNaviRTBClass->NSS[SaveIndex]=pNRBC->NSS[i];
				pLastSaveNaviRTBClass->RealDis=pNRBC->NSS[i].RoadLength;
				g_pCRDC->Create_ArcPt(pLastSaveNaviRTBClass->NSS[SaveIndex],pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPtCount);
				nuMemcpy(pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPt,pNRBC->NSS[i].ArcPt,pLastSaveNaviRTBClass->NSS[SaveIndex].ArcPtCount*sizeof(NUROPOINT));
			}
		}
		pLastSaveNaviRTBClass->NSS[SaveIndex].TownID=0;
		pLastSaveNaviRTBClass->NSS[SaveIndex].RoadNameAddr=0;
	}

	//�]�k��pLastSaveNaviRTBClass��pNRBC�s��
	pTmpNaviRTBClass=pNRBC->NextRTB;
	pNRBC->NextRTB=pSaveNaviRTBClass;
	while(nuTRUE){
		if(NULL==pSaveNaviRTBClass->NextRTB){
			pSaveNaviRTBClass->NextRTB=pTmpNaviRTBClass;
			break;
		}
		pSaveNaviRTBClass=pSaveNaviRTBClass->NextRTB;
	}

	return nuTRUE;
}

/*** �z�L�_�W�INodeID��X�Ӹ��q�bDw����BlockIdx�PRoadIdx ***/
nuBOOL Class_CalMRT::GetBlockRoadIdx(nuUSHORT *BlockIdx, nuUSHORT *RoadIdx, nuULONG FNodeID, nuULONG TNodeID)
{
	/*** �ϥΤG���k ����ު�i��⦸�G���j�M�k ��X�������ƭ� �p�G�S���j�M�� �^��nuFALSE�ñN�ƭȪ�l�� ***/
	*RoadIdx = _MAXUNSHORT;
	nuLONG IdxRange = 0;
	nuLONG m_Min=-1;
	nuLONG m_Max=m_mrt.RtBHeader.TotalRoadCount;
	nuLONG m_Mid=(m_Max+m_Min)/2;
	IdxRange=1;

	//�u�n��H�ֳt���覡�M�� �ñư������i�Ϊ��I ���N�O�n��k
	while(nuTRUE){
		if(FNodeID>(*m_mrt.RtBIdx)[m_Mid].FNodeID)
		{	m_Min=m_Mid;	m_Mid=(m_Max+m_Min)/2;	}
		else if(FNodeID<(*m_mrt.RtBIdx)[m_Mid].FNodeID)
		{	m_Max=m_Mid;	m_Mid=(m_Max+m_Min)/2;	}
		else{
			if(TNodeID>(*m_mrt.RtBIdx)[m_Mid].TNodeID)
			{	m_Min=m_Mid;	m_Mid=(m_Max+m_Min)/2;	}
			else if(TNodeID<(*m_mrt.RtBIdx)[m_Mid].TNodeID)
			{	m_Max=m_Mid;	m_Mid=(m_Max+m_Min)/2;	}
			else{
				*BlockIdx=(*m_mrt.RtBIdx)[m_Mid].BlockIdx;
				*RoadIdx=(*m_mrt.RtBIdx)[m_Mid].RoadIdx;
				return nuTRUE;
			}
		}
		if((m_Max-m_Min)<=IdxRange) break;
	}

	m_Min=-1;
	m_Max=m_mrt.RtBHeader.TotalRoadCount;
	m_Mid=(m_Max+m_Min)/2;
	while(nuTRUE){
		if(TNodeID>(*m_mrt.RtBIdx)[m_Mid].FNodeID)
		{	m_Min=m_Mid;	m_Mid=(m_Max+m_Min)/2;		}
		else if(TNodeID<(*m_mrt.RtBIdx)[m_Mid].FNodeID)
		{	m_Max=m_Mid;	m_Mid=(m_Max+m_Min)/2;		}
		else
		{
			if(FNodeID>(*m_mrt.RtBIdx)[m_Mid].TNodeID)
			{	m_Min=m_Mid;	m_Mid=(m_Max+m_Min)/2;	}
			else if(FNodeID<(*m_mrt.RtBIdx)[m_Mid].TNodeID)
			{	m_Max=m_Mid;	m_Mid=(m_Max+m_Min)/2;	}
			else{
				*BlockIdx=(*m_mrt.RtBIdx)[m_Mid].BlockIdx;
				*RoadIdx=(*m_mrt.RtBIdx)[m_Mid].RoadIdx;
				return nuTRUE;
			}
		}
		if((m_Max-m_Min)<=IdxRange) break;
	}
	return nuFALSE;
}

nuLONG Class_CalMRT::GetDistance(NUROPOINT Pt1, NUROPOINT PT2)
{
	if(Pt1.x==PT2.x && Pt1.y==PT2.y) return 0;
	nuLONG X,Y;
	X = NURO_ABS(Pt1.x-PT2.x) * nulCos(NURO_ABS((Pt1.y+PT2.y)/2) / _EACHDEGREECOORSIZE) / nuGetlBase() * 1113 / _LONLATBASE;
	Y = NURO_ABS(Pt1.y-PT2.y) * 1109 / _LONLATBASE;
	return nulSqrt(X,Y);
}

nuLONG Class_CalMRT::GetAngle(NUROPOINT FPt, NUROPOINT NPt, NUROPOINT TPt)
{
	nuLONG  ct = 0, ct1 = 0, ct2 = 0;
	ct1=nulAtan2(FPt.y-NPt.y,FPt.x-NPt.x);
	ct2=nulAtan2(NPt.y-TPt.y,NPt.x-TPt.x);

	ct = ct2-ct1;
	if(ct>180){
		ct=ct-360;
	}
	else if(ct<(-180)){
		ct=ct+360;
	}
	return ct;
}
