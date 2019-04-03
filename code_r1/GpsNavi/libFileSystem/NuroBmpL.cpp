
#include "NuroBmpL.h"

CNuroBmpL::CNuroBmpL()
{

}

CNuroBmpL::~CNuroBmpL()
{

}

/*����ȷ��ÿ�δ��ļ��ж����ĳ���С�ڻ����1024*/
#ifndef _USE_DDB_BITMAP
nuWORD tlbytesread(nuBYTE *des,nuSIZE n=1, nuSIZE item=0,nuFILE *fp=NULL)
{
	nuWORD length=item*n,clength=0,templength=0;
	if(length>1024)
	{
		
		while(length>1024)
		{
			if((templength=nuFread(des,1,1024,fp))!=1024)
			{
				clength=clength+templength;
				return clength;
			};
			clength=clength+templength;
			des=des+1024;
			length=length-1024;
		}
		templength=nuFread(des,1,length,fp);
		clength=clength+templength;
		return clength;
	}
	else
	{
		templength=nuFread(des,n,item,fp);
		return templength;
	}
}

/*�����Ĺ����ǽ�nmp�ļ�������������Ϣ�����ڴ���*/
const nuBOOL COLOR_L=3;
nuBOOL CNuroBmpL::ReadNuroBmp(const nuTCHAR *pszFilename, PNURO_BMP temp)
{
	NURO_BMP bytemp = {0};
	nuFILE *fp = NULL;
	if(!(fp=(nuFILE*)nuTfopen(pszFilename, NURO_FS_RB)))
	{	
		return nuFALSE;
	}
	if(nuFread(&bytemp,1, sizeof(bytemp),fp) != sizeof(bytemp))
	{
		return nuFALSE;
	}
	temp->bmpBitCount = bytemp.bmpBitCount;
	temp->bmpReserve = bytemp.bmpReserve;
	temp->bmpType = bytemp.bmpType;
	temp->bmpTransfColor = bytemp.bmpTransfColor;
	temp->bmpWidth = bytemp.bmpWidth;
	temp->bmpHeight = bytemp.bmpHeight;
	temp->bmpBuffLen = bytemp.bmpBuffLen;
	temp->pBmpBuff = new nuBYTE[temp->bmpBuffLen];
	if(tlbytesread(temp->pBmpBuff,sizeof(nuBYTE),temp->bmpBuffLen,fp)!=temp->bmpBuffLen)
	{
		delete []temp->pBmpBuff;
		temp->pBmpBuff=NULL;
		return nuFALSE;
	}
	nuFclose(fp);
	return nuTRUE;
}
/*������nmp�ļ������ڴ���*/
nuBOOL CNuroBmpL::FillNuroBmp(const nuTCHAR *pszFilename, PNURO_BMP temp)
{
	NURO_BMP bytemp = {0};
	nuFILE *fp = NULL;
	if(!(fp=(nuFILE*)nuTfopen(pszFilename, NURO_FS_RB)))
	{	
		return nuFALSE;
	}
	if(nuFread(&bytemp,1,sizeof(bytemp),fp) != sizeof(bytemp))
	{
		return nuFALSE;
	}
	temp->bmpBitCount = bytemp.bmpBitCount;
	temp->bmpReserve = bytemp.bmpReserve;
	temp->bmpType = bytemp.bmpType;
	temp->bmpTransfColor = bytemp.bmpTransfColor;
	nuWORD i = 0;
	nuBYTE *des = NULL;
	nuBYTE *src = NULL;
	bytemp.pBmpBuff = new nuBYTE[bytemp.bmpBuffLen];
	if( (nuFread(bytemp.pBmpBuff, 1, bytemp.bmpBuffLen, fp)) != bytemp.bmpBuffLen )
	{
		return nuFALSE;
	}
	/*��ȡ��ɫ��Ϣʱһ��Ҫע����ɫ��Ϣ���ݴ洢��ʽ�ǵ�ת˳��洢��*/
	nuWORD tempx=0,tempdx=0;
	//�ֱ��ʾ�û�ÿ�е��ֽڳ��Ⱥ�ʵ��ÿ�е��Լ�����
	if((temp->bmpWidth*COLOR_L)%4!=0)
	{
		tempx=temp->bmpWidth*COLOR_L+4-(temp->bmpWidth*COLOR_L)%4;
		//�������ʵ��ÿ�ж��ٸ��ֽ�
	}
	else
	{
		tempx=temp->bmpWidth*COLOR_L;
	}
	if((bytemp.bmpWidth*COLOR_L)%4!=0)
	{
		tempdx=bytemp.bmpWidth*COLOR_L+4-(bytemp.bmpWidth*COLOR_L)%4;
	}
	else
	{
		tempdx=bytemp.bmpWidth*COLOR_L;
	}
	//��һ�����
	if((bytemp.bmpWidth>temp->bmpWidth)&&(bytemp.bmpHeight>temp->bmpHeight))
	{

		for(i=0;i<temp->bmpHeight;i++)
		{
			des=temp->pBmpBuff+i*tempx;
			src=bytemp.pBmpBuff+i*tempdx;
			nuMemcpy(des,src,temp->bmpWidth*COLOR_L);	
		}

	}
	//�ڶ�������û�����Ŀ�С��ʵ�ʵģ��û��ĸߴ���ʵ�ʵ�
	else if(bytemp.bmpWidth>temp->bmpWidth)
	{
		for(i=0;i<bytemp.bmpHeight;i++)
		{
			des=temp->pBmpBuff+i*tempx;
			src=bytemp.pBmpBuff+i*tempdx;
			nuMemcpy(des,src,temp->bmpWidth*COLOR_L);
		}
			
	}
	//����������û��ĸ�С��ʵ�ʵģ����û��Ŀ����ʵ�ʵ�
	else if(bytemp.bmpHeight>temp->bmpHeight)
	{
		
		for(i=0;i<temp->bmpHeight;i++)
		{
			des=temp->pBmpBuff+i*tempx;
			src=bytemp.pBmpBuff+i*tempdx;
			nuMemcpy(des,src,bytemp.bmpWidth*COLOR_L);
		}
	}
	else
	{	
		for(i=0;i<bytemp.bmpHeight;i++)
		{
			des=des=temp->pBmpBuff+i*tempx;
			src=bytemp.pBmpBuff+i*tempdx;
			nuMemcpy(des,src,bytemp.bmpWidth*COLOR_L);
		}
	}
	delete []bytemp.pBmpBuff;
	bytemp.pBmpBuff=NULL;
	nuFclose(fp);
	return nuTRUE;
}
#endif
