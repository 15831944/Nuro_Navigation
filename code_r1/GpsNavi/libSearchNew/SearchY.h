#if !defined(AFX_SEARCHY_H__B70EFCBE_9CCC_4004_BC5D_29B00AA0F1B4__INCLUDED_)
#define AFX_SEARCHY_H__B70EFCBE_9CCC_4004_BC5D_29B00AA0F1B4__INCLUDED_

 
#include "NuroDefine.h"
#include "nuSearchDefine.h"
#include "SearchBaseZ.h"
#include "SearchArea.h"
#include "SearchPoi.h"
#include "SearchRoad.h"	
#include "MapFileSKB.h"
/**
 * @brief ��ͼ����������
 * ����ģ�飺POI���� ��ͼ���� ��·����
*/
class CSearchY : public CSearchBaseZ
{
public:
    CSearchY();
    virtual ~CSearchY();    
    /**
     * @brief ��ʼ������
     * @param nidx Ϊ����������ڴ�����
     * @param nLen Ϊ����������ڴ泤��
     * @return nuTRUE: �ɹ� nuFALSE: ʧ��
    */
    nuBOOL Init(nuWORD nIdx, nuUINT nLen);
    nuVOID Free();
    nuBOOL SetMapId(nuLONG resIdx);
    nuBOOL SetCityId(nuWORD resIdx);
    nuBOOL SetTownId(nuWORD resIdx);
    nuBOOL SetPoiTP1(nuUINT resIdx);
   // nuBOOL SetPoiTP1(nuUINT resIdx,nuUINT word);

    nuBOOL SetPoiTP2(nuUINT resIdx);
    nuBOOL SetPoiKeyDanyin( nuWCHAR *pDanyin, nuBOOL bComplete);
    nuBOOL SetPoiKeyDanyin2( nuWCHAR *pDanyin, nuBOOL bComplete);   
	nuBOOL SetPoiKeyName(nuWCHAR *pName, nuBOOL bFuzzy);
    nuBOOL SetPoiKeyPhone(nuWCHAR *pPhone);
    nuBOOL SetSearchArea(NURORECT *pRect);
    nuBOOL SetRoadSZSLimit(nuUINT nMin, nuUINT nMax);
    nuBOOL SetRoadSZZhuyin(nuWORD zhuyin);
    nuBOOL SetRoadSZ(nuUINT nResIdx);
    nuBOOL SetRoadKeyDanyin(nuWORD *pDanyin);
    nuBOOL SetRoadKeyDanyin2(nuWORD *pDanyin);
	nuBOOL SetRoadKeyName(nuWORD *pKeyWord, nuBOOL bIsFromBeging = nuFALSE);
    nuBOOL SetRoadName(nuUINT nResIdx, nuBOOL bRealIdx);
    nuVOID SetStrokeLimIdx(nuUINT nResIdx); ///���ñʻ�����ʱ��������ʼ
    /**
     * @brief ��������ݵ����� ��ȡ�������
    */
    nuUINT	GetPoiCarFacAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL	SetPoiCarFac(nuUINT nResIdx);
    /**
     * @brief �������� ��ȡ��������������
    */
    nuUINT  GetPoiSPTypeAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL	SetPoiSPType(nuUINT nResIdx);    
    nuUINT	GetCityTotal();
    nuUINT	GetTownTotal();
    nuUINT	GetPoiTotal();
    nuUINT	GetTP1Total();
    nuUINT	GetRoadSZTotal();//��ȡ��·��������
    nuUINT	GetRoadTotal();
    nuUINT	GetRoadCrossTotal();
    /**GetRoadTownID
     * @brief �����¼�Ĵ������� 
     * ����������������ֹ��� 
     *
     * @param pHeadWords ���ִ�
     * @param pBuffer �����Ѽ�������ڴ�
     * @param nMaxWords ������������������
     *
     * @return �����Ѽ����Ĵ�������
    */
    nuUINT	GetNextWordAll(nuWORD* pHeadWords, nuWORD *pBuffer, nuUINT nMaxWords);    
    nuINT GetMapNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuINT GetCityNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuINT GetTownNameAll(nuVOID *pBuffer, nuUINT nMaxLen);    
    /**
     * @brief �����¼�Ĺؼ��ֹ���-��������
     *
     * @param pKey �ؼ����޶�
     * @param pBuffer ���������ڴ� �������ݰ�NURO_SEARCH_FILTERRES��ʽ��
     * @param nMaxLen �ڴ泤��
     *
     * @return �����Ѽ����Ľ������
    */
    nuINT GetFilterResAll(const nuWCHAR *pKey, nuVOID *pBuffer, nuUINT nMaxLen);    
    /**
     * @brief ���POI�������
     *
     * @param type ��������
     * @param nMax �����������
     * @param pBuffer ���������ڴ� �������ݰ�NURO_SEARCH_NORMALRES��ʽ��
     * @param nMaxLen �ڴ泤��
     *
     * @return �����Ѽ����Ľ������
    */
    nuINT  GetPoiNameList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
//	nuINT  GetPoiNameList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen,nuUINT word);
    nuINT  GetPoiTP1All(nuVOID *pBuffer, nuUINT nMaxLen);
    nuINT  GetPoiTP2All(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL GetPoiMoreInfo(nuUINT nResIdx, SEARCH_PA_INFO *pPaInfo, nuBOOL bRealIdx);
    nuBOOL GetPoiPos(nuUINT nResIdx, NUROPOINT* pos, nuBOOL bRealIdx);
    nuBOOL GetPoiCityName(nuUINT nResIdx, nuWORD *pBuffer, nuUINT nMaxLen, nuBOOL bRealIdx);
	nuLONG GetPoiCityID(nuUINT nResIdx, nuBOOL bRealIdx); // Added by Damon 20100309
    nuBOOL GetPoiTownName(nuUINT nResIdx, nuWORD *pBuffer, nuUINT nMaxLen, nuBOOL bRealIdx);
	nuUINT GetPoiNearDis(nuUINT nResIdx, nuBOOL bRealIdx);
    /**
     * @brief ���绰��ȷ����POI
    */
    nuBOOL GetPoiByPhone(const nuWCHAR *pPhone, SEARCH_POIINFO *pInfo);    
    nuINT	 GetRoadSZList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
    /**
     * @brief ���ROAD�������
     *
     * @param type ��������
     * @param nMax �����������
     * @param pBuffer ���������ڴ� �������ݰ�NURO_SEARCH_NORMALRES��ʽ��
     * @param nMaxLen �ڴ泤��
     *
     * @return �����Ѽ����Ľ������
    */
    nuINT	 GetRoadNameList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);	
    nuBOOL GetRoadPos(NUROPOINT* pos);
    nuBOOL GetRoadTownName(nuWORD *pBuffer, nuUINT nMaxLen);
    nuBOOL GetRoadCityName(nuWORD *pBuffer, nuUINT nMaxLen);
    nuUINT	GetRoadDoorTotal();
    /**
     * @brief ��ȡ���ƺ���Ϣ
     * ��������Ҫ�����ĵ�·
    */
    nuBOOL GetRoadDoorInfo(nuVOID *pBuffer, nuUINT nMaxLen);
    /**
     * @brief ���ROADCROSS�������
     *
     * @param type ��������
     * @param nMax �����������
     * @param pBuffer ���������ڴ� �������ݰ�NURO_SEARCH_NORMALRES��ʽ��
     * @param nMaxLen �ڴ泤��
     *
     * @return �����Ѽ����Ľ������
    */
    nuINT	 GetRoadCrossList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
    nuBOOL GetRoadCrossPos(nuUINT nResIdx, NUROPOINT* pos);
    nuBOOL GetRoadCrossTownName(nuUINT nResIdx, nuWORD *pBuffer, nuUINT nMaxLen);
    nuBOOL GetRoadCrossCityName(nuUINT nResIdx, nuWORD *pBuffer, nuUINT nMaxLen);    
    nuUINT	GetMainRoadTotal();///����·ģʽAPI
    nuUINT	GetChildRoadTotal(nuUINT nMainRoadIdx, nuBOOL bRealIdx);///����·ģʽAPI
    nuINT		GetRoadNameList_MR(NURO_SEARCH_TYPE type, nuWORD nMax, nuVOID* pBuffer, nuUINT nMaxLen);///����·ģʽAPI
    nuUINT	GetRoadNameALL_MR(nuUINT nMainRoadIdx, nuVOID* pBuffer, nuUINT nMaxLen, nuBOOL bRealIdx);///����·ģʽAPI
    nuBOOL	SetRoadName_MR(nuUINT nMainRoadIdx, nuUINT nRoadIdx, nuBOOL bRealIdx);///����·ģʽAPI

    //add prosper.05
    nuVOID Stroke_GetNextWordData(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID* candi, const nuUINT candylen, const nuBOOL ReSort);
    nuVOID ZhuYinForSmart_SecondWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont, const nuUINT candylen, const nuBOOL ReSort);
    nuBOOL ZhuYinForSmart_OtherWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID *candi, const nuUINT candylen, const nuBOOL ReSort);
    nuVOID Stroke_Poi_GetNextWordData(nuVOID* pPoiBuf, const nuUINT PoiBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID* candi, const nuUINT candylen, const nuBOOL ReSort);
    nuVOID ZhuYinForSmart_Poi_SecondWords(nuVOID* pPoiBuf, const nuUINT PoiBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont, const nuUINT candylen, const nuBOOL ReSort);
    nuBOOL ZhuYinForSmart_Poi_OtherWords(nuVOID* pPoiBuf, const nuUINT PoiBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID *candi, const nuUINT candylen, const nuBOOL ReSort);
  
	nuINT GetPoiPZList(NURO_SEARCH_TYPE type, nuWORD nMax, nuBYTE* pBuffer, nuUINT nMaxLen);
    nuUINT	GetPoiPZTotal();
    nuBOOL SetPoiPZZhuyin(nuWORD zhuyin);
	//nuUINT	GetPoiTotal(nuUINT temp);
	nuBOOL SetPoiPZ(nuUINT nResIdx);
	nuBOOL SetPoiKeyNameP(nuWCHAR *pName, nuBOOL bFuzzy);
	nuINT  GetRoadTownID();

	nuUINT SetAreaCenterPos(nuroPOINT pos);
    //�ڴ���� SKB״̬����
    	nuBOOL    StartSKBSearch(nuUINT nType);
        nuVOID    StopSKBSearch();
    /**
    * @brief �����ƴ����ѯ�б�
    *   �ڴ������road�������������ǰ CT֮��
    * @param keyStr ����ƴ���б�
    * @param pBuffer ��ѯ����б�
    * @param nMaxLen pBuffer����
    * @param resCount ����漰�ĵ�·����
    * @return ��õ�ƴ������
    */
     nuINT     GetSKBAll(nuCHAR* keyStr, nuCHAR* pBuffer, nuINT nMaxLen, nuINT* resCount);
     nuINT GetNDYSKBAll(nuCHAR* keyStr, nuCHAR* pBuffer, nuINT nMaxLen, nuINT* resCount);
     nuINT    GetSKBInBuffer(nuCHAR* pBuffer, nuINT nMaxLen);
	 nuBOOL   JudgeSKB(nuCHAR* strDes, nuCHAR* strSrc, nuINT nDesLen, nuINT nSrcLen, nuWORD townID);
	nuLONG    m_SKBMapIDT;
    nuWORD  m_SKBCityIDT;
    nuWORD  m_SKBTownIDT;
    nuUINT  m_SKBLoadLen;
    nuUINT  m_SKBResT;
    SEARCH_SKB_CITYINFO infoT;
    nuCHAR    m_SKBKeyStrT[128];
    nuBYTE  m_SKBBuffer[128];
   

	nuBOOL GetMode(VOICEROADFORUI& data,nuVOID* wName,nuBOOL &bMode);
	nuBOOL GetPosInfo(nuBOOL &bNumChange,nuINT &nDoorNum,nuINT nDoorNum2,nuroPOINT &point);
	//nuBOOL SetVoiceSPDKeyName(VOICEROADFORUI data,nuVOID* wRoad,nuroPOINT &point);
	nuBOOL SetNoName(nuBOOL bRes);

	nuBOOL GetRoadSKB(nuVOID* pSKBBuf, nuUINT& nCount); //Prosper 2011 1216
	nuBOOL GetPoiSKB(nuVOID* pSKBBuf, nuUINT& nCount);	//Prosper 2011 1216

	nuBOOL GetRoadWordData(nuINT &nTotal,nuVOID* pBuffer, nuUINT nMaxLen);
	nuBOOL  LoadSKB(nuVOID* pBuffer,nuVOID* pBuffer2);
	nuBOOL GetNEXTAll(nuVOID* pSKBBuf, nuUINT& nCount);
private:
    /**
     * @brief ����������ģ���������
    */
    nuVOID ResetAllSearch();
    //nuBOOL StartSearchPoi(nuUINT);//prosper
	nuWORD g_nSKBMMIdx;
	nuWORD g_nSKBMMIdx2;

	nuBOOL StartSearchPoi();
    nuVOID QuitSearchPoi();
    nuBOOL StartSearchRoad();
    nuVOID QuitSearchRoad();
private:
    CSearchArea	m_SearchArea;//��������
    CSearchPoi	m_SearchPoi;//POI����
#ifdef _USE_SEARCH_ROAD_
    CSearchRoad m_SearchRoad;//��·����
#endif
    nuWORD	m_nLoadBufferIdx;//ΪSEARCHģ���ṩ���ڴ�����
    nuUINT	m_nLoadBufferMaxLen;//ΪSEARCHģ���ṩ���ڴ��С
    nuUINT	m_nLB_CTLen;//�����CITY TOWN��Ϣ����
	nuINT temp; //prosper

	 nuUINT count;
	   nuWORD townID;
	  nuroPOINT m_pos;
	  // nuCHAR *pSkb,*pSkb1;
};

#endif // !defined(AFX_SEARCHY_H__B70EFCBE_9CCC_4004_BC5D_29B00AA0F1B4__INCLUDED_)
