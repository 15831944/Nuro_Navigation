#ifndef __NURO_NAVIGATION_CONSTANTS
#define __NURO_NAVIGATION_CONSTANTS

#define VRT_Defway						0//General Road						�@��D��
#define VRT_Freeway						1//Freeway							���t����
#define VRT_Fastway						2//Fastway							�ֳt�D��
#define VRT_SlipRoad					3//Slip Road						��y�D
#define VRT_Overpass					4//Overpass							���[��
#define VRT_Tunnel						5//Tunnel							�G�D
#define VRT_Underpass					6//Underpass						�a�U�D
#define VRT_UnOverpass					7//Road Under Overpass				���[���U�D��
#define VRT_SurroundWay					8//Road Surrond the City			�~���D
#define VRT_StopcockWay					9//Slip Road(Diff Name)				�`�D
#define VRT_GuideWay					10//Road along MajorRoad 			�޹D
#define VRT_3DSlipRoad					11//Overpass Slip Road				�ߥ��
#define VRT_Tollgate					20//Tollgate						���O��
#define VRT_RestStop					21//Reststop						�𮧰�
#define VRT_HasSlipRoad					22//warn user here has Slip Road	����y�D
#define	VRT_ScanSpeed					23//���t�Ӭ�
#define VRT_IN_FASTROAD					27
#define	VRT_IN_SLOWROAD					28 
#define VRT_TrafficCircle				30//Traffic Circle					����
#define VRT_ROADCROSS					31
#define VRT_FastToSlow                  33//(��?��) for panasonic
#define VRT_SlowToFast					34//(��?��) for panasonic
#define VRT_SlowWay						40//:��?��
#define VRT_UTURN						41
#define VRT_LTURN						42
#define VRT_RTURN						43
#define VRT_FERRY						50 //�ڶ�
#define VRT_Bridge                      51//����
#define VRT_StartSite					91//Start Site that u set set		�_�I
#define VRT_CityTownBoundary			96//City or Town Boundary			�m�����
#define VRT_MapBoundary					97//Near Map Boundary				�a�����
#define VRT_MidSite						98//Middle Site that uset set		�g���I
#define VRT_EndSite						99//End Site that user set			���I
//TurnFlag in RoutingData 
#define T_No						    0//�L�ʧ@
#define T_Afore							1//����
#define T_Left						    2//����
#define T_Right							3//�k��
#define T_LeftSide						4//�ø��V��
#define T_RightSide						5//�ø��V�k
#define T_MidWay						6//���u
#define T_LUturn						7//���j��
#define T_RUturn						8//�k�j��
#define T_Direction						9//�̫��ܤ�V
#define T_LeftLeft						18//����
#define T_RightRight				    19//�k��
#define T_LeftLeftSide                  20//�ø��V��
#define T_RightRightSide				21//�ø��V�k
#define T_LULUturn						22//���j��
#define T_RURUturn						23//�k�j��
//--------------------------------------------------------------
#define AF_NoPlay						9999//(����������)
#define AF_LoseHere						0//(�u�����Z���P��V)
#define AF_In_SlipRoad					1//�i�J��y�D
#define AF_In_Underpass					2//�i�J�a�U�D
#define AF_In_Fastway					3//�i�J�ֳt�D��
#define AF_In_Overpass					4//�i�J���[��
#define AF_In_Freeway					5//�i�J���t����
#define AF_In_Tunnel					6//�i�J�G�D
#define AF_Out_SlipRoad					7//�p����y�D
#define AF_Out_Underpass				8//�p���a�U�D
#define AF_Out_Fastway					9//�p���ֳt�D��
#define AF_Out_Overpass					10//�p�����[��
#define AF_Out_Freeway					11//�p�����t����
#define AF_Out_Tunnel					12//�p���G�D
#define AF_In_UnOverpass				13//�������D��
#define AF_In_Tollgate					14//�i�J���O��
#define AF_In_RestStop					15//�i�J�𮧯�
#define AF_Has_SlipRoad					16//����y�D
#define	AF_MidSit						17//���t�Ӭ�
#define AF_In_TrafficCircle				18//In Traffic Circle					����
#define AF_Out_TrafficCircle			19//Out Traffic Circle					����
#define AF_Has_RestStop					20
#define AF_IN_FASTROAD					21
#define	AF_IN_SLOWROAD					22 
#define AF_OUT_FASTROAD					23
#define AF_OUT_SLOWROAD					24
#define AF_IN_MAINROAD					25 //��������
#define AF_IN_AUXROAD				    26  //���븨��
#define AF_OUT_MAINROAD					27 //�뿪����
#define AF_OUT_AUXROAD				    28  //�뿪����
#define AF_IN_Bridge                    29 //�i�J����

#define AF_CityTownBoundary				30//��F���m���
#define AF_MapBoundary					31//��F���

#define AF_IN_UTURN						40
#define AF_IN_LTURN						41
#define AF_IN_RTURN						42
#define AF_IN_FERRY						43 //����ڶ�

//#define AF_MidSit						98//��F�g���I
#define AF_EndSite						99//��F���I
#define AF_ChangeRoadName				100//�ܴ���

//Distance.txt index
#define	DIS_FOLLOW							1
#define	DIS_100M							2
#define DIS_300M							3
#define	DIS_700M							4
#define DIS_500M							5
#define DIS_1KM								6
#define DIS_2KM								7
#define DIS_IGNORE							0
#define DIS_ESTIMATION                      8
//
#define DIS_DRIVE                           9
#define DIS_PREPARE                         10
//fastway
#define  VOICEDIS2000_E						1850
#define  VOICEDIS2000_S						2150
#define  VOICEDIS1000_E						850
#define  VOICEDIS1000_S						1150
#define  VOICEDIS500_E_FastWay				400
#define  VOICEDIS500_S_FastWay				600
//
#define  VOICEDIS500_E_SlowWay				400
#define  VOICEDIS500_S_SlowWay				600
#define  VOICEDIS300_E						250
#define  VOICEDIS300_S						350
#define  VOICEDIS100_E						0
#define  VOICEDIS100_S						150 

//
#define  IN_REAL3DPIC						600
#define  IN_CROSSDIS_LEVEL_1				300
#define	 IN_CROSSDIS_LEVEL_2				150
#define  OUT_CROSSDIS_LEVEL_1				50
#define  OUT_CROSSDIS_LEVEL_2				100
//
#define  NO_ACTION							0
#define  IN_LEVEL_1							1
#define  IN_LEVEL_2							2
#define  OUT_LEVEL_1						3
#define	 OUT_LEVEL_2						4

//
#define  DIS_BETWEENINGORE							150
#endif

#define Elead_Roundabout_Right               1//�f�ɰw
#define Elead_Roundabout_Left				 2//���ɰw
#define Elead_In_TrafficCircle               3//�a�����
#define Elead_Straight						 4//����
#define Elead_Slight_Left					 5//���e�����s
#define Elead_Slight_Right					 6//�k�e�����s
#define Elead_Keep_Left						 7//�ø��V��
#define Elead_Keep_Right					 8//�ø��V�k
#define Elead_Left							 9//����
#define Elead_Right							10//�k��
#define Elead_Hard_Left						11//��������s
#define Elead_Hard_Right					12//�k������s
#define Elead_Uturn_Left					13//���j��
#define Elead_Uturn_Right					14//�k�j��
#define Elead_Destination                   15//��F�ت��a
#define Elead_LeaveNaviLine					16//�����ɯ���u
#define Elead_Enter_Bridge                  17//�i�J����
#define Elead_Enterfreeway_Left             18//�����i�J���t����
#define Elead_Enterfreeway_Right            19//�k���i�J���t����
#define Elead_Exitfreeway_Left              20//�������}���t����
#define Elead_Exitfreeway_Right             21//�k�����}���t����
#define Elead_Toll_Booth                    22//���O��
#define Elead_Enter_Tunnel                  23//�i�J�G�D
#define Elead_Enterferry_Left               24//����i�J���
#define Elead_Enterferry_Right              25//�k��i�J���
#define Elead_Exitferry_Left                26//�������}���
#define Elead_Exitferry_Right               27//�k�����}���
#define Elead_Exitferry                     28//�a����
#define Elead_Takeramp_Right                29//�k��i�J�`�D
#define Elead_Takeramp_Left                 30//����i�J�`�D