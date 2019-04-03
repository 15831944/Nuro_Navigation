#ifndef __EJTTS_H__
#define __EJTTS_H__

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef ANDROID	
#include <stdio.h>
#endif
#define TTSAPI 
#define JTTS_EXPORT_C
typedef unsigned char	BYTE;
typedef unsigned long	DWORD;
typedef int				BOOL;
typedef unsigned short  wcode;
typedef unsigned short	WORD;
typedef unsigned int	UINT;
typedef long			LONG;
	
#define JTPATH			0x64
#define TRUE			1
#define FALSE			0
	
	
typedef enum 
{
	ERR_NONE,			//	0
	ERR_ALREADYINIT,	//	1
	ERR_NOTINIT,		//	2 
	ERR_MEMORY,			//	3
	ERR_OPENFILE,		//	4
	ERR_PLAYING,		//	5
	ERR_MORETEXT,		//	6
	ERR_INVALIDTEXT,	//	7
	ERR_PARAM,			//	8
	ERR_INVALIDSESSION,	//	9
	ERR_SIZETOOSMALL,	//	10
	ERR_NOTSUPPORT,		//	11
	ERR_EXPIRED,		//	12
	ERR_ENGINE,			//	13
	ERR_DONOTHING,
	ERR_RESTARTDEVICE,
	ERR_PAUSEDEVICE,
	ERR_CODEPAGE
}ERRCODE;
	
	
typedef enum 
{
	PARAM_CODEPAGE,			
	PARAM_PITCH,			
	PARAM_VOLUME,		    
	PARAM_SPEED,			
	PARAM_PUNCMODE,			
	PARAM_DIGITMODE,		
	PARAM_ENGMODE,
	PARAM_TAGMODE,
	PARAM_WAVFORMAT,
}
JTTSPARAM;	
	
#define	CODEPAGE_GB		        936		
#define CODEPAGE_BIG5		    950
#define CODEPAGE_UTF8 			65001
#define CODEPAGE_UNICODE		1200
#define CODEPAGE_UNICODE_BIGE	1201	
	
#define DIGIT_AUTO			0
#define DIGIT_AUTO_NUMBER	0	
#define DIGIT_TELEGRAM		1	
#define DIGIT_NUMBER		2	
#define DIGIT_AUTO_TELEGRAM	3	
	
#define ENG_AUTO				0
#define ENG_SAPI				1	
#define ENG_LETTER				2	
	
#define FORMAT_WAV			0	
#define FORMAT_VOX_6K		1	
#define FORMAT_VOX_8K		2	
#define FORMAT_ALAW_8K		3	
#define FORMAT_uLAW_8K		4	
#define FORMAT_WAV_8K8B		5	
#define FORMAT_WAV_8K16B	6	
#define FORMAT_WAV_16K8B	7	
#define FORMAT_WAV_16K16B	8	
#define FORMAT_WAV_11K8B	9	
#define FORMAT_WAV_11K16B	10	
#define FORMAT_WAV_22K8B	11	
#define FORMAT_WAV_22K16B	12	
#define FORMAT_WAV_44K8B	13	
#define FORMAT_WAV_44K16B	14	
	
	//֧��TAG
#define TAG_AUTO				0x00
#define TAG_JTTS				0x01
#define TAG_SSML				0x02
#define TAG_NONE				0x03
	
	//DigitMode
#define DIGIT_AUTO_NUMBER		0
#define DIGIT_TELEGRAM			1
#define DIGIT_NUMBER			2
#define DIGIT_AUTO_TELEGRAM		3
	
	
	// PuncMode
#define PUNC_OFF				0
#define PUNC_ON					1
#define PUNC_OFF_RTN			2
#define PUNC_ON_RTN				3
	
	// EngMode
#define ENG_AUTO				0
#define ENG_SAPI				1
#define ENG_LETTER				2
#define ENG_LETTER_PHRASE		3
	
	//Gender
#define GENDER_FEMALE			0
#define GENDER_MALE				1
#define GENDER_NEUTRAL			2
	
	//Pitch
#define PITCH_MIN   0
#define PITCH_MAX   1000
	
	//Speed
#define SPEED_MIN   0
#define SPEED_MAX   1000
	
	// Volume
#define VOLUME_MIN	0
#define VOLUME_MAX	1000
	
#define JTTS_DEFAULT  500
	
#define JTTS_IDLE		0
#define JTTS_PLAY		1
#define JTTS_PAUSE		2
#define JTTS_STOP		3
	
#define NOTIFY_TTS_BEGIN		0	// lParam: not use 
#define NOTIFY_TTS_END			1	// lParam: not use
#define NOTIFY_TTS_PROGRESS		2	// lParam: bytes of content have been read
#define NOTIFY_TTS_PROGRESS2	3	// lParam: end postion of content will be read in next session
#define NOTIFY_TTS_DATA			4	// lParam: data package
	
JTTS_EXPORT_C ERRCODE TTSAPI jTTSInit(const nuCHAR* szCNLib, const nuCHAR* szENLib, const nuCHAR* szDMLib, DWORD* pdwHandle, void * pExtBuf);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSEnd(DWORD dwHandle);

JTTS_EXPORT_C int	 TTSAPI jTTSGetExtBufSize(void);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSSetParam(DWORD dwHandle, JTTSPARAM nParam, DWORD dwValue);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSGetParam(DWORD dwHandle, JTTSPARAM nParam, DWORD *pdwValue);

JTTS_EXPORT_C ERRCODE TTSAPI jTTSSessionStart(DWORD dwHandle, const nuCHAR * pcszText);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSSessionStop(DWORD dwHandle);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSSessionGetData(DWORD dwHandle, void * pVoiceData, DWORD * pdwLen,int nBufIndex);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSSessionGetReadBytes(DWORD dwHandle, DWORD * pdwBytes);

#ifdef ANDROID
#ifndef STD_ANSI_C
long	jtts_ftell( FILE*  stream );
int		jtts_fseek( FILE*  stream, long offset, int origin );
size_t	jtts_fread( void *buffer, size_t size, size_t count, FILE*  stream );
size_t	jtts_fwrite(void *buffer, size_t size, size_t count, FILE*  stream );
FILE*	jtts_fopen( const nuCHAR *filename, const nuCHAR *mode );
int		jtts_fclose( FILE* stream );
void*	jtts_memset(void *dest, int c, size_t count);
void*	jtts_memcpy(void *dest, const void *src, size_t count);
void*	jtts_malloc(unsigned int size);
void	jtts_free(void* p);
int		jtts_sprintf(nuCHAR *buffer, const nuCHAR *format, ...);
int		jtts_printf(const nuCHAR *format, ...);
int		jtts_atoi(const nuCHAR *string);
float	jtts_atof(const nuCHAR *string);
char*	jtts_strtok(nuCHAR *strToken, const nuCHAR *strDelimit);
#endif
#endif
typedef BOOL (* JTTSCALLBACKPROCEX)(WORD wParam, LONG lParam, DWORD dwUserData);

#define JTTS_ACTIVE_PLAYMODE	0
#define JTTS_PASSIVE_PLAYMODE	1

#define JTTS_PLAYSTATUS_INDEX	0
#define JTTS_PLAYMODE_INDEX		4

//������ʽ
typedef struct tagJTTSActivePlayStruct
{
	UINT uPlayStatus;

	// ���±�����Ҫ�ϲ�Ӧ������ֵ
	UINT uPlayMode;				// ͬ�����ŷ�ʽ����JTTS_ACTIVE����JTTS_PASSICE������״̬����JTTS_ACTIVE
	unsigned long dwUserData;

	nuCHAR* pPlayBuf;				// �������������ϳɵ����ݻ���������С��nBufNum*nBufSize
	unsigned long nBufNum;		// ���ݻ������ĸ���,����Ӧ������������
	unsigned long nBufSize;		// ÿ���������Ĵ�С,���ֽڼ���

	void* pPlayDevice;			// ����豸�ľ������ָ��
	// ���ϱ�����Ҫ�ϲ�Ӧ������ֵ

	BOOL* pbPlaying;			// ��ǰBuffer�Ƿ��ڲ���״̬

	// ���º�����Ҫ�ϲ�Ӧ����ʵ��
	void (*lpfnPlay)(void* pPlayDevice, nuCHAR* pVoiceData, unsigned long nLen, int* pbPlaying);
	BOOL (*lpfnNotifyCallBack)(unsigned short wParam, long lParam, DWORD dwUserData);
	void (*lpfnSleep)(void);
	// ���Ϻ�����Ҫ�ϲ�Ӧ����ʵ��
} JTTSActivePlayStruct;

// ������ʽ
typedef struct tagJTTSPassivePlayStruct
{
	UINT uPlayStatus;

	// ���±�����Ҫ�ϲ�Ӧ������ֵ
	UINT uPlayMode;				// ͬ�����ŷ�ʽ����JTTS_ACTIVE����JTTS_PASSICE������״̬����JTTS_PASSICE
	unsigned long dwUserData;

	nuCHAR* pPlayBuf;				// �������������ϳɵ����ݻ�����,��С��nPlayBufSize
	unsigned long nPlayBufSize; // ��������С,Ӧ���ǲ����豸��������С�ı���,������2��
	
	nuCHAR* pTTSBuf;				// TTS��һ��Session��buffer
	unsigned long nTTSBufSize;	// TTS��һ��Session��buffer��С�����ֽڼ���
	// ���ϱ�����Ҫ�ϲ�Ӧ������ֵ

	// ���º�����Ҫ�ϲ�Ӧ����ʵ��
	BOOL (*lpfnNotifyCallBack)(unsigned short wParam, long lParam, DWORD dwUserData);
	void (*lpfnSleep)(void);
	// ���Ϻ�����Ҫ�ϲ�Ӧ����ʵ��

	unsigned long nReadPos;		// pPlayBuf �ɶ����ݵ�λ��
	unsigned long nWritePos;	// pPlayBuf ��д�����ݵ�λ��
	unsigned long nRealDataSize;// pPlayBuf Ŀǰ������������ݵĴ�С
	BOOL bSessionEnd;			// �ϳɵ�Session������־
	
	int  (*lpfnGetVoiceData)(DWORD dwHandle, void* pJPS, nuCHAR* pData, unsigned long nSize);
} JTTSPassivePlayStruct;

JTTS_EXPORT_C ERRCODE TTSAPI jTTSPlay(DWORD dwHandle, const nuCHAR* pcszText, void* pJPS);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSStop(DWORD dwHandle);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSPause(DWORD dwHandle);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSResume(DWORD dwHandle);
JTTS_EXPORT_C ERRCODE TTSAPI jTTSGetAudio(DWORD dwHandle,UINT* pnSamplesPerSec,UINT* pnBitsPerSample);
	
#ifdef __cplusplus
}
#endif

////////
UINT g_uTextCounter;	//��ʾ��������
////////
#endif
