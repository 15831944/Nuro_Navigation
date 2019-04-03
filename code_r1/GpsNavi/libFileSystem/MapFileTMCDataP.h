
#include "FileMapBaseZ.h"

#define  _TMC_UIROADNAME_LEN_  30
#define  _TMC_UIEVENTNAME_LEN_ 30
#define  _TMC_UIEVENTNAMECHAR_LEN_ 60
#define  _TMC_DATA_LIMIT_	    400
#define  _TMC_VD_MAPTABLE_COUNT 489
#define  _TMC_VD_MAPTABLE_COUNT2 176

#define  FILE_CSC_VD			nuTEXT("UIdata\\��DVD.dat")
#define  FILE_CSC_VD2			nuTEXT("UIdata\\VD.txt")
#define  FILE_CSC_VD_ID			nuTEXT("UIdata\\VDID_MAPPING.txt")
#define  FILE_CSC_VD_NAME		nuTEXT("UIdata\\VDID_MAPPING2.txt")
 
#define  FILE_CSC_XML			nuTEXT("UIdata\\traffic_tmc.txt")
#define  FILE_CSC_XMLR			nuTEXT("UIdata\\traffic_city.txt")
#define  FILE_NAME_SORT			nuTEXT("UIdata\\Sort.bin")
#define  FILE_NAME_TABLE			nuTEXT("UIdata\\tw.ln")


typedef struct tag_VDMapID
{
  nuCHAR VDID[15];
  nuCHAR ID[10];
} VDMapID;
typedef struct tag_VDROADNAME
{
  nuCHAR VDID[15];
  nuCHAR ID[20];
} VDROADNAME;
typedef struct tag_XML_RDST_TMCINFO // XML/FM temp
{
	nuCHAR cLocation[10];
	nuCHAR cEvent[10]; 
	
}XML_RDST_TMCINFO;

typedef struct tag_TMC_INFO_LIST	//UI�һݪ��W�ٸ�T
{
	nuWORD  wRoadName[_TMC_UIROADNAME_LEN_];
	nuINT	nEventID; 
	nuWORD	wEvenName[_TMC_UIEVENTNAME_LEN_];
	
}TMC_INFO_LIST, *PTMC_INFO_LIST;

typedef struct tag_TMC_INFO_UI
{
	nuINT   nCount;
	PTMC_INFO_LIST pPTMC_INFO_LIST;
	
} TMC_INFO_UI,*pTMC_INFO_UI;

typedef struct tag_TMC_EVENT_DATA	  //.TMC ���� EVENT�Ѽ� 
{
	nuWORD   wTraffic_Num;
	nuWORD   wTraffic_NameLen;
	nuSHORT  sTraffic_EventWeighting;
	nuSHORT  sTraffic_EventTime;
	nuWORD	 wEventName[15];

}TMC_EVENT_DATA;

typedef struct tag_TMC_Header		  //.TMC Header_DATA
{

	nuDWORD DataCnt;
	nuDWORD VertexDataAddr;
	nuDWORD TrafficDataAddr;
	nuWORD  TrafficCnt;
	nuWORD  Reserve;

} TMC_Header;

typedef struct tag_TMC_DATA			   //.TMC DATA (nodes��T)
{
	
	nuWORD  wLocationCode;
	nuWORD  wLocationCodeNum;
	nuDWORD dLocationVertexAddr;
	nuDWORD dLocationUpAddr;
	nuDWORD dLocationDownAddr;
	
}TMC_DATA;

typedef struct tag_LOCATION_DATA		//����Location_table ���W�ٸ�T
{
	
	nuINT  cLocID;
    nuWORD cLocName[50];//�T�w�j�p        
	
}TMC_LOCATION;

typedef struct tag_TMC_Byte_DATA	//FM ��T�� BYTE�Φ��ǻ� �T�����R�W
{
	nuINT	nRoad;
	nuINT	nEvent;
	nuDWORD nTime;//�T�w�j�p        

}TMC_Byte_DATA;

typedef struct tag_Code				//Unicode �� Big5 �һݵ��c 
{

	nuINT	nBig;
	nuINT	nUniCode;    

}Trans_DATA;

typedef struct tag_TMC_XML_Complex_DATA				//XML_ROAD ��T 
{													//@@@@@@@@@ �භ�Q��k�ഫ ��ARM���i�H�e�{ @@@@@@@@@@@@@@	 			

	nuWORD wRoadName[_TMC_UIROADNAME_LEN_];
	nuWORD wEvenName[_TMC_UIEVENTNAME_LEN_];
	nuDWORD nTime;        

}TMC_XML_C_DATA;


typedef struct Tag_UNITVD2
{
	nuCHAR	VDID[16];
	nuCHAR	VDName[32];
	nuLONG	VDSpeed;
	nuLONG	EventCount;
	nuCHAR	Event1[32];
	nuCHAR	Event2[32];
	nuCHAR	Event3[32];
	nuCHAR	Event4[32];	
}UNITVD2,*PUNITVD2;


typedef struct Tag_EVENTVD2
{
	nuCHAR	EventID[32];
	nuCHAR	Event[256];
}EVENTVD2,*PEVENTVD2;

typedef struct tag_TMC_VD_EVENT
{
	nuCHAR   nEventId[30];
	
} TMC_VD_EVENT,*pTMC_VD_EVENT;


class CMapFileTMCDataP : public CFileMapBaseZ  
{
public:
	CMapFileTMCDataP();
	virtual ~CMapFileTMCDataP();

	nuBOOL	Get_TMC_FM_XML_SIZE(nuUINT& nselet,nuUINT* nFm_Count,nuUINT& nXML_Count,nuUINT* nXML_Complex_Count);//�ѪRDATA �έpCOUNT �A nselet:�ɮװѼ�
	
	//UI    ���^�D��/�ƥ�W�ٸ�T (BUFFER/����/�ƧǼҦ�)
	nuBOOL	Get_TMC_XML_L(nuVOID* pTmcBuf, const nuUINT TmcDataLen,nuUINT nmode);			
	nuBOOL	Get_TMC_XML(nuVOID* pTmcBuf, const nuUINT TmcDataLen,nuUINT nmode);		
	nuBOOL	Get_TMC_FM(nuVOID* pTmcBuf, const nuUINT TmcDataLen,nuUINT nmode);
	nuBOOL	Get_TMC_XML_FM(nuVOID* pTmcBuf, const nuUINT TmcDataLen,nuUINT nmode);
	nuBOOL	Get_TMC_VD(nuVOID* pTmcBuf, const nuUINT TmcDataLen,nuUINT nmode);

	//Router���^¶���һݸ�T(BUFFER,�O�d�Ѽ�)
	nuBOOL	Get_TMC_Router(nuVOID* pTmcBuf, const nuUINT TmcDataLen);		

	nuINT	TransCode(nuINT code); //�Ƨǥ�  unicode �� big5

	nuBOOL	OpenXML(nuLONG nMapID);
   	nuBOOL	XML_Parser();					//XML�ѪR���
	nuBOOL	XML_Update();					//��s @@
	nuBOOL	XMLFree();

	nuBOOL	OpenRoadXML(nuLONG nMapID);
	nuBOOL	RoadXML_Parser();				//XML_L�ѪR���
	nuBOOL	RoadXML_Update();				//��s @@
	nuBOOL	RoadXMLFree();					//@@�ݸɥR
	
	nuBOOL	FMFree();
	nuBOOL	Set_TMC_Byte(nuVOID*pTmcBuf);	//FM�ѪR���
	nuBOOL	Byte_Update();					//��s �ݧ���
	nuBOOL	ByteFree();						//@@�ݸɥR
    
	nuBOOL	ALLFree();
	nuBOOL	TMCInfoFree();

	

	//Set_TMC_Byte () �����ܼ� 
	nuINT	m_nWords;		//��N�Ӧr  (26�r���@��)
	nuINT	m_nLeftWords;	//�Ѿl�r��
	nuCHAR  m_sLeftWord[3]; //�Ѿl�r��

	nuBOOL	ShiftWords(nuVOID* pTmcBuf,nuINT* nNums,nuINT);	//���r��SHIFT	
	nuCHAR	m_sCheckStr[26];							//�Ȧs		DATA
	nuCHAR	m_sTmc_information[13][2];					//�ഫ		TMC�ѪR���G���}�C
	nuINT	m_nTmc_information2[13][2];					//�ഫ		ANSI�ΰ}�C 
	nuBOOL	m_bCheckHeader;								//�P�_		�O�_�ŦXDATA_HEAD	
	nuBOOL	m_bLeftWord;								//			�O�_���Ѿl��sTmpWord[]�S�� ��J....
	nuBOOL	m_bCorrect;									//			�O�_�����T��DATA(���ݬ�5A5A)
	nuCHAR	m_sCheckWord[4];							//�P�_�}�Y  �i��SHIFT�ʧ@(�N�ѤU���r��i�沾�ʨä��)
	nuINT	m_nLeft;									//�ѤU�����B�z�r����
    nuBOOL	m_bLeft;

	//����TMC EVENT_ID(NAME)/LOCATION_ID(NAME)/TIME
	TMC_Byte_DATA	m_nByte[_TMC_DATA_LIMIT_];
	TMC_Byte_DATA	*m_XML_Data;
	TMC_XML_C_DATA	*m_XML_Complex_Data;
	TMC_XML_C_DATA	*m_VD_Data;
	//Trans_DATA		*data;

	//�ɶ����Z- Start / End
	nuDWORD	m_dStartTime;
	nuDWORD	m_dDistTime;	
	nuDWORD	m_dnowTime;

	//FM/XML/FM+XML/XML_R �ƶq
	nuINT	m_nByte_Record;
	nuINT	m_nXml_Record;
	nuINT   m_nXml_fm_Record;
	nuINT	m_nXml_Complex_Record;

	
	//CHECK - TIME �O�d���Įɶ�������T @@
	nuBOOL	CheckDataTime();
	nuBOOL	CheckDataTimeXML();
	nuBOOL	CheckDataTimeComplexXML();
	
	//��ﭫ�Ƹ�T �H�Χ�s�ɶ���T
	nuBOOL	CheckData(TMC_Byte_DATA temp);
	nuBOOL	CheckDataX(TMC_Byte_DATA temp);
	nuBOOL	CheckDataXMLComplex(TMC_XML_C_DATA temp);

	//�Ƨ�  0:NULL 1:ROAD 2:Event 
	nuBOOL  FM_Order(nuINT);
	nuBOOL  XML_Order(nuINT);			
	nuBOOL	XML_COMPLEX_Order(nuINT n);
	nuBOOL	XML_FM_Order(nuINT n);
	nuBOOL	VD_Order(nuINT n);
	
	//FILE  �򥻨禡
	nuBOOL	IsOpen();
	nuVOID	Close();
	nuUINT	GetLength();
	nuBOOL	ReadData(nuUINT addr, nuVOID *pBuffer, nuUINT len);

	//EVENT/LOACTION SORT
	nuVOID	ShellSort();							//��}��Bubble
	nuINT	BinarySearch_TMC_DATA(nuINT find);		//�G���Ƨ�-Location_code(.TMC)
	nuINT	BinarySearch_TMC_LocName(nuINT find);	//�G���Ƨ�-Location_Id(Location_table)
	nuBOOL	ShowEvent(nuINT);						//��s�ƥ��T(FM+XML)
	nuBOOL	ShowLocation(nuINT);					//��s���W��T(FM+XML)

	TMC_EVENT_DATA		*EventComparData;			//TMC������EVENT���(�Ѥ���)
	TMC_DATA			*TMC_dataA;					//TMC������DATA_A��� �Q��loc_code �i��Ƨ� �H�Q���᪺���
	TMC_LOCATION		*LocData;					//TMC Table�W�ٸ��   �Q��loc_id   �i��Ƨ� �H�Q���᪺���

	nuBOOL	SetEvent(nuINT nEventSet[20]);			//UI�]�w�ƥ� ����bTMCPass ����Router�ϥ� (***�n�令�ʺA���j�p***)
	nuINT	n_Fm_Xml_total;							//FM+XML total records ()

	nuINT   nTmcLocCount;		//TMC�����(DataA)�`��
	nuINT	TMC_Event_Count;	//�p��ƥ�W�ٵ���
	nuINT	nLocSize;			//location_code ����
	nuINT	nLocTableSize;		//location_id   ����
	
	nuBOOL	bLocationFrist;		//�P�_�O�_�i��TMC DATA_A����ƱƧ�
	nuBOOL	bEventFrist;		//�P�_�O�_�N EventData ���J


	//UI&Router �ϥ�TMC������ưѼ� 
	TMC_Info_Router		m_TMC_Info_Router;  //Router �һݪ�DATA
	TMC_INFO_UI			tmc_ui;				//FM&RDS_XML �Ҩ��o���T(���W,Event_ID,�ƥ�W��)
	nuINT				m_nArry_idx;		//�W�ٰ}�C(tmc_ui)��index

	nuBOOL ReadVD();
	nuINT  FindMapID(char *temp);
	nuBOOL ReadVD2(nuCHAR *sTime);
	nuBOOL ReadVD3(nuCHAR *sTime);

	nuINT CityID;
	nuINT nCityCounts[22];
	nuINT nSpeedCounts[24];
	nuINT nStartIdx[24];
	
	nuLONG GetVDCount(nuCHAR *sTime);
	nuBOOL GetVDUnit(nuLONG UnitIndex,UNITVD2 &VD);
	nuBOOL CleanVDData();
	nuBOOL GetVD(nuVOID*pTmcBuf,const nuUINT size);

	nuLONG nVDCount;
	UNITVD2 *pVDData;//�˶�VD��ƪ����c����

	nuBOOL GetVDEVENT(nuCHAR *pEvent,EVENTVD2 &VDevent);

	nuLONG nVDEventCount;
	EVENTVD2 *pVDevent;
	nuBOOL bVDInit;
	nuINT nVD_Event_Count;
	nuINT nVD_Road_Count;
	Trans_DATA *data;
	nuINT nSortLimt;
	VDMapID sMapID[_TMC_VD_MAPTABLE_COUNT];
	VDROADNAME sMapID2[_TMC_VD_MAPTABLE_COUNT2];
	nuBOOL bNoLoad;
	nuINT nTempRoadIdx;
	nuINT nTempHighIdx;
	
private:
	nuCFile file;			
	nuCFile LocNamefile;
	nuWORD	totalcount;
	nuFILE  *pFile;
};
