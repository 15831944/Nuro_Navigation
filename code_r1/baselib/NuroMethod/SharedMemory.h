// SharedMemory.h: interface for the CSharedMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAREDMEMORY_H__36C3E779_270F_4259_9F36_710E5AD810F3__INCLUDED_)
#define AFX_SHAREDMEMORY_H__36C3E779_270F_4259_9F36_710E5AD810F3__INCLUDED_

#include "../NuroDefine.h"
#define  SHARED_MEM_SIZE   10*1024

typedef enum
{
	LX_OK                   = 0, // ��������
	LX_SHAREDMEMORY_EXISTS  = 1, // �����ڴ��Ѿ�����
	LX_INVALID_SHAREDMEMORY = 2, // �����ڴ���󷵻�
	LX_INVALID_SIZE         = 3  // �����ڴ��С����
}LX_RETURN_VALUE;

typedef struct tagHEADERMEM
{	
	long nNowSize;  //��ǰ��Ŀ
	long nTotalSize;//�ܵ��ڴ���
    long bMutex;
	long bFirst;
}HEADERMEM, *PHEADERMEM;

class CSharedMemory  
{
public:
	bool bOutMutex();
	bool bInMutex();
	long GetTotalSize();
	bool bSetFirst();
	long GetShareStruNum();
	int WriteShareMem(void *pDate, long nSize,long nIndex);
	CSharedMemory();
	virtual ~CSharedMemory();
	/**/
	int GetShareMem(void *pBuff, long nSize, long nIndex);
	bool AddSharedMemory( long nSize ); // nSize == 0 ���
	int ReleaseSharedMemory();
	int CreateSharedMemory( long nPerStruSize );
	
private:
	//HANDLE m_hMutex;
	nuHANDLE m_hFileMapping;
	//HEADERMEM m_struHeader;
	//long m_nTotalSize;
	//long m_nUseSize;
	void* m_pMemStartAddr;

};

#endif // !defined(AFX_SHAREDMEMORY_H__36C3E779_270F_4259_9F36_710E5AD810F3__INCLUDED_)
