// FileCCD.cpp: implementation of the CFileCCD class.
//
//////////////////////////////////////////////////////////////////////

#include "FileCCD.h"
#include "NuroModuleApiStruct.h"
#include "NuroConstDefined.h"
#include "libFileSystem.h"

extern PMEMMGRAPI	g_pFsMmApi;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CCDBLOCK_SIZE_X						(25000*COORCONSTANT)
#define CCDBLOCK_SIZE_Y						(25000*COORCONSTANT)
#define XCCDBLOCK_COUNT						1440


CFileCCD::CFileCCD()
{
	m_ccdData.nCCDBlockCount	= 0;
}

CFileCCD::~CFileCCD()
{
	Free();
}

nuBOOL CFileCCD::Initialize()
{
	m_ccdData.nCCDBlockCount	= 0;
	return nuTRUE;
}

nuVOID CFileCCD::Free()
{
	for(nuWORD i = 0; i < m_ccdData.nCCDBlockCount; i++)
	{
		RelCCDBlockUsed(&(m_ccdData.pCCDBlockList[i]));
	}
	m_ccdData.nCCDBlockCount = 0;
}


nuPVOID CFileCCD::GetDataCCD(const nuroRECT& rtRange, nuWORD nMapIdx /* = 0 */) //���ᳬ��
{
	nuDWORD pBlockIDUsed[4];
	nuMemset(pBlockIDUsed, 0, sizeof(pBlockIDUsed));
	nuINT nIDUsedIdx = ColCCDBlockIDList(rtRange, pBlockIDUsed);
	if( !nIDUsedIdx )
	{
		return NULL;
	}
	/*test*//*test
	nuTCHAR tsTest[225];
	wsprintf(tsTest, TEXT("ccd1: %d, %d, %d"), nIDUsedIdx, pBlockIDUsed[0], pBlockIDUsed[1]);
	MessageBox(NULL, tsTest, TEXT(""), 0);
	*/
	//
	nuDWORD nCCDBlk = 0;
	nuTCHAR tsFile[NURO_MAX_PATH] = {0};
	nuFILE*	pFile = NULL;
	nuTcscpy(tsFile, nuTEXT(".CCD"));
	if( !LibFS_FindFileWholePath(nMapIdx, tsFile, NURO_MAX_PATH) )
	{
		return NULL;
	}
	pFile = nuTfopen(tsFile, NURO_FS_RB);
	if( pFile == NULL )
	{
		return NULL;
	}
	nuFseek(pFile, 0, NURO_SEEK_SET);
	if( nuFread(&nCCDBlk, 4, 1, pFile) != 1 )//Read CCD blocks
	{
		nuFclose(pFile);
		return NULL;
	}
	/*test*//*test
	nuTCHAR tsTest[25];
	wsprintf(tsTest, TEXT("ccd cound = %d"), nCCDBlk);
	MessageBox(NULL, tsTest, TEXT(""), 0);
	*/
	nuDWORD* pBlockID = new nuDWORD[nCCDBlk];
	if( pBlockID == NULL )
	{
		nuFclose(pFile);
		return NULL;
	}
	if( nuFread(pBlockID, 4, nCCDBlk, pFile) != nCCDBlk )//Read CCD BlockID list
	{ 
		delete []pBlockID;
		pBlockID=NULL;
		nuFclose(pFile);
		return NULL;
	}
	nuWORD nCCDBlkUsed = 0;
	nuBOOL bFindSame =nuFALSE;
	nuDWORD i = 0;
	/*test*//*test
	nuTCHAR tssTest[125];
	wsprintf(tssTest, TEXT("ccd: %d, %d"), pBlockIDUsed[0], pBlockIDUsed[1]);
	MessageBox(NULL, tssTest, TEXT(""), 0);
	*/
	for( i = 0; i < nCCDBlk; i++ )
	{
		for( nuINT j = 0; j < nIDUsedIdx; j++ )
		{
			if( pBlockID[i] == pBlockIDUsed[j] )
			{
				/*test*//*test
				nuTCHAR tsTest[125];
				wsprintf(tsTest, TEXT("ccd cound = %d, %d"), j, pBlockIDUsed[j]);
				MessageBox(NULL, tsTest, TEXT(""), 0);
				*/
				//�������Ҫ���λ�ñ��Ѷ�ȡ����С���ȶ���û���Ѷ�ȡ��CCDBlock��Ҫ������ͬ
				if( nCCDBlkUsed < m_ccdData.nCCDBlockCount )
				{
					bFindSame = nuFALSE;
					nuWORD k;
					for( k = nCCDBlkUsed; k < m_ccdData.nCCDBlockCount; k++ )
					{
						if( m_ccdData.pCCDBlockList[k].nBlockID == pBlockID[i] )
						{
							bFindSame = nuTRUE;
							break;
						}//�Ѷ�ȡ��CCDBlock������������Ҫ��ȡ��һ��CCDBlock
					}
					if( bFindSame )
					{
						if( k != nCCDBlkUsed )
						{
							CCDBLOCK ccdBlock = m_ccdData.pCCDBlockList[nCCDBlkUsed];
							m_ccdData.pCCDBlockList[nCCDBlkUsed] = m_ccdData.pCCDBlockList[k];
							m_ccdData.pCCDBlockList[k] = ccdBlock;
						}//�Ѷ�ȡ��CCDBlock���������Ҫ��ȡ��CCDBlock��ŵ�λ�ò�ͬ������λ�õ�ǰ��
					}
					else
					{
						if( m_ccdData.nCCDBlockCount < MAX_CCD_BLOCK )
						{
							CCDBLOCK ccdBlock = m_ccdData.pCCDBlockList[nCCDBlkUsed];
							m_ccdData.pCCDBlockList[nCCDBlkUsed] = m_ccdData.pCCDBlockList[k];
							m_ccdData.pCCDBlockList[k] = ccdBlock;
							m_ccdData.nCCDBlockCount ++;
						}//CCDBlockList���滹�пգ��ѿյ��Ƶ�ǰ�棬������ȡ
						else
						{
							RelCCDBlockUsed(&m_ccdData.pCCDBlockList[nCCDBlkUsed]);
						}//�и��µ�
					}//һ���µ�CCDBlockҪ��ȡ
				}
				m_ccdData.pCCDBlockList[nCCDBlkUsed].nDwIdx	= 0;
				m_ccdData.pCCDBlockList[nCCDBlkUsed].nBlockID	= pBlockID[i];
				m_ccdData.pCCDBlockList[nCCDBlkUsed].nBlockIdx	= i;
				nCCDBlkUsed ++;
				break;
			}//�ҵ�һ��Ҫ��ȡ��CCDBlock
		}
		if( nCCDBlkUsed == MAX_CCD_BLOCK )
		{
			break;
		}
	}
	for( i = nCCDBlkUsed; i < m_ccdData.nCCDBlockCount; i++ )
	{
		RelCCDBlockUsed(&m_ccdData.pCCDBlockList[i]);
	}//�ͷ�û���õ���CCDBlock
	m_ccdData.nCCDBlockCount = nCCDBlkUsed;
	nuDWORD nAddr;
	for( i = 0; i < m_ccdData.nCCDBlockCount; i++ )
	{
		/*
		if( pBlockID[ m_ccdData.pCCDBlockList[i].nBlockIdx ] == -1 )
		{
			continue;
		}
		*/
		if( m_ccdData.pCCDBlockList[i].ppCCDNodeList != NULL &&
			*m_ccdData.pCCDBlockList[i].ppCCDNodeList != NULL )
		{
			continue;
		}
		if( nuFseek(pFile, 4 + 4*nCCDBlk + 4 * m_ccdData.pCCDBlockList[i].nBlockIdx, NURO_SEEK_SET) != 0 || 
			nuFread(&nAddr, 4, 1, pFile) != 1 ||
			nuFseek(pFile, nAddr, NURO_SEEK_SET) != 0 )
		{
			continue;
		}
		if( nuFread(&m_ccdData.pCCDBlockList[i].nCCDCount, 4, 1, pFile) != 1 )
		{
			continue;
		}
		m_ccdData.pCCDBlockList[i].ppCCDNodeList = (PPCCDNODE)g_pFsMmApi->MM_AllocMem(m_ccdData.pCCDBlockList[i].nCCDCount*sizeof(CCDNODE));
		if( m_ccdData.pCCDBlockList[i].ppCCDNodeList == NULL )
		{
			continue;
		}
		if( nuFread((*m_ccdData.pCCDBlockList[i].ppCCDNodeList), sizeof(CCDNODE), m_ccdData.pCCDBlockList[i].nCCDCount, pFile) != m_ccdData.pCCDBlockList[i].nCCDCount )
		{
			g_pFsMmApi->MM_FreeMem((nuVOID**)m_ccdData.pCCDBlockList[i].ppCCDNodeList);
			m_ccdData.pCCDBlockList[i].ppCCDNodeList = NULL;
			continue;
		}
	}
	delete []pBlockID;
	pBlockID=NULL;
	nuFclose(pFile);
	return &m_ccdData;
}

nuBOOL CFileCCD::RelCCDBlockUsed(PCCDBLOCK pCCDBlock)
{
	if( pCCDBlock != NULL )
	{
		if( pCCDBlock->ppCCDNodeList != NULL )
		{
			g_pFsMmApi->MM_FreeMem((nuVOID**)pCCDBlock->ppCCDNodeList);
			pCCDBlock->ppCCDNodeList	= NULL;
			pCCDBlock->bUsed			= 0;
			pCCDBlock->nBlockID			= 0;
			pCCDBlock->nBlockIdx		= 0;
			pCCDBlock->nCCDCount		= 0;
			pCCDBlock->nDwIdx			= 0;
		}
	}
	return nuTRUE;
}

nuDWORD CFileCCD::nuCCDPointToBlockID(nuLONG x, nuLONG y)
{
	if( y < 0 )
	{
		y = (y + HALF_MAX_LATITUDE) / CCDBLOCK_SIZE_Y;
	}
	else
	{
		y = y/CCDBLOCK_SIZE_Y + HALF_MAX_LATITUDE/CCDBLOCK_SIZE_Y;
	}
	if( x < 0 )
	{
		x = (x + HALF_MAX_LONGITUDE) / CCDBLOCK_SIZE_X;
	}
	else
	{
		x = x / CCDBLOCK_SIZE_X + HALF_MAX_LONGITUDE / CCDBLOCK_SIZE_X;
	}
	return (x + y * XCCDBLOCK_COUNT);
}

nuINT CFileCCD::ColCCDBlockIDList(const nuroRECT &rtRange, nuDWORD *pCCDBlkIDList)
{
	nuDWORD pIDList[4] = {0};
	pIDList[0] = nuCCDPointToBlockID(rtRange.left, rtRange.top);
	pIDList[1] = nuCCDPointToBlockID(rtRange.left, rtRange.bottom);
	pIDList[2] = nuCCDPointToBlockID(rtRange.right, rtRange.top);
	pIDList[3] = nuCCDPointToBlockID(rtRange.right, rtRange.bottom);
	nuINT IDListIdx = 0;
	nuBOOL bSame = nuFALSE;
	for( nuINT i = 0; i < 4; i++ )
	{
		bSame = nuFALSE;
		for(nuINT j = 0; j < IDListIdx; j++)
		{
			if( pIDList[i] == pCCDBlkIDList[j] )
			{
				bSame = nuTRUE;
				break;
			}
		}
		if( bSame )
		{
			continue;
		}
		pCCDBlkIDList[IDListIdx++] = pIDList[i];
	}
	return IDListIdx;
}

nuUINT CFileCCD::GetCCDName(nuWORD nMapIdx, nuLONG nNameAddr, nuWCHAR *pNameBuf, nuWORD nLen)
{
	if( nNameAddr < 0 || pNameBuf == NULL)
	{
		return 0;
	}
	nuTCHAR tsFile[NURO_MAX_PATH] = {0};
	nuFILE*	pFile = NULL;
	nuTcscpy(tsFile, nuTEXT(".CCD"));
	if( !LibFS_FindFileWholePath(nMapIdx, tsFile, NURO_MAX_PATH) )
	{
		return 0;
	}
	pFile = nuTfopen(tsFile, NURO_FS_RB);
	if( pFile == NULL )
	{
		return 0;
	}
	nuBYTE nNameLen;
	if( nuFseek(pFile, nNameAddr, NURO_SEEK_SET) != 0 ||
		nuFread(&nNameLen, 1, 1, pFile) != 1 )
	{
		nuFclose(pFile);
		return 0;
	}
	if( nNameLen > nLen )
	{
		nNameLen = (nuBYTE)(nLen - sizeof(nuWCHAR));
	}
	if( nuFread(pNameBuf, 1, nNameLen, pFile) != nNameLen )
	{
		nNameLen = 0;
	}
	pNameBuf[nNameLen/sizeof(nuWCHAR)] = 0;
	nuFclose(pFile);
	return nNameLen;
}