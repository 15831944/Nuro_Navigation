// Copyright (c) 2009 Nuro Corp.  All rights reserved.
// $Id: nuro3DModelStruct.h,v 1.9 2010/04/15 01:30:20 zealass Exp $
// $Author: zealass $
// $Date: 2010/04/15 01:30:20 $
// $Locker:  $
// $Revision: 1.9 $
// $Source: /home/nuCode/libRenderModel/nuro3DModelStruct.h,v $
/////////////////////////////////////////////////////////////////////////
#ifndef _NURO_3D_MODEL_STRUCT_20090918_ZK
#define _NURO_3D_MODEL_STRUCT_20090918_ZK
#include "defines.h"
#include "nuDefine.h"

//.3DR file struct
#define _ZK_USE_FIXED_VERTEX
#define _3D_SCALE_SET_                  (0.7f)
#define _ZK_MAX_COUNT_MODEL_LOADEN      (15)
#define _3D_MODEL_SHOW_MAX              _ZK_MAX_COUNT_MODEL_LOADEN

typedef struct tagCOLOR_F
{
	float		fR;
	float		fG;
	float		fB;
}COLOR_F, *PCOLOR_F;

typedef struct tagFILE_3DR_HEADER
{
	nuDWORD	nGroupCount;
	nuDWORD	nDataFormat;
}FILE_3DR_HEADER, *PFILE_3DR_HEADER;
typedef struct tagFILE_3DR_GROUP
{
	nuDWORD				nDataAddr;
	nuDWORD				nVertexCount;
	nuDWORD				nTextureCount;
	nuDWORD				nNormalCount;
	nuDWORD				nFaceCount;
	COLOR_F				fKa;
	COLOR_F				fKd;
	COLOR_F				fKs;
	float				fD;
	float				fNs;
	long				illum;
	long				nBmpAddr;
}FILE_3DR_GROUP, *PFILE_3DR_GROUP;
typedef struct tagFILE_3DR_VERTEX_X
{
#ifdef _ZK_USE_FIXED_VERTEX
	int		vX;
	int		vY;
	int		vZ;
#else
	float	vX;
	float	vY;
	float	vZ;
#endif
}FILE_3DR_VERTEX_X,*PFILE_3DR_VERTEX_X;
typedef struct tagFILE_3DR_TEXTURE_X
{
#ifdef _ZK_USE_FIXED_VERTEX
	int		tX;
	int		tY;
#else
	float	tX;
	float	tY;
#endif
}FILE_3DR_TEXTURE_X, *PFILE_3DR_TEXTURE_X;
typedef struct tagFILE_3DR_NORMAL_X
{
#ifdef _ZK_USE_FIXED_VERTEX
	int		nX;
	int		nY;
	int		nZ;
#else
	float	nX;
	float	nY;
	float	nZ;
#endif
}FILE_3DR_NORMAL_X, *PFILE_3DR_NORMAL_X;
typedef nuWORD		_3DR_FACE_INDEX;
typedef struct tagFILE_3DR_BMP
{
	int		nWidth;
	int		nHeight;
	int		nBitCount;
	int		nBuffLen;
	char*	pColorBuff;
}FILE_3DR_BMP, *PFILE_3DR_BMPE;

//For 3D Models Data
typedef struct tagMODEL_VAR_FROM_OPENGL
{
	nuDWORD				nDataLen;
	nuBYTE*				pDataBuff;//����������Ƭ�б�ķ�ʽ���棬��Demoһ��
	nuUINT				nBmpTexture;
}MODEL_VAR_FROM_OPENGL, *PMODEL_VAR_FROM_OPENGL;
typedef struct tagMODEL_3DMAX_DATA
{
	long	nID;
	long	nX;
	long	nY;

	FILE_3DR_HEADER			stufileHeader;
	PFILE_3DR_GROUP			pstuGroupArray;
	PMODEL_VAR_FROM_OPENGL	pstuVarOpenGLArray;

    long    rX;//��ͼX
    long    rY;//��ͼY
    long    tY;//���Y
    int     height;//��Ļ��
    int     dCenD;//ƫ�ľ���
    float   fSclRef;//������
    float   fZhRef;// ��ͷ��H/Zֵ
    long    lY;//���·���Y
    int     maxHeight;// z �������ֵ;
    long    xmin;
    long    xmax;
    long    ymin;
    long    ymax;
}MODEL_3DMAX_DATA, *PMODEL_3DMAX_DATA;


#endif
