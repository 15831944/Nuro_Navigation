// nuroResource.h: interface for the nuroResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NURORESOURCE_H__2D0C847B_B745_4445_93EB_7688D5E83AEB__INCLUDED_)
#define AFX_NURORESOURCE_H__2D0C847B_B745_4445_93EB_7688D5E83AEB__INCLUDED_

//#include "nuDefine.h"
#include "NuroArchiveInc.h"

#define NURO_BMP_CONTENT_TYPE_UNKNOWN        0UL
#define NURO_BMP_CONTENT_TYPE_565            1UL
#define NURO_BMP_CONTENT_COMPRESS_TYPE_NONE  0UL
#define NURO_BMP_CONTENT_COMPRESS_TYPE_LZMA  1UL

struct NuroBmpContent //16 Bytes
{
	nuUSHORT width;
	nuUSHORT height;
	nuUSHORT bytesperline;
	nuUCHAR  type; //bmp content type
	nuUCHAR  compresstype; //compress type
	nuUINT   compresssize;
	nuUINT   size;
};
struct ALPackHead //48 Bytes
{
	nuCHAR	head[4];
	nuUINT  version;
	nuUINT	total;
	nuUINT  max;
	nuUINT	datapos;
	nuUINT	datasize;
	nuUINT	indexpos;
	nuUINT	indexsize;
	nuCHAR	attr[16];
};

class CResources  
{
public:
	CResources();
	virtual ~CResources();

	nuBOOL Initialize();
	
	static nuBOOL LoadNBC(NURO_BMP* pNuroBmp, const nuTCHAR* filename);
	
	nuUINT	LoadPack(const nuTCHAR* packname);
	nuVOID	UnloadPack();
	
	nuVOID*	FindFile(const nuCHAR* filepath); 
	nuUINT	GetFileLength(nuVOID* file); //
	nuBOOL	LoadFileData(nuVOID* file, nuUCHAR* buffer, nuUINT size); //

	nuBOOL	LoadNuroBMP(NURO_BMP* pNuroBmp, nuVOID* file);
	nuVOID    UnloadNuroBMP(NURO_BMP* pNuroBmp);

//private:
public:
	ALPackHead _packHead;
	nuUCHAR* _packInfo;
	nuTCHAR _packName[256];

	nuUINT cryptTable[0x200];
	nuVOID prepareCryptTable(nuUINT* cryptTable, nuUINT n);
	nuUINT HashString(const nuCHAR *lpszFileName, nuUINT dwCryptIndex);
};

#endif // !defined(AFX_NURORESOURCE_H__2D0C847B_B745_4445_93EB_7688D5E83AEB__INCLUDED_)
