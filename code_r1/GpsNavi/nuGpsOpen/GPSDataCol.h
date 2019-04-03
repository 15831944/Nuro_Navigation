// GPSDataCol.h: interface for the CGPSDataCol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSDATACOL_H__F1E40937_4F35_468C_A5B6_9D0E2580417C__INCLUDED_)
#define AFX_GPSDATACOL_H__F1E40937_4F35_468C_A5B6_9D0E2580417C__INCLUDED_

#include "NuroClasses.h"
#include "NuroOpenedDefine.h"
#include "GpsLogFileZ.h"

#include "NuroModuleApiStruct.h"



#define MAXSAVEBUFFER	256

//NEMA Table��
#define NMEAID_NONE		0
#define NMEAID_GGA		10//GGA�t�C
#define NMEAID_GNGGA	11
#define NMEAID_GPGLL	20
#define NMEAID_GSA		30
#define NMEAID_GNGSA	31
#define NMEAID_GSV		40//GSV�t�C
#define NMEAID_BDGSV	41
#define NMEAID_GLGSV	42
#define NMEAID_GPRMC	50
#define NMEAID_GPVTG	60
#define NMEAID_RTOEM	100
#define NMEAID_GPTXT	101
#define NMEAID_DRDLLOUT	102
#define NMEAID_GPGDR	103
#define NMEAID_GYRO		104
#define NMEAID_DRRMC		105

#define KMTOSNOT 1.8519

//���D		40075 000m = 360 00000		->	1113:1000
//�l�Ƚu	39942 000m = 360 00000		->	1109.5:1000
#define LONEFFECTCONST							1113//111
#define LATEFFECTCONST							1109//110
#define EFFECTBASE								1000//100
#define DEGBASE									100000

#define RCVCOUNT		2048

#define	AUTOFIXANGLE		2
#define FIXPOSITION			12

/************************************************************/

typedef struct TAGMEASINFO
{
	nuINT	datafield:24;
	nuUINT	datatype:6;
	nuINT	reserve:2;
}MEASINFO,*PMEASINFO;


typedef struct TAGGYROSTATUS
{
	nuBOOL	bAngleInit;
	nuBOOL	bSpeedInit;
	nuBOOL	bAngleInput;
	nuBOOL	bSpeedInput;
	nuLONG	lSystemStatus:4;
	nuLONG	lDeltaAngle:28;
	nuLONG	lDeltaDis;
	nuLONG	lcalibstatus;
}GYROSTATUS;

typedef struct TAGEKFSTATUS
{
	nuLONG	pluses;
	nuLONG	period;
	nuDWORD	difang;
	nuSHORT	temperature;
	nuCHAR	direction;
	nuBYTE	calib_status_ScalefactorTacho:2;
	nuBYTE	calib_status_ScalefactorGyro:2;
	nuBYTE	calib_status_BiasGyro:2;
	nuBYTE	calib_status_Reserve:2;
	nuLONG	pulse_scale;
	nuLONG	gyro_bias;
	nuLONG	gyro_scale;
	nuSHORT	acc_pluse_scale;
	nuSHORT	acc_gyro_bias;
	nuSHORT	acc_gyro_scale;
	nuBYTE	meas_used_TachoPulse:1;
	nuBYTE	meas_used_forbackwardsignal:1;
	nuBYTE	meas_used_Gyro:1;
	nuBYTE	meas_used_Temperature:1;
	nuBYTE	meas_used_GPSPosition:1;
	nuBYTE	meas_used_GPSVelocity:1;
	nuBYTE	meas_used_GYROsensor:1;
	nuBYTE	meas_used_speedpulsesensor:1;
	nuBYTE	reserved2;
}EKFSTATUS;

typedef struct TAGSPECIALCASE_UBLOS
{
	nuSHORT	nOdometerSpeed;//���t�u�t��
	nuBOOL	bAngleInit;
	nuBOOL	bSpeedInit;
	nuBOOL	bAngleInput;
	nuBOOL	bSpeedInput;
	nuLONG	lSystemStatus:4;
	nuLONG	lDeltaAngle:28;
	nuLONG	lcalibstatus;
	GPSMODINFO	ModInfo;
}SPECIALCASE_UBLOS;

typedef struct TAGSPECIALCASE_ROYALTEK
{
	nuBOOL	bAngleInit;
	nuBOOL	bSpeedInit;
	nuBOOL	bAngleInput;
	nuBOOL	bSpeedInput;
	nuLONG	lSystemStatus:4;
	nuLONG	lDeltaAngle:28;
	nuLONG	lDeltaDis;
	nuSHORT	nSlopeStatus;	//2:�W�Y 1:�w�W�Y  0:���`	-1:�w�U�Y -2:�U�Y	   

}SPECIALCASE_ROYALTEK;

typedef struct TAGSPECIALCASE_EL
{
	nuCHAR	sELGyroStatus;
	nuSHORT	nSlopeStatus;
	nuSHORT	nSpeed;
	nuSHORT	nAngle;		
	nuLONG	nLatitude;//
	nuLONG	nLongitude;//
}SPECIALCASE_EL;

typedef struct TAGSPECIALCASE_SMART
{
	nuLONG	lLatitude;		
	nuLONG	lLongitude;
	nuSHORT	nOBD_Speed;		//CANBUS SPEED FOR ���p
	nuSHORT	nSlopeStatus;	//2:�W�Y 1:�w�W�Y  0:���`	-1:�w�U�Y -2:�U�Y	   
	nuSHORT	nAngle;		
	nuLONG	lSystemStatus;
}SPECIALCASE_SMART;

typedef struct TAGSPECIALCASE_SIRFBINARY
{
	nuSHORT	nOBD_Speed;
	nuSHORT	nReverseSignal;//�˨��T�� 0:���e ��l:�˰h
	nuBOOL	bAngleInit;
	nuBOOL	bSpeedInit;
	nuBOOL	bAngleInput;
	nuBOOL	bSpeedInput;
}SPECIALCASE_SIRFBINARY;

#define FINDDR_NO			0
#define FINDDR_GENERAL		1
#define FINDDR_EL			2
#define FINDDR_ROYALTEK		3
#define FINDDR_UBLOS		4
#define FINDDR_SMART		5
#define FINDDR_SIRFBINARY	6
#define FINDDR_CN_DR		7

typedef struct TAGSPECIALCASEDATA
{
	nuINT					l_DRMode;
	SPECIALCASE_EL			m_EL;//�ɧQ
	SPECIALCASE_ROYALTEK	m_ROYALTEK;//����
	SPECIALCASE_UBLOS		m_UBLOS;//UBLOS
	SPECIALCASE_SMART		m_SMART;//���p
	SPECIALCASE_SIRFBINARY	m_SIRFBINARY;//�Q�USIRF Binary
}SPECIALCASEDATA;

typedef struct GYROSATINFO {
	nuUCHAR nPRN;			// Get from $GPGSV
	nuUCHAR bActived;		//true or false�Ainstead of unsigned short stActiveSat[12]
	nuUSHORT nSigQuality;	// Get from $GPGSV
	nuUSHORT nAzimuth;		// Get from $GPGSV
	nuUSHORT nElevation;		// Get from $GPGSV
} GyroSatInfo;

typedef struct tagFEEDBACKINFO
{
	nuLONG	nRoadx;
	nuLONG	nRoady;
	nuLONG	ndx;
	nuLONG	ndy;
	nuLONG	nOldx;
	nuLONG	nOldy;
	nuSHORT	nSpeed;
	nuINT	nTime;
	nuINT	Angle;
	nuINT	SystemAngle;
}FEEDBACKINFO,*PFEEDBACKINFO;

class CGPSDataCol  
{
	public:
		nuBOOL bCheckTimeForZone(NUROTIME* nuTIME, nuINT iZoneTime);
		nuBOOL AddMMF(nuLONG nLat,nuLONG nLng,nuSHORT nAngle,nuLONG nLatFix,nuLONG nLngFix,nuSHORT nAngleFix);
		CGPSDataCol();
		virtual ~CGPSDataCol();
		nuVOID InitClass();
		nuVOID GPSFeedBack(const FEEDBACKDATA* pFeedBackInfo);
		nuVOID GPSFeedBack_Speed(nuLONG nRoadx, nuLONG nRoady, nuSHORT dx, nuSHORT dy, nuSHORT nSpeed, nuINT nTime);
		nuBOOL			b_updateModInfo;
		
		GPSDATA			m_GPSRawInfo;//added by daniel 20120204
		GPSDATA			m_BackData;
		GPSDATA			m_GyroBackData;
		nuLONG			l_GPSSateSystem;
		
		nuBOOL			NewConvertNewData(nuBYTE* NewData,nuLONG DataLen,nuLONG lGPSMode);
		nuINT			ColPanaBinary(nuBYTE *NewData,nuLONG DataLen,nuBYTE &lGPSMode);
		nuBOOL			Col_ELeadData(const GYROGPSDATA_EL* pEL_GyroData);
		nuBOOL			bFindRMC;
		nuBOOL			bFindGSV;
		nuBOOL			bFindGGA;
		nuBOOL			g_bHaveNewData;
		GPSMODINFO		m_GpsModInfo;

	protected:
		nuLONG			m_nZoneTime;
		nuLONG            m_nChinaFix;
		nuLONG			TempSaveInfoAngle;


		FEEDBACKINFO	g_FixedInfo;//�t�Φ^�Ӫ��ץ���T
		nuLONG			l_FixAngleStableCount;
		nuBYTE			nGGASeconds;//�ΨӦP�B���

		SPECIALCASEDATA	m_SpecialCaseData;
		GPSDATA			m_FirstHandData;
		GPSDATA			m_SecondTimeData;
		GPSDATA			m_DRData;

	private:
		nuBOOL			CombineGPSandDR(nuLONG lGPSMode);

		nuVOID			CopyNEMAToBackupBuffer();//
						
		//Louis 090910 New Collation GPSData
		nuLONG CheckNEMATable(nuCHAR* NewData,nuLONG lGPSMode);
		nuBOOL ColSingleLineNEMAData(nuCHAR *ItemData,nuBYTE DataLen,nuLONG lNEMACode,nuLONG lGPSMode);

		//�`��NEMA��ƪ��Ѽ� 091007 Louis
		nuVOID ColRMC(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColGGA(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColGSA(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColGSV(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColRTOEM(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColGPGDR(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColGYRO(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColDRRMC(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuBOOL CheckNEMAReady(nuLONG lGPSMode);

		//�`��UBlos�S�w���
		nuBOOL ColUBlosEKFSTATUS(nuUCHAR *ItemData,nuBYTE DataLen);
		nuBOOL ColUBlosNAVSTATUS(nuUCHAR *ItemData,nuBYTE DataLen);
		nuBOOL ColUBlosESFMEAS(nuUCHAR *ItemData,nuBYTE DataLen);
		nuBOOL ColUBlosESFSTATUS(nuUCHAR *ItemData,nuBYTE DataLen);
		nuBOOL ColUBlosEKF(nuUCHAR *ItemData,nuBYTE DataLen);
		nuBOOL ColUBlosVersion(nuUCHAR *ItemData,nuBYTE DataLen);
		nuBOOL ColUBlosEnable(nuUCHAR *ItemData,nuBYTE DataLen);
		nuVOID ColGPTXT(nuLONG Index,nuCHAR *ItemData,nuBYTE DataLen);
		nuVOID InitNewConvertNewData();

		nuUCHAR			byTempSaveBuffer[MAXSAVEBUFFER];
		nuLONG			lNowNEMACode;
		nuBYTE			byTempSaveBufferCount;//
		nuBOOL			bStartSave;//�ΨӧP�w�O�_�}�l�B�z�@���ƪ�flag
		nuBYTE			byCheckSum;//�����checksum���x�s�p�⾹
		nuCHAR			byChecksumBuffer[3];//�s��checksum��ƪ��Ŷ�
		nuBYTE			byChecksumBufferCount;//�ȦsChecksum��ƪ��p�ƾ�
		nuBOOL			bAddNewStar;//�O�_�W�[�s���ìP���
		nuDWORD			byEKFCheckSum[2];
		nuLONG			m_nChecrSerRec;
		nuLONG			m_GSAIndex;
		nuLONG			m_GSAcleantime;
		nuLONG			GSAID[MAX_STAR_NUMBER];
		nuBYTE			Rcv[RCVCOUNT];
		nuWORD			RcvLen;
		GYROSTATUS		stuGyro;
		nuLONG			g_TunelDelay;
		nuLONG			g_hasDRSystem;
		nuBOOL			IsTunel;
		nuBYTE			m_nRMC_State;
};

#endif // !defined(AFX_GPSDATACOL_H__F1E40937_4F35_468C_A5B6_9D0E2580417C__INCLUDED_)










































