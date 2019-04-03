/************************************************************************
* @file SearchBaseZ.h
* 
* 
* ����SearchBaseZ����	                                                             
************************************************************************/
#if !defined(AFX_SEARCHBASEZ_H__B7486302_1B72_419A_9E3E_466974FD0053__INCLUDED_)
#define AFX_SEARCHBASEZ_H__B7486302_1B72_419A_9E3E_466974FD0053__INCLUDED_

#include "NuroModuleApiStruct.h"
#include "nuSearchDefine.h"
#include "NuroClasses.h"

#define _USE_SEARCH_ROAD_ 1           ///�����·����ģ�����
#define _SEARCH_ROAD_MAINROADMODE_ 1  ///��������·ģʽ��PANA���ã���ȡ��·ʱʹ�ô�MR��׺��
#define _USE_PANA_MODE_ 1             ///����pana�ر������������������в�ͬ�Ĵ���

#define _SEARCH_ROAD_FJUDGE_ENDWORD_ '@'  ///fuzzy judge end word
#define _SEARCH_ROAD_FJUDGE_ENDWORD1_ '#'  //added by ouyang 20100120 һ����·������ֻ����Ū

/**
* @brief Search����
*/
class CSearchBaseZ  
{
public:
    CSearchBaseZ();
    virtual ~CSearchBaseZ();
    
    /**
    * @brief  ��ʼ��������ģ��
    *
    * @param pApiAddr ������ģ��API
    * @return ����ֵ��ʾ�Ƿ��ʼ���ɹ� \n
    *	true: �ɹ�\n
    *	false: ʧ��\n
    */
    static nuBOOL InitData(PAPISTRUCTADDR pApiAddr);
    
    /**
    * 
    */
    static nuVOID FreeData();
    
    /**
    * @brief ��ȡ����״̬
    *
    * @return �Ƿ�����\n
    *	true: ��������\n 
    *	false: δ����
    */
    nuBOOL IsRun();
    
    /**
    * @brief �������п���ת��
    *
    * @param type ��������\n
    *	NURO_SEARCH_NEXT���Ƿ���NEXT�ᱻת��ΪNURO_SEARCH_NEWʵ��\n
    *	NURO_SEARCH_RELOAD��buffer������С�᷵��false\n
    *	NURO_SEARCH_PRE���������buffer��nMax���ƴ��ڣ�\n
    *	...
    * @param nMax ��������޶�
    * @param lastPos �����б��λ��
    * @param lastCount ����������ȡ������
    * @retval pTranResTagPos ���ض���������ʼλ��
    * @retval pTranResMaxNum ���������������
    * @return ת���Ƿ�ɹ�
    */
    static nuBOOL TranslateSS(const NURO_SEARCH_TYPE &type, 
        const nuUINT &nMax, 
        const nuUINT &lastPos, 
        const nuUINT &lastCount, 
        nuUINT *pTranResTagPos, 
        nuUINT *pTranResMaxNum);
    
    /** 
    * @brief �����������
    * 
    * @param pBuffer ָ�򻺴����
    * @param max ���������Ԫ������
    * @param type ��������\n
    *	1:city\n
    *	2:stroke+ name\n
    *	3:nameaddr\n
    *	4:city+ town+ stroke+ name
    * @return �����Ƿ�ɹ�\n
    *	true:�ɹ�\n
    *	false:ʧ��
    */
    static nuBOOL QueueBUffer(SEARCH_BUFFER *pBuffer, nuUINT max, nuBYTE type);
    static nuBOOL QueueBUfferRoad(SEARCH_BUFFER_ROAD *pBuffer, nuUINT max, nuBYTE type);
    
protected:
    
    nuBOOL	m_bRun; ///����״̬
    
protected:
    static NURO_SEARCHINFO m_searchInfo;  ///������Ϣ
    static PFILESYSAPI	m_pFsApi;         ///�ļ�ϵͳģ��
    static PMEMMGRAPI_SH	m_pMmApi;           ///�ڴ����ģ��
    static nuUINT	m_nCityTotal;           ///�����ͼ��city����
    static nuUINT	m_nCBInfoLen;           ///�����ͼ��CBFILE��Ϣ����
    static nuUINT	m_nStrokeLimIdx;        ///�ʻ�����ʱ��������λ	
};

#endif // !defined(AFX_SEARCHBASEZ_H__B7486302_1B72_419A_9E3E_466974FD0053__INCLUDED_)
