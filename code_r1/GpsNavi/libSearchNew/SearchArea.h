#if !defined(AFX_SEARCHAREA_H__8B1E23A8_F9DA_4A1A_BB5C_8E326EBDFB73__INCLUDED_)
#define AFX_SEARCHAREA_H__8B1E23A8_F9DA_4A1A_BB5C_8E326EBDFB73__INCLUDED_

#include "SearchBaseZ.h"

class CMapFileCbZ;
class CSearchArea : public CSearchBaseZ  
{
public:
    CSearchArea();
    virtual ~CSearchArea();
    nuBOOL Init();
    nuVOID Free();
    
    nuUINT	LoadCBInfo(nuWORD nMMIdx, nuUINT nMaxLen);
    nuVOID	FreeCBInfo();
    nuUINT	GetCityTotal();
    nuUINT	GetTownTotal();
    nuUINT	GetMapNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuUINT	GetCityNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuUINT	GetTownNameAll(nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL	GetCityNameByID(nuWORD cityID, nuVOID *pBuffer, nuUINT nMaxLen);
    nuBOOL	GetTownNameByID(nuWORD cityID, nuWORD townID, nuVOID *pBuffer, nuUINT nMaxLen);
    /**
    * @brief ���TOWN��BLKINFO ��CB����towninfo��BlockInfoCount��ʼ����
    */
    nuUINT	GetTownBlkInfo(nuWORD cityID, nuWORD townID, nuBYTE *pBuffer, nuUINT nMaxLen);
private:
    /**
    * @brief ���TOWNINFO
    */
    nuBOOL	GetTownInfo(nuBYTE *pCBInfo, nuUINT addr, SEARCH_CB_TOWNINFO *pTI);
    /**
    * @brief ���TOWNINFO�е�cityid
    */
    nuWORD	GetTownInfo_CC(nuBYTE *pCBInfo, nuUINT addr);
    /**
    * @brief ���TOWNINFO�е�townid
    */
    nuWORD	GetTownInfo_TC(nuBYTE *pCBInfo, nuUINT addr);
    /**
    * @brief ����ity����town����m_nFirstTownIdxBuffer��
    */
    nuWORD	SearchTownFirst(nuWORD nCityIdx,
        nuBYTE *pCBInfo, 
        nuUINT nTownCount);
    nuUINT	m_nTownTotal;       ///town����
    nuWORD	m_nCBInfoIdx;       ///�ڴ��־
    nuLONG	m_nST_MapID;        ///load����������mapid
    nuWORD	m_nFirstTownIdxBuffer[NURO_SEARCH_CITYPERMAP_DFT];///ÿ��city����townλ��
};

#endif // !defined(AFX_SEARCHAREA_H__8B1E23A8_F9DA_4A1A_BB5C_8E326EBDFB73__INCLUDED_)
