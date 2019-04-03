#if !defined(AFX_SEARCHROAD_H__69340EF9_C168_4655_A955_5629DF66D5DA__INCLUDED_)
#define AFX_SEARCHROAD_H__69340EF9_C168_4655_A955_5629DF66D5DA__INCLUDED_

#include "SearchBaseZ.h"
#include "NuroClasses.h"

class CMapFileBhY;
class CMapFileRdwY;
class CSearchArea;
const nuINT _CROSS_COL_RN_LIMIT_ = 16;
const nuINT _CROSS_COL_PT_LIMIT_ = 1024;
const nuINT _SAST_JUDGE_RN_DIS_ = 6000;//RN file check NAMEADDR_DIS limit
const nuINT _SNST_COL_LIMIT_ = 128;

struct nuroMapArea
{
    nuLONG	nMapID;
    nuWORD	nCityID;
    nuWORD	nTownID;
};

/**
* @class  CSearchRoad  
* @brief  ��·����  \n
*   ģ���ڴ��������ȡ����˳��δʹ�õ����ݳ���Ϊ0�� \n
*   CT��SZY��RN��RNC��TownBLKInfo��RTInfo
*   �����������Ϻ��������ʹ����ͬһ�������ǣ������ÿ��������ʱ��ͬ�������Ӧ������� ��������²���������
*/
class CSearchRoad : public CSearchBaseZ
{
public:
    CSearchRoad();
    virtual ~CSearchRoad();
    /**
    * @brief  ��ʼ��searchroad
    * @param nMMIdx �ڴ��־
    * @param nMMMaxLen �ڴ泤��
    * @param nCBLen ���ص�map��CITYTOWN��Ϣ����
    * @param pSearchArea
    */
    nuBOOL  Init(nuWORD nMMIdx, nuUINT nMMMaxLen, nuUINT nCBLen, CSearchArea* pSearchArea);
    nuVOID  Free();
    nuBOOL	SetRoadSZSLimit(nuUINT nMin, nuUINT nMax);
    nuBOOL	SetRoadSZZhuyin(nuWORD zhuyin);
    nuUINT	GetRoadSZTotal();
    nuINT	GetRoadSZList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen); 

    nuBOOL	SetRoadSZ(nuUINT nResIdx);
    nuBOOL	SetRoadKeyDanyin(nuWORD *pDanyin);
	 nuBOOL	SetRoadKeyDanyin2(nuWORD *pDanyin);
    nuBOOL	SetRoadKeyName(nuWORD *pKeyWord, nuBOOL bIsFromBeging = false);
    nuUINT	GetRoadTotal();
    /**
    * @brief ���road�������                       \n
    *   �����NURO_SEARCH_NORMALRES����             \n
    * @return ��õ�road����                        \n
    *   --��ʹ�÷�ҳʱ������ֵ�ĸ�16λΪ������ڵ�ҳ������16λΪpoi����
    */
    nuINT	GetRoadNameList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);

	//prosper 05
	nuVOID  Stroke_GetNextWordData(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID* candi, const nuUINT candylen, const nuBOOL ReSort);
	
    nuVOID ZhuYinForSmart_SecondWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont, const nuUINT candylen, const nuBOOL ReSort);
	nuBOOL ZhuYinForSmart_OtherWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID *candi, const nuUINT candylen, const nuBOOL ReSort);

	
	/**
    * @brief �Ե�·������ж�������                 \n
    *   ��MRģʽ�� ��֧�ֶ�����·���ж�������       \n
    *   ������pBuffer�����ɵĽ��                   \n
    *   pBuffer�е�������NURO_SEARCH_FILTERRES����  \n
    *   �����Я����ʵ���ڲ�idx                     \n
    *   Ҫʹ�øý���еĵ�·�������ã���Ҫ������ڲ�idx �����bRealIdxΪtrue
    */
    nuINT	GetRoadFilterResAll(const nuWCHAR *pKey, nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL	SetRoadName(nuUINT nResIdx, nuBOOL bRealIdx=0);
    /**
    * @brief  ��ȡ����·����
    */
    nuUINT  GetRoadTotal_MR();
    /**
    * @brief  ��ȡ�ӵ�·����
    */
    nuUINT	GetChildRoadTotal(nuUINT nMainRoadIdx, nuBOOL bRealIdx=0);
    /**
    * @brief  ��ȡ����·��Ϣ                        \n
    *   �����NURO_SEARCH_NORMALRES����
    * @return ��õ�road����                        \n
    *   --��ʹ�÷�ҳʱ������ֵ�ĸ�16λΪ������ڵ�ҳ������16λΪpoi����
    */
    nuUINT	GetRoadNameList_MR(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
    /**
    * @brief  ��ȡ�ӵ�·��Ϣ[ȫ����]    \n
    *   ���ڴ治�㣬���ؿ����ɵ��ӵ�·��Ϣ
    * @param nMainRoadIdx ����·���� ����GetRoadNameList_MR
    * @param bRealIdx ���nMainRoadIdx�Ƿ�Ϊ�ڲ���ʵidx
    * @return ������ʵ��ȡ���ӵ�·��Ϣ����
    */
    nuUINT	GetRoadNameALL_MR(nuUINT nMainRoadIdx, nuBYTE* pBuffer, nuUINT nMaxLen, nuBOOL bRealIdx=0);
    /**
    * @brief  ����·��[����·ģʽ]
    * @param bRealIdx ���nMainRoadIdx�Ƿ�Ϊ�ڲ���ʵidx
    */
    nuBOOL	SetRoadName_MR(nuUINT nMainRoadIdx, nuUINT nRoadIdx, nuBOOL bRealIdx=0);
    /**
    * @brief  �������� ��ȫ������д�������
    */
    nuUINT	GetNextWordAll(nuWORD* pHeadWords, nuWORD *pBuffer, nuUINT nMaxWords);
    /**
    * @brief  ��õ�·��������Ϣ����
    */
    nuUINT	GetRoadDoorTotal();
    /**
    * @brief  ��õ�·��������Ϣ[ȫ��ȡ]
    * @return �ڴ治��ʱ ��ȡ������Ϣ��ʧ��
    */
    nuBOOL	GetRoadDoorInfo(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL	GetRoadPos(NUROPOINT* pos);
    nuWORD	GetRoadTownID();
    nuWORD	GetRoadCityID();
    nuUINT	GetRoadCrossTotal();
    nuINT	GetRoadCrossList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
    nuBOOL	GetRoadCrossPos(nuUINT nResIdx, NUROPOINT* pos);
    nuWORD	GetRoadCrossTownID(nuUINT nResIdx);
    nuWORD	GetRoadCrossCityID(nuUINT nResIdx);
	nuBOOL  SetNoName(nuBOOL bRes);
   
    nuVOID	ClearSZYInfo();
	nuBOOL	GetRoadSKB(void* pSKBBuf, nuUINT& nCount);  //Prosper 20111226
	nuBOOL	GetRoadWordData(nuINT &nTotal,nuVOID* pBuffer, nuUINT nMaxLen);
	nuBOOL	NAME_Order(nuINT n);
	
	nuBOOL GetNEXTWORD(nuVOID* pKEYBuf, nuUINT& nCount) ;
	nuWCHAR	   m_wsNEXT_WORD_Data[NEXT_WORD_MAXCOUNT];
	nuINT      nNEXT_WORD_COUNT;
	nuBOOL nuWcsFuzzyJudge_O_FORSEARCHROAD(nuWCHAR* pDes, nuWCHAR* pKey, nuUINT desLen, nuUINT keyLen
						  , nuINT& startpos, nuINT& diffpos);
private:
    typedef struct tagSEARCH_MAIN_ROAD  ///����·��Ϣ
    {
        nuWORD tag;     ///����·�ڽ���е���ʼλ��
        nuWORD total;   ///�ӵ�·����
    }SEARCH_MAIN_ROAD;
    typedef struct tagSEARCH_SNST_DATA  ///ͬ���ռ���Ϣ
    {
        nuUINT addr1;   ///Ŀ��·����ַ
        nuUINT addr2;   ///��Ŀ��ͬ���ĵ�ַ
    }SEARCH_SNST_DATA;
    /**
    * @brief  �����·������������  \n
    *   ����SZY FILE
    */
    nuUINT	FlushSZYInfo();
    nuVOID	ResetSZSearch();
    /**
    * @brief  ��·�������� \n
    *   ���������SZY����
    */
    nuWORD	SearchRoadSZ();
    /**
    * @brief  �����·��������  \n
    *   ����RN RNC FILE
    */
    nuUINT	FlushRNInfo();
	nuUINT	FlushRNInfo2(); //Prosper add by 20130606, for load before input
    nuVOID	ClearRNInfo();
    nuVOID	ResetRNSearch();
    /**
    * @brief  ��ȡ��·��������  \n
    *   ǰ�᣺RN ���ϱ�����  \n
    * @param addr ·����ַ
    * @param pBuffer ָ������ ��nMaxLenΪ0ʱ�����ڴ��е�·�����ϵ�ַ����pBuffer \n
    *   �������ʱ ��·�����Ƶ�pBufferָ��ĵ�ַ
    * @param nMaxLen pBuffer�ĳ��ȣ�Ϊ0ʱ˵����Ҫ����·�����ϵ�ַ������·�����ݣ�
    * @param pStrokes ����·���ʻ�����NULLʱ�����أ�
    * @return ·������ nuWcslen()
    */
    nuUINT	GetRoadName(nuUINT addr, nuWORD *&pBuffer, nuUINT nMaxLen=EACH_ROAD_NAME_LEN, nuBYTE *pStrokes=NULL);
    /**
    * @brief  ��ȡ��·��������  \n
    *   ǰ�᣺RN���ϱ�����  ���ڵ������ϴ����ڴ����ַ�� ������Ϊ���ص�������\n
    * @param addr ·����ַ
    * @param pBuffer ��·���������ݸ��Ƶ�pBufferָ��ĵ�ַ
    * @param nMaxLen pBuffer�ĳ���
    * @return �������� nuWcslen()
    */
    nuUINT	GetRoadDanyin(nuUINT addr, nuVOID* pBuffer, nuUINT nMaxLen);
    /**
    * @brief  �ж�2��·����ַ�Ƿ�ͬ��
    */
    nuBOOL	IsSameRoadName(nuUINT addr1, nuUINT addr2);
    /**
    * @brief  ��·����                  \n
    *   ��С������λ CITY ��m_nCityIDTag�����һ��Ҫ������CITYID    \n
    *   �����ļ� ͬFlushRNInfo()        \n
    *   ����RNC�еĵ�·�������б���     \n
    *   �ų�ͬ��ͬ����· �ռ���m_SASTDATA��
    * @param tag ��Ҫ���Ľ��m_SearchRoadRes�е���ʼλ��
    */
    nuUINT	SearchNextRN(nuUINT tag);
	nuUINT	SearchNextRN2(nuUINT tag); //Prosper add by 20130606, for load before input
	  /**
    * @brief  �ж�2��·����ַ�Ƿ�ͬ��·
    */
    nuBOOL	IsSameMainRoad(nuUINT addr1, nuUINT addr2);
    /**
    * @brief  �������·���    \n
    *   �жϳ�ͬһ��·������ �����·��Ϣ��m_MainRoad
    * @param total �������ĵ�·����
    * @return ����·����
    */
    nuUINT	FillMainRoad(nuUINT total);
    /**
    * @brief  ͬ����·��ַ����  \n
    *   ʹ����������Ϣ����ʱ
    * @param pNameAddr ·�����ϵ�ַ
    * @param nMaxLim ����Ѽ�����
    */
    nuUINT	CollectSameRoad(nuUINT *pNameAddr, nuUINT nMaxLim);
    /**
    * @brief  ��õ�·������Ϣ�������m_SearchRoadRes�� \n
    *   ����FlushCrossInfo()                            \n
    *   ����BH RDW �ļ�                                 \n
    *   ��ÿ��BLOCK������RDW�е�A1 A2��Ϣ�鵽���õ�·�򷵻� \n
    *   ��setroad֮�󱻵���
    */
    nuBOOL    LoadRoadPos();
    /**
    * @brief  �����··����������  \n
    *   ���� CT RT BH
    */
    nuUINT	FlushCrossInfo();
    nuVOID	ClearCrossInfo();
    nuVOID	ResetCrossSearch();
    /**
    * @brief  ����blk��idx  \n
    *   ���� BH�е�blk Idx
    */
    nuUINT  BlkIDToIdx(nuUINT nBlkID);
    /**
    * @brief  ��һ��RTblock�в��ҵ�·�Ľ���·�� 
    *   ���� FlushCrossInfo()��RDW              \n    
    *   1.�ռ�ͬ��ͬ��·��                      \n
    *   2.�ռ���·��block�еĶ˵�     --RDW     \n
    *   ---����RT-A3                            \n
    *   1.���˵�����[�˵�����������ж�]      \n
    *   2.��õ�·��Ϣ[RT-A1/A2]                \n
    *   3.ͬ���ų�                              \n
    *   4.����ӵ�·�ų�
    * @param blkID
    * @param tag ��������m_SearchCrossRes����ʼλ��
    * @return ��block�������Ľ���·������
    */
    nuUINT	SearchRCBlock(nuUINT blkID, nuUINT tag, CMapFileBhY& bhfile, CMapFileRdwY& rdwfile);
    
	nuBOOL RoadNameSort(nuVOID *pWord,nuINT nLens);
	nuBOOL CheckRoadNoNumber(nuVOID *pWord,nuINT nLens);
	nuINT  TransCode(nuINT code);
private:

	//Prosper 2011.12.07
	bool    Sort_KEY_index(nuWORD);
	nuINT 	nKeyCount;
	nuWCHAR	KEY_Data[37];

    CSearchArea *m_pSearchArea;     ///searcharea ͨ�������town blkinfo
    nuWORD m_nMMIdx;                ///searchʹ�õ��ڴ���־
    nuUINT m_nMMMaxLen;             ///searchʹ�õ��ڴ�鳤��
    nuUINT m_nMMCTLen;              ///����mapʱ��ȡ��CITYTOWN��Ϣ��ʼ�շ����ڴ����ʼ��λ��
    nuUINT	m_nSzyMin;              ///�趨��������С�ʻ�
    nuUINT	m_nSzyMax;              ///�趨���������ʻ�
    nuWORD  m_nSzyZhuyin;           ///�趨������ע��
    nuUINT	m_nSzyMinT;             ///��������������������������С�ʻ�
    nuUINT	m_nSzyMaxT;             ///���������������������������ʻ�
    nuWORD  m_nSzyZhuyinT;          ///������������������������ע��
    nuUINT	m_nSzyResTotal;         ///�������������������
    nuUINT	m_nMMSzyLen;            ///��ȡ�������������ϳ���
    nuWORD	m_nSzyLoadNum;          ///��ȡ����������
    nuLONG	m_nSzySearchMapID;      ///��������������������mapid
    nuWORD	m_nSzySearchCityID;     ///��������������������cityid
    nuWORD	m_nSzySearchTownID;     ///��������������������townid
    nuUINT	m_nSzySearchTag;        ///���UI�Խ����¼���еĶ�ȡ��
    nuUINT	m_nSzySearchLastCount;  ///��һ��UI��ȡ���ֽ������
    nuWORD	m_nSzyWordbuffer[NURO_SEARCH_BUFFER_MAX_ROADSZ];    ///���������������� 
    nuWORD	m_nSzyWord;             ///�趨������
    nuWORD	m_nSzyWordT;            ///��ǵ�·�����������������
    nuWORD  m_nSearchRoadKeyDanyin[EACH_ROAD_NAME_LEN>>1];      ///�趨�ĵ�·keydanyin
    nuWORD  m_nSearchRoadKeyDanyinT[EACH_ROAD_NAME_LEN>>1];     ///��ǵ�·�������������keydanyin
    nuWORD  m_nSearchRoadKeyName[EACH_ROAD_NAME_LEN>>1];        ///�趨�ĵ�·keyname
    nuWORD  m_nSearchRoadKeyNameT[EACH_ROAD_NAME_LEN>>1];       ///��ǵ�·�������������keyname
    nuWORD	m_nCityIDTag;           ///���Ҫ������cityid
    nuWORD	m_nCityIDMax;           ///���Ҫ����������cityid
    nuUINT	m_nMMRNCLen;            ///��ȡ��RNC FILE���ϳ���
    nuUINT	m_nMMRNLen;             ///��ȡ��RN FILE���ϳ���    
    nuUINT	m_nResTotal;            ///�������ĵ�·����
    nuLONG	m_nRNCSearchMapID;      ///��ǵ�·�������������mapid
    nuWORD	m_nRNCSearchCityID;     ///��ǵ�·�������������cityid
    nuWORD	m_nRNCSearchTownID;     ///��ǵ�·�������������townid
    nuUINT	m_nRNCSearchTag;        ///���UI�Ե�·����Ķ�ȡ��
    nuUINT	m_nRNCSearchLastCount;  ///��һ��UI��ȡ��·�������
    nuUINT	m_nMRSearchTag;         ///���UI������·��¼�Ķ�ȡ��
    nuUINT	m_nMRSearchLastCount;   ///��һ��UI��ȡ����·�������
    nuUINT	m_nMainRoadTotal;       ///������������·����
    nuUINT	m_nSearchRoadNameAddr;  ///�趨�ĵ�·����ַ
    nuWORD	m_nSearchRoadCityID;    ///�趨�ĵ�·��cityid
    nuWORD	m_nSearchRoadTownID;    ///�趨�ĵ�·��townid
    nuWORD	m_nSearchRoadIdx;       ///�趨�ĵ�·�ڽ�����е�����
    SEARCH_PDN_NODE_R m_nSearchRDN; ///�趨�ĵ�·��������Ϣ��Ҫ
    nuWORD	m_nSearchRoadDoorNum;   ///�趨�ĵ�·�����ƺ�����
    nuUINT	m_nSearchRoadDoorPos;   ///�趨�ĵ�·��������Ϣ��PDN�ļ��ĵ�ַ
    nuUINT	m_nRC_RTLen;            ///��ȡ��RT�����ϳ��� -����CROSS
    nuUINT  m_nTownBlkInfoLen;      ///town��blkinfo����
    nuUINT  m_nBHTotal;             ///blk����
    nuUINT  m_nBHIdxLen;            ///��ȡ��blkidx����
    nuUINT	m_RCTotal;              ///�������Ľ���·������
    nuLONG	m_nRCSearchMapID;       ///��ǽ���·�ڽ��������mapid
    nuWORD	m_nRCSearchCityID;      ///��ǽ���·�ڽ��������cityid
    nuWORD	m_nRCSearchTownID;      ///��ǽ���·�ڽ��������townid
    nuUINT	m_nRCSearchNameAddr;    ///��ǽ���·�ڽ��������nameaddr
    nuWORD  m_nRCSearchTag;         ///���UI�Խ���·�ڵĶ�ȡ��
    nuWORD  m_nRCSearchLastCount;   ///��һ��UI��ý���·����Ϣ������
    nuUINT	m_nBLIdx;               ///���TOWN BLK INFO�ĵ�1����
    nuUINT	m_nBLIdxM;              ///���TOWN BLK INFO�ĵ�2���� ���1����һ���ǵ�ǰ������blk ID
    nuINT     m_nSASTDATA;            ///m_SASTDATA��ʵ���ռ�����
	nuBOOL    m_bIsFromBeging;        ///�q�r���}�l���
    SEARCH_SNST_DATA m_SASTDATA[_SNST_COL_LIMIT_];  ///ͬtown ͬname ��ͬnameaddr��Ϣ��¼
    SEARCH_BUFFER_ROAD m_SearchRoadRes[NURO_SEARCH_BUFFER_MAX_ROAD];    ///��·�������

#ifdef _SEARCH_ROAD_MAINROADMODE_
    SEARCH_MAIN_ROAD m_MainRoad[NURO_SEARCH_BUFFER_MAX_ROAD];           ///����·���������
#endif
    SEARCH_BUFFER_ROAD m_SearchCrossRes[NURO_SEARCH_BUFFER_MAX_CROSS];  ///����·�ڽ��

    //for searchDanyin extend
public:
    nuUINT GetRoadKeyDanyinMatchWords(nuWORD** buffer);
private:
    nuWORD      m_danYinMatchWordsTag[EACH_ROAD_NAME_LEN>>1];
    nuroMapArea m_danYinMatchWordsAreaTag;
    nuUINT      m_danYinMatchWordsCount;
    nuWORD      m_danYinMatchWordsBuffer[16*200];
	nuBOOL		m_bKickNumber ;
	nuINT		m_nNameIdx;
	nuINT		m_nDYWordIdx;
	nuINT		nSortLimt;
	
	typedef struct tag_ListName				//Unicode �� Big5 �һݵ��c 
	{
		nuWCHAR wsListName2[EACH_ROAD_NAME_LEN>>1];
	}ListName;

	
	typedef struct tag_Code				//Unicode �� Big5 �һݵ��c 
	{

		nuINT	nBig;
		nuINT	nUniCode;    

	}Trans_DATA;
	Trans_DATA *data;
	nuBOOL m_bDYData;
	nuBOOL m_bSort;
	nuWORD m_nListNameIdx;
	nuWORD m_nSearchResIdx;
	nuWORD m_nTownIdx;


	nuINT  m_nTempMap;
	nuINT  m_nTempCity;
	nuBOOL bLoadAfter;
	nuWORD m_nTownInfoMemIdx;
};
#endif // !defined(AFX_SEARCHROAD_H__69340EF9_C168_4655_A955_5629DF66D5DA__INCLUDED_)
