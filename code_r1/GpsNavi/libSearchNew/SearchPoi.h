#if !defined(AFX_SEARCHPOI_H__E7F89252_746D_4834_9F2C_C55FACACFCF1__INCLUDED_)
#define AFX_SEARCHPOI_H__E7F89252_746D_4834_9F2C_C55FACACFCF1__INCLUDED_

#include "SearchBaseZ.h"
class CMapFilePnY;

/**
* @class CSearchPoi
* @brief POI���� \n
*   ģ���ڴ��������ȡ����˳��δʹ�õ����ݳ���Ϊ0�� \n
*   AREA����--CT��BHIdx \n
*   ��AREA����--CT��PI��PN  \n
*   �����������Ϻ��������ʹ����ͬһ�������ǣ������ÿ��������ʱ��ͬ�������Ӧ�������
*/
class CSearchPoi : public CSearchBaseZ  
{
public:
    CSearchPoi();
    virtual ~CSearchPoi();
    nuBOOL Init(nuWORD nIdx, nuUINT nLen, nuUINT nIdleAddr);
    nuVOID Free();    
    nuBOOL SetPoiKeyDanyin(nuWCHAR *pDanyin,nuBOOL bComplete = nuFALSE ); // @bComplete added 20100118 by ouyangΪ�˵���������ȡ��ȫһ�µ��ִ�
	nuBOOL SetPoiKeyDanyin2(nuWCHAR *pDanyin,nuBOOL bComplete = nuFALSE ); // @bComplete added 20100118 by ouyangΪ�˵���������ȡ��ȫһ�µ��ִ�

	nuBOOL SetSearchArea(NURORECT *pRect);
    nuBOOL SetPoiKeyPhone(nuWCHAR *pPhone);    
    nuUINT	GetTP1Total();
    nuUINT	GetPoiTotal();    
    nuBOOL	GetPoiByPhone(const nuWCHAR *pPhone, SEARCH_POIINFO *pInfo);
    
	nuUINT  FlushPZYInfo();
	nuVOID    ClearPZYInfo();
    nuVOID    ResetPZSearch();
	nuVOID	ClearRNInfo();
	nuUINT  GetPoiPZTotal();
	nuINT     GetPoiPZList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
    nuWORD  SearchPoiPZ();
    nuBOOL    SetPoiPZZhuyin(nuWORD zhuyin);
   
	nuUINT GetPoiTotal(nuUINT);

	nuVOID    SetKeyNameFuzzy(const nuBOOL c_bFuzzy);
    /**
    * @brief ���poi�������                        \n
    *   �����NURO_SEARCH_NORMALRES����             \n
    * @return ��õ�poi����                         \n
    *   --��ʹ�÷�ҳʱ������ֵ�ĸ�16λΪ������ڵ�ҳ������16λΪpoi����
    */
    nuINT		GetPoiNameList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);   
	
	//prosper
	nuVOID ZhuYinForSmart_SecondWords(nuVOID* pPoiBuf, const nuUINT PoiBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& m_iCount, const nuUINT SelectWord, const nuBOOL ReSort);
	nuBOOL ZhuYinForSmart_OtherWords(nuVOID* pPoiBuf, const nuUINT PoiBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& m_iCount,nuVOID *candi, const nuUINT candylen, const nuBOOL ReSort);
	nuVOID Stroke_GetNextWordData(nuVOID* pPoiBuf, const nuUINT PoiBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID* candi, const nuUINT candylen, const nuBOOL ReSort);
    nuBOOL SetPoiKeyName(nuWORD *pKeyWord, nuBOOL bIsFromBeging);

    nuBOOL    SetPoiPZ(nuUINT nResIdx);
    
	//PROSPER 2011.1207
	nuBOOL     Sort_KEY_index(nuWORD);
	nuBOOL     GetPoiSKB(nuVOID* pSKBBuf, nuUINT& nCount);
	nuWCHAR	   KEY_Data[100];
	nuINT      nKeyCount;
	nuINT	   m_nCityID;
	nuINT	   m_nMAPID;




    /**
    * @brief �Խ�����ж�������                     \n
    *   ������pBuffer�����ɵĽ��                   \n
    *   pBuffer�е�������NURO_SEARCH_FILTERRES����  \n
    *   �����Я����ʵ���ڲ�idx                     \n
    *   Ҫʹ�øý���еĵ�·�������ã���Ҫ������ڲ�idx �����bRealIdxΪnuTRUE
    */
    nuINT		GetPoiFilterResAll(const nuWCHAR *pKey, nuVOID *pBuffer, nuUINT nMaxLen);    
    nuUINT	GetPoiTP1All(nuVOID *pBuffer, nuUINT nMaxLen);
    nuUINT	GetPoiTP2All(nuVOID *pBuffer, nuUINT nMaxLen);    
    nuUINT	GetPoiCarFacAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL    SetPoiCarFac(nuUINT nResIdx);
    nuUINT  GetPoiSPTypeAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL  	SetPoiSPType(nuUINT nResIdx);    
    nuBOOL    GetPoiMoreInfo(nuUINT nResIdx, SEARCH_PA_INFO *pPaInfo, nuBOOL bRealIdx=0);
    nuBOOL  	GetPoiPos(nuUINT nResIdx, NUROPOINT* pos, nuBOOL bRealIdx=0);
    nuWORD	GetPoiCityID(nuUINT nResIdx, nuBOOL bRealIdx=0);
    nuWORD	GetPoiTownID(nuUINT nResIdx, nuBOOL bRealIdx=0); 
    nuUINT  GetNextWordAll(nuWORD* pHeadWords, nuWORD *pBuffer, nuUINT nMaxWords);
	nuUINT  GetPoiNearDis(nuUINT nResIdx, nuBOOL bRealIdx=0);


	

    nuVOID ClearSearchInfo();

	nuINT	TransCode(nuINT code);
	nuVOID  SortByStroke(nuINT nTotal);
	nuUINT	Load(); // PROSPER 2013,05 add
	nuUINT SetAreaCenterPos(nuroPOINT pos);
	nuBOOL GetNEXTWORD(nuVOID* pKEYBuf, nuUINT& nCount) ;
private:
    /**
    * @brief ��ȡ��area����poiʱ��Ҫ������  ����BH��
    */
    nuBOOL LoadSearchInfo_AREA();
    /**
    * @brief ��cityid��ȡsearch��Ҫ������  ����PI��PN��
    * @param cityID 
    * @param bLoadPN �Ƿ���ҪloadPN������ ��Ԥ��POI��������ʱ ���Բ�������ȡCITY��PN��Ϣ
    */
    nuBOOL LoadSearchInfo_CITY(nuWORD cityID, nuBOOL bLoadPN=nuTRUE);    
    /**
    * @brief  ��ȡ���绰����ʱ��Ҫ������ \n
    * ��SearchNextPoi_PHONE ����  ͣ��
    */
    //nuBOOL LoadSearchInfo_PHONE(nuWORD cityID); 
    nuVOID ResetPoiSearch();
    /**
    * @brief  �绰���� \n
    *   �绰�����ɴ�API�������� �����SearchNextPoi_PHONEʵ��   \n
    *   ��֧�ֱʻ����� POI����Ϣ����ȡ�õ�������ʱȥ����
    * @param type ��������
    * @param nMax ��෵������
    * @param pBuffer ���������ڴ�
    * @param nMaxLen �ڴ泤��
    */
    nuINT		GetPoiList_PHONE(NURO_SEARCH_TYPE type, nuWORD nMax, 
        nuBYTE* pBuffer, nuUINT nMaxLen);    
    nuUINT	SearchNextPoi(NURO_SKT skt, nuUINT tag);
    /**
    * @brief  ��danyin/name���� \n
    *        ����LoadSearchInfo_CITY
    * @param tag �ڲ�����������ַ ���Ա�����
    */
    nuUINT	SearchNextPoi_NAME(nuUINT tag);
	nuUINT	SearchNextPoi_NAME_CN(nuUINT tag);

    /**
    * @brief  ��TP1/TP2���� \n
    *        ����LoadSearchInfo_CITY
    * @param tag �ڲ�����������ַ ���Ա�����
    */
    nuUINT	SearchNextPoi_TYPE(nuUINT tag);

	//add prosper 05
//	nuUINT	SearchNextPoi_TYPE2(nuUINT tag,nuUINT word);
    
	//nuUINT	SearchNextPoi_PHONE(nuUINT tag);//ʵ�ֱ�GetPoiList_PHONEȡ��
    /**
    * @brief  ��AREA����\n
    *       ����LoadSearchInfo_AREA �������� ����PDW FILE
    */
    nuUINT	SearchNextPoi_AREA();
    /**
    * @brief  ��������������������ʵ�� �������� 
    */
    nuUINT	SearchNextPoi_Car();
    /**
    * @brief  ��SPI��������������ʵ�� �������� 
    */
    nuUINT	SearchNextPoi_SPI();
    nuUINT  BlkIDToIdx(nuUINT nBlkID);

	

	// Added by damon 20100202
	#define LONEFFECTCONST						1.113
	#define LATEFFECTCONST						1.109
	#define EFFECTBASE							1.000
	#define DEGBASE								100000

	double getLatEffect(nuroPOINT pt)
	{
		return (nuCos(pt.y/DEGBASE)*((pt.y*10/DEGBASE)%10) + nuCos(pt.y/DEGBASE+1)*(10-((pt.y*10/DEGBASE)%10)))/10;
	}
	// ---------------------

	

private:
    //nuBOOL    nuPhoneJudge(nuWCHAR* pDes, nuWCHAR* pKey, nuUINT desLen, nuUINT keyLen);

    /**
    * @brief  �绰��Ϣ�Ƚ� ����'-'
    * @param pDes �绰1
    * @param pSrc �绰2
    * @param desLen �绰1����
    * @param keyLen �绰2����
    */
    nuINT     nuPhoneCompare(nuWCHAR* pDes, nuWCHAR* pSrc, nuUINT desLen, nuUINT keyLen);
    
    /**
    * @brief  ���POI Name \n
    *       ��PN�ɶ�ȡ����ʱ�����ڴ��ж�ȡ���������ֱ�Ӵ�PN file��ȡname��Ϣ
    * @param idx �ڲ�POI���������
    * @param pNameBuffer ���������ڴ�
    * @param nMaxLen �ڴ泤��
    * @param pnfile PN�ļ�
    */
    nuBOOL    GetPoiName(nuUINT idx, nuBYTE* pNameBuffer, nuUINT nMaxLen, CMapFilePnY &pnfile);
    nuBYTE* GetPoiNameInfo(nuUINT addr);
    nuBOOL  	FillResBuffer(nuUINT tag, SEARCH_PI_POIINFO *pPoiInfo, nuBYTE strokes=-1);
    nuUINT  FindPhoneMatch();
    nuWORD	m_nLoadBufferIdx;   ///searchʹ�õ��ڴ���־
    nuUINT	m_nLoadBufferMaxLen;///searchʹ�õ��ڴ�鳤��
    nuWORD	m_nCityIDTag;       ///city����ʱ����ǵ�ǰ��������cityid
    nuWORD	m_nCityIDMax;       ///city����ʱ�������������cityid
    nuWORD	m_nCityIDLoad;      ///city����ʱ�����load�ص�����cityid
    nuUINT	m_nLoadPoiCount;    ///����load�ص������е�poi��
    nuUINT	m_nLB_CTLen;        ///����mapʱ��ȡ��CITYTOWN��Ϣ��ʼ�շ����ڴ����ʼ��λ��
    nuUINT	m_nLB_PILen;        ///��ȡ�ص�PI���� ��>0 ��ȡ��PI��Ϣ���ڴ�������m_nLB_CTLen��
    nuUINT	m_nLB_PNLen;        ///��ȡ�ص�PN���� ��>0 ��ȡ��PI��Ϣ���ڴ�������m_nLB_PILen��
    nuUINT	m_nLoadPnBaseAddr;  ///load��PN�������PN�ļ���ƫַ ����ת��nameaddr���ڴ��еĵ�ַ
    nuUINT  m_nLB_PILen2;
	nuUINT	m_nLoadPoiCount2;
    nuUINT	m_nLB_PNLen2; 
	nuUINT  m_nLoadPnBaseAddr2;
	
    nuLONG    m_nLB_PAMapID;      ///��Ƕ�ȡ��PA���ϵ�MAPID
//     nuUINT	m_nLB_PALen;    ///��ȡ��PA���ϵĳ���     
//     nuLONG    m_nLB_PI_B_MapID;
//     nuUINT  m_nLB_PI_B_Len;
//     nuUINT  m_nLB_PI_B_Total;
    nuUINT  m_firstPos;         ///��ǵ绰�����������ʼλ��
    nuUINT  m_lastPos;          ///��ǵ绰��������Ľ���λ��    
    nuWORD	m_nSearchPoiKeyDanyin[EACH_POI_NAME_LEN>>1];    ///���õ�keydanyin
    nuWORD	m_nSearchPoiKeyDanyinT[EACH_POI_NAME_LEN>>1];   ///��ǽ��������keydanyin����
    nuWORD	m_nSearchPhone[32];         ///���õ�keyphone
    nuWORD	m_nSearchPhoneT[32];        ///��ǽ��������keyphone����
    NURO_SEARCHINFO m_SearchBufferInfo; ///��ǽ��������searchinfo����    
    nuWORD	m_nSearchTagPos;            ///���UI�Խ����¼���еĶ�ȡ��
    nuUINT	m_nLastGetCount;            ///��һ��UI��ȡnamelist�������
    nuUINT	m_nResTotal;                ///����������POI���� Ϊ-1ʱ��ʾ�޽��
    nuUINT  m_nCarFac;                  ///���õĳ�������
    nuUINT  m_nCarFacT;                 ///��ǽ�������ĳ�����������    
    nuUINT  m_nSPType;                  ///���õ�SPI����
    nuUINT  m_nSPTypeT;                 ///��ǽ��������SPI����    
    nuBOOL    m_bSA;                      ///��ʾ��ʹ��AREA����
    nuBOOL	m_bSAT;                     ///��ǽ���Ƿ�����AREA����
    NURORECT	m_sAreaRect;            ///���õ�AREA����
    NURORECT	m_sAreaRectT;           ///��ǽ��������AREA����
    nuUINT	    m_nBHIdxLen;            ///��ȡ�ص�BH��Ϣ���� ��AREA����ʱʹ�� ��ȡ���� \n
                                        ///��m_nLB_CTLen��    
    SEARCH_BUFFER m_SearchRes[NURO_SEARCH_BUFFER_MAX_POI];///�������
    nuWORD  m_nSearchPoiKeyName[EACH_POI_NAME_LEN>>1];
	nuWORD  m_nSearchPoiKeyNameT[EACH_POI_NAME_LEN>>1];
	nuBOOL    m_bIsFromBeging;            ///�q�r���}�l���;

	nuBOOL     m_bComCompare; //added 20100118 by ouyang ��ǵ������������ǲ��ǲ�����ȫ�ȶԵķ�ʽ��������ȫ�ȶԵ��ִ�
	nuBOOL     m_bKeyNameFuzzy;
	
	nuBOOL     check;
	nuINT      temp;
	nuINT      num;

	nuINT CheckWordIsNumber(nuWORD WordCode); //CheckWord for Sort , prosper add by 20130701

   nuUINT m_nMMPzyLen;

	nuUINT m_nPzyLoadNum;
    nuUINT m_nPzySearchCityID;
    nuUINT m_nPzySearchMapID;

	nuUINT m_nPzySearchTag;
    nuUINT m_nPzySearchLastCount;

    nuUINT m_nPzyMinT ;
    nuUINT m_nPzyMaxT ;
    nuUINT m_nPzyZhuyinT;
    
    nuUINT m_nPzySearchTownID ;
    nuUINT m_nPzyResTotal;
	nuWORD m_nPzyWordbuffer[NURO_SEARCH_BUFFER_MAX_ROADSZ];    ///����������������

    nuUINT m_nPzyZhuyin;
	nuUINT m_nPzyMin;
	nuUINT m_nPzyMax;
    nuUINT Pzy_count;

	nuWORD  m_nDY_countIdx;
	nuWORD  m_nsort_countsIdx;
	nuBOOL  m_bcheck;
    

    nuWORD	m_nPzyWord;             ///KEYWORD
    nuINT 	nFirstSort ; 
	

	typedef struct tag_Code				//Unicode �� Big5 �һݵ��c 
	{

		nuINT	nBig;
		nuINT	nUniCode;    

	}Trans_DATA;
	Trans_DATA *data;
	nuINT		m_nWordIdx;
	nuINT		nSortLimt;
	nuBOOL		m_bNameSort;
	nuBOOL      m_bSort;
	
	//nuINT	    *m_nWordStartIdx;//[NURO_SEARCH_BUFFER_MAX_DYPOI];
	//nuINT	    *m_nWordLens;//[NURO_SEARCH_BUFFER_MAX_DYPOI];
	nuBOOL		m_bIndexSort;

	nuWORD	m_nWordStartIdxMemIdx;
	nuWORD	m_nWordLensMemIdx;
	nuWCHAR	   m_wsNEXT_WORD_Data[NEXT_WORD_MAXCOUNT];
	nuINT      nNEXT_WORD_COUNT;
	
	nuBOOL	m_bSetAreaCenterPos;
	nuroPOINT m_TypeCenterPos;
	nuINT		m_POI_DY_COUNT;

};

#endif // !defined(AFX_SEARCHPOI_H__E7F89252_746D_4834_9F2C_C55FACACFCF1__INCLUDED_)
