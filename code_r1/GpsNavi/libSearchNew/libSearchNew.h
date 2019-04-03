/******************************************
* @file libSearchNew.h
*
* search lib ��������
*******************************************/
#ifndef	__NURO_NEW_SEARCH_20081001
#define	__NURO_NEW_SEARCH_20081001

#include "NuroDefine.h"
#include "NuroModuleApiStruct.h"
#include "nuSearchDefine.h"

#ifdef _USRDLL

#ifdef SEARCHNEW_EXPORTS
#define SEARCHNEW_API extern "C" __declspec(dllexport)
#else
#define SEARCHNEW_API extern "C" __declspec(dllimport)
#endif

#else
#define SEARCHNEW_API extern "C"
#endif

/**
* @brief  ��ʼ����������
*
* @param pApiAddr ������ģ��API
* @return ����ֵ��ʾ�Ƿ��ʼ���ɹ� \n
*	true: �ɹ�\n
*	false: ʧ��\n
*/
SEARCHNEW_API 
nuBOOL LibSH_InitSearchZ(APISTRUCTADDR* pApiAddr);

/**
* @brief ��ֹģ��
*/
SEARCHNEW_API 
nuVOID LibSH_FreeSearchZ();
/**
* @brief  ����sarch
*
* @param nMMIdx �ڴ��ַ-δʹ�ô˲���
* @param nMMLen �ڴ��С
* @return ����ֵ��ʾ�Ƿ��ʼ���ɹ� \n
*	true: �ɹ�\n
*	false: ʧ��\n
* 
*������search �����ڴ�
*/
SEARCHNEW_API nuBOOL LibSH_StartSearch(nuWORD nMMIdx, nuUINT nMMLen);
/**
* @brief  ��ֹsearch ��������ֹdanyin����ģ�飩
* 
*/
SEARCHNEW_API nuVOID LibSH_EndSearch();
/**
* @brief  ��ȡmapinfo
* ���BH HEAD������mapinfo
*/
SEARCHNEW_API nuBOOL LibSH_GetMapInfo(nuLONG mapid, SEARCH_MAP_INFO &mapinfo);
/**
* @brief  ��������ĵ�ͼID
* @param resIdx ��ͼID ����LibSH_GetMapNameAll
* ������CBINFO-city town��Ϣ 
* Ĭ������searchʱ ��setmapip(0)
*/
SEARCHNEW_API nuBOOL LibSH_SetMapId(nuLONG resIdx);
/**
* @brief  ����������cityid
* @param resIdx cityid ����LibSH_GetCityNameAll
*/
SEARCHNEW_API nuBOOL LibSH_SetCityId(nuWORD resIdx);

/**
* @brief  ����������townid
* @param resIdx townid ����LibSH_GetTownNameAll
*/
SEARCHNEW_API nuBOOL LibSH_SetTownId(nuWORD resIdx);
/**
* @brief  ��������poi������1 id
* @param resIdx ��LibSH_GetPoiTP1All����
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiTP1(nuUINT resIdx); 

/**
* @brief  ��������poi������2 id
* @param resIdx ����LibSH_GetPoiTP2All
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiTP2(nuUINT resIdx);
/**
* @brief  ��������poi��keydanyin
* @param pDanyin ���������ؼ����ַ��� nuWCHAR
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiKeyDanyin(nuWCHAR *pDanyin,nuBOOL bComplete);
/**
* @brief  ��������poi��keyname
* @param pName ���������ؼ����ַ��� nuWCHAR
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiKeyName(nuWCHAR *pName, nuBOOL bFuzzy);
/**
* @brief  ��������poi��phonen
* @param pPhone �绰�����ؼ����ַ��� nuWCHAR
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiKeyPhone(nuWCHAR *pPhone);
/**
* @brief  ��������poi������Χ
* @param pRect poi������Χ
*/
SEARCHNEW_API nuBOOL LibSH_SetSearchArea(NURORECT *pRect);
/**
* @brief  ����������·���ֵıʻ�����Χ
* @param nMin ��Сֵ
* @param nMax ���ֵ
* [nMin, nMax]�����䷶Χ
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadSZSLimit(nuUINT nMin, nuUINT nMax);
/**
* @brief  ����������·����ע��
* @param zhuyin ���õ�����ע�� nuWCHAR
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadSZZhuyin(nuWORD zhuyin);
/**
* @brief  ���õ�·����������
* @param nResIdx ����LibSH_GetRoadSZList
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadSZ(nuUINT nResIdx);
/**
* @brief  ���õ�·������keydanyin
* @param pKeyWord ��·���������ؼ����ַ��� nuWCHAR
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadKeyDanyin(nuWORD *pKeyWord);
/**
* @brief  ���õ�·������keyname
* @param pKeyWord ��·�������ƹؼ����ַ��� nuWCHAR
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadKeyName(nuWORD *pKeyWord, nuBOOL bIsFromBeging = false);
/**
* @brief  ���õ�·��������- Ϊ��һ����ȡ��·��Ϣ��ǰ�᡾��ȡ����·�ڵȡ�\n
*           ����·ģʽ��ʹ��LibSH_SetRoadName_MR
* @param nResIdx ��·���� \n
*       ������ȡ��·���Ĳ�����LibSH_GetRoadNameList�ȡ�
* @param bRealIdx �Ƿ���ʵ����  \n
*       ��Ϊtrue����nResIdx�������� Я���˵�·���ڲ�����е���ʵ���� ����LibSH_GetFilterResAll��
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadName(nuUINT nResIdx, nuBOOL bRealIdx);
/**
* @brief  ���ñʻ�����
* @param nResIdx ����GETNAMELIST���Ʋ���
*   �����ص�namelist�е�һ��idxֵ��Ϊ�ʻ����� ʵ�ֱʻ��ϡ��ʻ��µ�ǰ�� 
*/
SEARCHNEW_API nuVOID LibSH_SetStrokeLimIdx(nuUINT nResIdx);


//prosper 05
SEARCHNEW_API nuVOID LibSH_Stroke_GetNextWordData(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID* pCady, const nuUINT candylen, const nuBOOL ReSort);
SEARCHNEW_API nuVOID LibSH_ZhuYinForSmart_SecondWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont, const nuUINT candylen, const nuBOOL ReSort);
SEARCHNEW_API nuBOOL LibSH_ZhuYinForSmart_OtherWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID *candi, const nuUINT candylen, const nuBOOL ReSort);

SEARCHNEW_API nuVOID LibSH_Stroke_Poi_GetNextWordData(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID* pCady, const nuUINT candylen, const nuBOOL ReSort);
SEARCHNEW_API nuVOID LibSH_ZhuYinForSmart_Poi_SecondWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont, const nuUINT candylen, const nuBOOL ReSort);
SEARCHNEW_API nuBOOL LibSH_ZhuYinForSmart_Poi_OtherWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& WordCont,nuVOID *candi, const nuUINT candylen, const nuBOOL ReSort);

SEARCHNEW_API nuINT  LibSH_Smart_GetPoiList(NURO_SEARCH_TYPE st, nuWORD nMaxPoi, nuVOID* pBuffer, nuUINT nMaxLen,nuUINT word);

SEARCHNEW_API nuINT  LibSH_GetPoiPZList(NURO_SEARCH_TYPE type, nuWORD nMax, nuVOID* pBuffer, nuUINT nMaxLen);
SEARCHNEW_API nuUINT LibSH_GetPoiPZTotal();

SEARCHNEW_API nuBOOL LibSH_SetPoiPZZhuyin(nuWORD zhuyin);
SEARCHNEW_API nuBOOL LibSH_SetPoiPZ(nuUINT nResIdx);

SEARCHNEW_API nuBOOL LibSH_SetPoiKeyNameP(nuWCHAR *pName, nuBOOL bFuzzy);

/**
* @brief  �������������
* @param pBuffer ���ֻ���ռ�
* @param nMaxLen �ռ䳤��
*/
SEARCHNEW_API nuUINT LibSH_GetPoiCarFacAll(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ��������POI����������������
* @param nResIdx ���� LibSH_GetPoiCarFacAll
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiCarFac(nuUINT nResIdx);
/**
* @brief  �������SPI����
* @param pBuffer ���ֻ���ռ�
* @param nMaxLen �ռ䳤��
*/
SEARCHNEW_API nuUINT LibSH_GetPoiSPTypeAll(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ��������POI��SPI����
* @param nResIdx ���� LibSH_GetPoiSPTypeAll
*/
SEARCHNEW_API nuBOOL LibSH_SetPoiSPType(nuUINT nResIdx);
/**
* @brief  �����Ѽ�
* @param pHeadWords ǰ���ּ�
* @param pBuffer ����ռ�
* @nMaxWords �ռ���Ա����nuWCHAR��
*/
SEARCHNEW_API nuUINT LibSH_CollectNextWordAll(nuWORD* pHeadWords, 
                                             nuWORD *pBuffer, nuUINT nMaxWords);
/**
* @brief  ��õ�ǰ���õ�ͼ�µ�city��������
*/
SEARCHNEW_API nuUINT LibSH_GetCityTotal();
/**
* @brief  ��õ�ǰ���õ�ͼ-city�µ�town��������
*/
SEARCHNEW_API nuUINT LibSH_GetTownTotal();
/**
* @brief  ��÷�������������POI����
*/
SEARCHNEW_API nuUINT LibSH_GetPoiTotal();

SEARCHNEW_API nuUINT LibSH_GetPoiCount(nuUINT);//prosper

SEARCHNEW_API nuUINT LibSH_GetPoiTotal_Word(nuUINT word);//prosper
/**
* @brief  ��õ�ǰ���õ�ͼ�µ�TP1��������
*/
SEARCHNEW_API nuUINT LibSH_GetTP1Total();
/**
* @brief  ��÷�������������������������
*/
SEARCHNEW_API nuUINT LibSH_GetRoadSZTotal();
/**
* @brief  ��÷������������ĵ�·���� \n
*       ʹ������·ģʽʱ�� LibSH_GetRoadTotal_MR
*/
SEARCHNEW_API nuUINT LibSH_GetRoadTotal();
/**
* @brief  ��÷������������ĵ�·�Ľ���·������ 
*/
SEARCHNEW_API nuUINT LibSH_GetRoadCrossTotal();
/**
* @brief  ������еĵ�ͼ����
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT LibSH_GetMapNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ����趨�ĵ�ͼ��city����
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT LibSH_GetCityNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ����趨�ĵ�ͼ-city��town����
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT LibSH_GetTownNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ����趨�ĵ�ͼ��poi-����1������
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT  LibSH_GetPoiTP1All(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ����趨�ĵ�ͼ-TP1��poi-����2������
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT  LibSH_GetPoiTP2All(nuVOID* pBuffer, nuUINT nMaxLen);
/**
* @brief  ��÷�������������POI���
* @param st ��ȡ����
* @param nMaxPoi ��෵������
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT  LibSH_GetPoiList(NURO_SEARCH_TYPE st, nuWORD nMaxPoi, 
                                    nuVOID* pBuffer, nuUINT nMaxLen);
/**
* @brief  ���POI�ĸ�����Ϣ
* @param nPoiListIdx ���� LibSH_GetPoiList
* @param pPaInfo ����SEARCH_PA_INFO���ڴ�
* @param bRealIdx nPoiListIdx�Ƿ�Ϊ�ڲ�����ֵ
*/
SEARCHNEW_API nuBOOL LibSH_GetPoiMoreInfo(nuUINT nPoiListIdx, 
                                        SEARCH_PA_INFO *pPaInfo, nuBOOL bRealIdx);
/**
* @brief  ���POI��������Ϣ
* @param nPoiListIdx ���� LibSH_GetPoiList
* @param pos ����pos���ڴ�
* @param bRealIdx nPoiListIdx�Ƿ�Ϊ�ڲ�����ֵ
*/
SEARCHNEW_API nuBOOL LibSH_GetPoiPos(nuUINT nPoiListIdx, NUROPOINT* pos, nuBOOL bRealIdx);
/**
* @brief  ���POI��city����
* @param nResIdx ���� LibSH_GetPoiList
* @param pBuffer �������Ƶ��ڴ�
* @param nMaxLen �ڴ泤��
* @param bRealIdx nPoiListIdx�Ƿ�Ϊ�ڲ�����ֵ
*/
SEARCHNEW_API nuBOOL LibSH_GetPoiCityName(nuUINT nResIdx, nuWORD *pBuffer, 
                                        nuUINT nMaxLen, nuBOOL bRealIdx);

SEARCHNEW_API nuLONG LibSH_GetPoiCityID(nuUINT nResIdx, nuBOOL bRealIdx); // Added by Damon 20100309

/**
* @brief  ���POI��town����
* @param nResIdx ���� LibSH_GetPoiList
* @param pBuffer �������Ƶ��ڴ�
* @param nMaxLen �ڴ泤��
* @param bRealIdx nPoiListIdx�Ƿ�Ϊ�ڲ�����ֵ
*/
SEARCHNEW_API nuBOOL LibSH_GetPoiTownName(nuUINT nResIdx, nuWORD *pBuffer, 
                                        nuUINT nMaxLen, nuBOOL bRealIdx);
/**
* @brief  ͨ���绰��ȷ����POI
* @param pPhone �绰��Ϣ
* @param pInfo ����SEARCH_POIINFO���ڴ�
*/
SEARCHNEW_API nuBOOL LibSH_GetPoiByPhone(const nuWCHAR *pPhone, SEARCH_POIINFO *pInfo);
/**
* @brief  ��÷��������ĵ�·����
* @param type ��ȡ����
* @param nMax ��෵������
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT  LibSH_GetRoadSZList(NURO_SEARCH_TYPE type, nuWORD nMax, 
                                       nuVOID* pBuffer, nuUINT nMaxLen);
/**
* @brief  ��÷��������ĵ�·���
* @param type ��ȡ����
* @param nMax ��෵������
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT  LibSH_GetRoadNameList(NURO_SEARCH_TYPE type, nuWORD nMax, 
                                         nuVOID* pBuffer, nuUINT nMaxLen);
/**
* @brief  ��÷��������ĵ�··�ڽ�� ���� LibSH_SetRoadName
* @param type ��ȡ����
* @param nMax ��෵������
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT  LibSH_GetRoadCrossList(NURO_SEARCH_TYPE type, nuWORD nMax, 
                                          nuVOID* pBuffer, nuUINT nMaxLen);
/**
* @brief  ���ָ����·�����ƺ����� ���� LibSH_SetRoadName
*/
SEARCHNEW_API nuUINT LibSH_GetRoadDoorTotal();
/**
* @brief  ���ָ����·�����ƺ���Ϣ ���� LibSH_SetRoadName
* @param pBuffer ���ֽ�����ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadDoorInfo(nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ��ý���·�ڵ�����
* @param nResIdx ����LibSH_GetRoadCrossList
* @param pos ����������
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadCrossPos(nuUINT nResIdx, NUROPOINT* pos);
/**
* @brief  ��ý���·�ڵ�town���� 
* @param nResIdx ����LibSH_GetRoadCrossList
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadCrossTownName(nuUINT nResIdx, nuWORD *pBuffer, 
                                              nuUINT nMaxLen);
/**
* @brief  ��ý���·�ڵ�city����
* @param nResIdx ����LibSH_GetRoadCrossList
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadCrossCityName(nuUINT nResIdx, nuWORD *pBuffer, 
                                              nuUINT nMaxLen);
/**
* @brief  ���ָ����·��������Ϣ
* @param pos ���ֽ�����ڴ�
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadPos(NUROPOINT* pos);
/**
* @brief  ���ָ����·��town���� ���� LibSH_SetRoadName
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadTownName(nuWORD *pBuffer, nuUINT nMaxLen);
/**
* @brief  ���ָ����·��city���� ���� LibSH_SetRoadName
* @param pBuffer �������ֵ��ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuBOOL LibSH_GetRoadCityName(nuWORD *pBuffer, nuUINT nMaxLen);
/**
* @brief  ��÷������������ĵ�·����-ʹ������·ģʽ
*/
SEARCHNEW_API nuUINT LibSH_GetRoadTotal_MR();
/**
* @brief  ���ָ������·���ӵ�·����
* @param nMaxinRoadIdx ���� LibSH_GetRoadNameList_MR�Ȼ�ȡ������·namelist
* @param bRealIdx nMaxinRoadIdx�Ƿ�Ϊ�ڲ�������
*/
SEARCHNEW_API nuUINT LibSH_GetChildRoadTotal_MR(nuUINT nMainRoadIdx, nuBOOL bRealIdx);
/**
* @brief  ��÷��������ĵ�·���
* @param type ��ȡ����
* @param nMax ��෵������
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT LibSH_GetRoadNameList_MR(NURO_SEARCH_TYPE type, nuWORD nMax, 
                                           nuVOID* pBuffer, nuUINT nMaxLen);
/**
* @brief  ���ָ������·���ӵ�·
* @param nMainRoadIdx ���� LibSH_GetRoadNameList_MR�Ȼ�ȡ������·namelist
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
* @param bRealIdx nMaxinRoadIdx�Ƿ�Ϊ�ڲ�������
*/
SEARCHNEW_API nuINT LibSH_GetRoadNameALL_MR(nuUINT nMainRoadIdx, nuVOID* pBuffer, 
                                          nuUINT nMaxLen, nuBOOL bRealIdx);
/**
* @brief  ���õ�·��������- Ϊ��һ����ȡ��·��Ϣ��ǰ�᡾��ȡ����·�ڵȡ�
* @param nMainRoadIdx ��·���� \n
*       ������ȡ����·���Ĳ�����LibSH_GetRoadNameList_MR�ȡ�
* @param nRoadIdx �ӵ�·���� \n
*       ������ȡ�ӵ�·���Ĳ�����LibSH_GetRoadNameALL_MR�ȡ�
* @param bRealIdx �Ƿ���ʵ����  \n
*       ��Ϊtrue����nResIdx�������� Я���˵�·���ڲ�����е���ʵ���� ����LibSH_GetFilterResAll��
*/
SEARCHNEW_API nuBOOL LibSH_SetRoadName_MR(nuUINT nMainRoadIdx, nuUINT nRoadIdx, nuBOOL bRealIdx);

/**
* @brief  ��ȡ�����ֹ��˽��
* @param pKey ���ֹؼ���
* @param pBuffer ���������ڴ�
* @param nMaxLen �ڴ泤��
*/
SEARCHNEW_API nuINT   LibSH_GetFilterResAll(const nuWCHAR *pKey, nuVOID *pBuffer, nuUINT nMaxLen);
/**
* @brief  ����SKB����
*   ����������SEARCH ROAD/POI��ʹ�� �����SEARCH ROAD/POI�����е��������
*/
SEARCHNEW_API nuBOOL  LibSH_StartSKBSearch(nuUINT nType);
/**
* @brief  ��ֹSKB����
*   ���SKB�������
*/
SEARCHNEW_API nuVOID  LibSH_StopSKBSearch();
/**
* @brief �����ƴ����ѯ�б�
*   �ڴ������road�������������ǰ CT֮��
* @param keyStr ����ƴ���б�
* @param pBuffer ��ѯ����б�
* @param nMaxLen pBuffer����
* @param resCount ����漰�ĵ�·����
* @return ��õ�ƴ������
*/
SEARCHNEW_API nuINT   LibSH_GetSKBAll(nuCHAR* keyStr, nuCHAR* pBuffer, nuINT nMaxLen, nuINT* resCount);

SEARCHNEW_API nuUINT LibSH_SHDYStart();
SEARCHNEW_API nuUINT LibSH_SHDYStop();
SEARCHNEW_API nuUINT LibSH_SHDYSetRegion(nuBYTE nSetMode, nuDWORD nData);
SEARCHNEW_API nuUINT LibSH_SHDYSetDanyin(nuWCHAR *pWsDy, nuBYTE nWsNum);
SEARCHNEW_API nuUINT LibSH_SHDYGetHead(PDYCOMMONFORUI pDyHead);
SEARCHNEW_API nuUINT LibSH_SHDYGetPageData(PDYDATAFORUI pDyDataForUI, nuDWORD nItemIdx);
SEARCHNEW_API nuUINT LibSH_SHDYGetPageStroke(PDYDATAFORUI pDyDataForUI, nuBYTE nStroke);
SEARCHNEW_API nuUINT LibSH_SHDYGetOneDetail(PDYDETAILFORUI pDyDetailForUI, nuDWORD nIdx);
SEARCHNEW_API nuUINT LibSH_SHDYCityTownName(PDYCITYTOWNNAME pDyCTname, nuLONG nCityID);
SEARCHNEW_API nuUINT LibSH_SHDYSetSearchMode(nuINT nMode);

//@Prosper 2012.12
SEARCHNEW_API nuUINT LibSH_SHDYGetWordData(PDYWORDFORUI pDyDataForUI);
SEARCHNEW_API nuUINT LibSH_SHDYSetDanyinKeyname(nuWCHAR *pWsDy, nuBYTE nWsNum);
SEARCHNEW_API nuUINT LibSH_SHDYGetPageData_WORD(PDYDATAFORUI pDyDataForUI, nuDWORD nItemIdx);

SEARCHNEW_API nuUINT LibSH_SHDYSetKey(nuWCHAR *pWsDy, nuBYTE nWsNum);

//@zhikun 2009.07.13
SEARCHNEW_API nuUINT LibSH_ShBeginZ(nuUINT nType);
SEARCHNEW_API nuUINT LibSH_ShEndZ();
//@for search by the pinyin file 
/*
SEARCHNEW_API nuUINT LibSH_PYSetModeZ(nuUINT nMode);
SEARCHNEW_API nuUINT LibSH_PYSetRegionZ(nuBYTE nSetMode, nuDWORD nData);
SEARCHNEW_API nuUINT LibSH_PYSetStringZ(nuCHAR *pBuff, nuWORD nBuffLen);
SEARCHNEW_API nuUINT LibSH_PYGetHeadZ(PSH_HEADER_FORUI pShHeader);
SEARCHNEW_API nuUINT LibSH_PYGetPageDataZ(PSH_PAGE_FORUI pPageData, nuDWORD nItemIdx);
SEARCHNEW_API nuUINT LibSH_PYGetPagePinyinZ(PSH_PAGE_FORUI pPageData, nuBYTE nPinyin);
SEARCHNEW_API nuUINT LibSH_PYGetOneDetailZ(PSH_DETAIL_FORUI pOneDetail, nuDWORD nIdx);
SEARCHNEW_API nuUINT LibSH_PYCityTownNameZ(PSH_CITYTOWN_FORUI pCityTown);
*/
//@for the special door numbers. @zhikun 2009.07.27
SEARCHNEW_API nuUINT LibSH_ShSetModeZ(nuUINT nShMode);
SEARCHNEW_API nuUINT LibSH_ShSetInput(nuUINT nInputType);
SEARCHNEW_API nuUINT LibSH_ShSetRegionZ(nuBYTE nSetMode, nuDWORD nData);
SEARCHNEW_API nuUINT LibSH_ShSetStringZ(nuCHAR *pBuff, nuWORD nBuffLen);
SEARCHNEW_API nuUINT LibSH_ShGetHeadZ(PSH_HEADER_FORUI pShHeader);
SEARCHNEW_API nuUINT LibSH_ShGetPageDataZ(PSH_PAGE_FORUI pPageData, nuDWORD nItemIdx);
SEARCHNEW_API nuUINT LibSH_ShGetPagePinyinZ(PSH_PAGE_FORUI pPageData, nuBYTE nPinyin);
SEARCHNEW_API nuUINT LibSH_ShGetOneDetailZ(PSH_DETAIL_FORUI pOneDetail, nuDWORD nIdx);
SEARCHNEW_API nuUINT LibSH_ShCityTownNameZ(PSH_CITYTOWN_FORUI pCityTown);
SEARCHNEW_API nuUINT LibSH_ShGetRoadDetailZ(PSH_ROAD_DETAIL pOneRoad, nuDWORD nIdx);
SEARCHNEW_API nuUINT LibSH_ShGetDrNumCoorZ(nuDWORD nIdx, nuDWORD nDoorNum, nuroPOINT* point);
SEARCHNEW_API nuINT  LibSH_ShGetList(nuWORD& nMax,nuVOID* pBuffer, nuUINT nMaxLen);
SEARCHNEW_API nuINT  LibSH_ShGetNextWords(nuVOID* pRoadBuf, const nuUINT RoadBufLen,nuVOID* pWordBuf,const nuUINT WordLen,nuUINT& n_iCount,nuVOID *wKeyWord, const nuUINT candylen, const nuBOOL ReSort);
SEARCHNEW_API nuUINT LibSH_ShGetWordData(PDYWORDFORUI pDyData);
#ifndef VALUE_EMGRT
SEARCHNEW_API nuBOOL LibSH_ShGetDoorInfo(SH_ROAD_DETAIL &data);
SEARCHNEW_API nuINT LibSH_ShGetDoorInfoData(nuVOID* pBuffer);
#endif 

SEARCHNEW_API nuBOOL LibSH_LDCreateDataFile(nuTCHAR *pFileName
                                          , nuUINT nMax, nuUINT nEachRecordLen, nuINT mode);
SEARCHNEW_API nuBOOL LibSH_LDOpenFile(nuTCHAR *pFileName);
SEARCHNEW_API nuVOID LibSH_LDCloseFile();
SEARCHNEW_API nuBOOL LibSH_LDGetFileHeader(LOGDATAFILEHEADER *fileHeader);
SEARCHNEW_API nuBOOL LibSH_LDAddRecord(nuVOID *pBuffer, nuUINT nLen);
SEARCHNEW_API nuVOID LibSH_LDDelRecord(nuUINT idx);
SEARCHNEW_API nuVOID LibSH_LDClearRecord();
SEARCHNEW_API nuUINT LibSH_LDGetRecord(nuUINT sIdx, nuUINT nMax
                                       , nuVOID *pBuffer, nuUINT nBufferLen);

SEARCHNEW_API nuUINT LibSH_GetPoiNearDis(nuUINT nResIdx, 
										 nuBOOL   bRealIdx);

SEARCHNEW_API nuINT LibSH_GetRoadTownID();

/*
	//	Prosper Test

	SEARCHNEW_API nuBOOL LibSH_VoiceRoadSearch();
	SEARCHNEW_API nuBOOL LibSH_VoicePoiSearch();

*/

	
SEARCHNEW_API nuBOOL LibSH_VoiceRoadName(VOICEROADFORUI data,nuVOID *wChangeName,nuVOID *wCutName,nuroPOINT &point);

SEARCHNEW_API nuBOOL LibSH_VoicePoiSetMap(nuINT nIdx);
SEARCHNEW_API nuBOOL LibSH_VoicePoiPosName(nuVOID* pCityName,nuVOID* pTownName, nuDWORD nIdx);
SEARCHNEW_API nuBOOL LibSH_VoicePoiKeySearch(PDYDETAILFORUI pDyDetailForUI, nuDWORD nIdx);
SEARCHNEW_API nuBOOL LibSH_VoicePoiEnd();

SEARCHNEW_API nuBOOL LibSH_SHSetNoName(nuBOOL bRes);

//Prosper ADD SKB ,20130103 
SEARCHNEW_API nuBOOL LibSH_GetRoadSKB(nuVOID* pSKBBuf, nuUINT& WordCont);
SEARCHNEW_API nuBOOL LibSH_GetPoiSKB(nuVOID* pSKBBuf, nuUINT& WordCont);

SEARCHNEW_API nuBOOL LibSH_GetRoadWordData(nuINT &nTotal,nuVOID* pBuffer, nuUINT nMaxLen);
SEARCHNEW_API nuUINT LibSH_SHDYSetDanyin2(nuWCHAR *pWsDy, nuBYTE nWsNum);
SEARCHNEW_API nuBOOL LibSH_SetRoadKeyDanyin2(nuWORD *pKeyWord);
SEARCHNEW_API nuBOOL LibSH_SetPoiKeyDanyin2(nuWCHAR *pDanyin,nuBOOL bComplete);

SEARCHNEW_API nuINT LibSH_GetDYPoiTotal();
#ifdef ZENRIN
SEARCHNEW_API nuINT LibSH_GetDYDataCOUNT();
#endif
SEARCHNEW_API nuBOOL LibSH_NEWSEARCH_SDK(PCALL_BACK_PARAM pParam);

#endif
SEARCHNEW_API nuINT   LibSH_GetNEXTAll(nuVOID* pkeyStr, nuUINT& WordCont);
SEARCHNEW_API nuUINT LibSH_SHNewDYStart();
SEARCHNEW_API nuUINT LibSH_SHNewDYStop();
SEARCHNEW_API nuUINT LibSH_SHNewDYSetSearchMode(nuINT nMode);
SEARCHNEW_API nuUINT LibSH_SHNewDYSetRegion(nuBYTE nSetMode, nuDWORD nData);

SEARCHNEW_API nuUINT LibSH_SHNewDYSetDanyin(nuWCHAR *pWsDy, nuBYTE nWsNum);
SEARCHNEW_API nuUINT LibSH_SHNewDYSetDanyin2(nuWCHAR *pWsDy, nuBYTE nWsNum);
SEARCHNEW_API nuUINT LibSH_SHNewDYGetHead(PDYCOMMONFORUI pDyHead);
SEARCHNEW_API nuUINT LibSH_SHNewDYGetWordData(PDYWORDFORUI pDyDataForUI);
SEARCHNEW_API nuUINT LibSH_SHNewDYSetDanyinKeyname(nuWCHAR *pWsDy, nuBYTE nWsNum);
SEARCHNEW_API nuUINT LibSH_SHNewDYSetKey(nuWCHAR *pWsDy, nuBYTE nWsNum,nuBOOL);
SEARCHNEW_API nuUINT LibSH_SHNewDYGetPageData_WORD(PDYDATAFORUI pDyDataForUI, nuDWORD nItemIdx);
SEARCHNEW_API nuINT LibSH_GetNewDYDataCOUNT();
SEARCHNEW_API nuINT LibSH_GetNewDYPoiTotal();
SEARCHNEW_API nuUINT LibSH_SHNewDYGetOneDetail(PNDYDETAILFORUI pDyDetailForUI, nuDWORD nIdx);
SEARCHNEW_API nuBOOL LibSH_GetNewDYGetALLData(nuPVOID buffer,nuINT &nCount);
SEARCHNEW_API nuUINT LibSH_SHNewDYGetPoiTotal();
 SEARCHNEW_API nuINT   LibSH_GetNEXTAll(nuVOID* pkeyStr, nuUINT& WordCont);
SEARCHNEW_API nuINT LibSH_SetAreaCenterPos(nuroPOINT pos);

