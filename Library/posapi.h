/*****************************************************/
/* Pax.h                                             */
/* Define the Application Program Interface          */
/* for all PAX POS terminals     		     */
/*****************************************************/

#ifndef  _PAX_POS_API_H
#define  _PAX_POS_API_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define ushort unsigned short

//===========================================================
//           structure for smart card operation
//===========================================================
typedef struct{
   	unsigned char Command[4];
   	unsigned short Lc;
   	unsigned char  DataIn[512];
   	unsigned short Le;
}APDU_SEND;

typedef struct{
	unsigned short LenOut;
   	unsigned char  DataOut[512];
   	unsigned char  SWA;
   	unsigned char  SWB;
}APDU_RESP;


//================================================
//         structure for modem operation
//=================================================
typedef struct{
	unsigned char DP;
	unsigned char CHDT; 
	unsigned char DT1;
	unsigned char DT2;
	unsigned char HT;
	unsigned char WT;
	unsigned char SSETUP;
	unsigned char DTIMES;
	unsigned char TimeOut;
	unsigned char AsMode;
}COMM_PARA;



//=============================================================================
// structure  and macros for ped operation begin
// nicm add 2008-07-25 being
//=============================================================================
typedef struct
{
	// ��ɢ����Կ��Դ��Կ����Կ���ͣ�PED_GMK,PED_TMK,PED_TPK,PED_TAK,PED_TDK, ���õ���ucDstKeyType���ڵ���Կ����
	uchar ucSrcKeyType; 
	// ��ɢ����Կ��Դ��Կ����������һ���1��ʼ������ñ���Ϊ0�����ʾ�����Կ��д����������ʽ
	uchar ucSrcKeyIdx; 
	// Ŀ����Կ����Կ���ͣ�PED_GMK,PED_TMK,PED_TPK,PED_TAK,PED_TDK
	uchar ucDstKeyType;
	// Ŀ����Կ����
	uchar ucDstKeyIdx;
	// Ŀ����Կ���ȣ�8,16,24
	int iDstKeyLen; 
	// д����Կ������
	uchar aucDstKeyValue[24]; 
}ST_KEY_INFO;

typedef struct
{
  int iCheckMode;
  uchar aucCheckBuf[128];
}ST_KCV_INFO;

/**
AES ��Կ��Ϣ������д��AES ��Կ��Ϣʱ����AES ��Կ�������Ϣ,
��PedWriteKey()��������ST_KCV_INFO���ݽṹ��
*/
typedef struct
{
	/** ��ɢ����Կ��Դ��Կ����Կ���ͣ�
	PED_TLK,PED_TMK,PED_TPK,PED_TAK,PED_TDK, PED_TAESK, 
	���õ���ucDstKeyType���ڵ���Կ����*/
	uchar ucSrcKeyType;
	/** ��ɢ����Կ��Դ��Կ������
	����һ���1��ʼ������ñ���Ϊ0��
	���ʾ�����Կ��д����������ʽ*/
	uchar ucSrcKeyIdx;
	/** Ŀ����Կ����Կ����: PED_TAESK */
	uchar ucDstKeyType;
	/*Ŀ����Կ����*/
	uchar ucDstKeyIdx;
	/**Ŀ����Կ���ȣ�16,24,32 */
	int iDstKeyLen;
	/**д����Կ������ */
	uchar aucDstKeyValue[32];
}ST_AES_KEY_INFO;

#define PED_BKLK  0x01  //BKLK
#define PED_TMK   0x02 //TMK
#define PED_TPK   0x03 //PIN Key
#define PED_TAK	  0x04 //MAC Key
#define PED_TDK   0x05 //DES Key
#define	PED_DUKPT 0X06
#define	PED_TPAK  0X07//(����TPK/TAK���õ�ģʽ)


//define��Կ���������붨��
#define PED_DOWNLOAD_CMD_TYPE 0X00
// ��ȡ�汾
#define PED_CMD_GETVER 0x00
// ����ϵͳ���з�����Ȩ����ȡ�����
#define PED_CMD_REQ_SYS_SSA	0X01
// ������������Ĳ���ȡ
#define PED_CMD_GET_TEK 0X02
// ��ʽ��ped
#define PED_CMD_FORMAT_PED 0X03//
 // д��MKSK ��Կ
#define PED_CMD_WRITEKEY 0x04//
// д��TIK
#define PED_CMD_WRITETIK 0x05//
// ������Կ��ǩ
#define PED_CMD_SETKEYTAG 0X06//
// PED�������
#define PED_CMD_DOWNLOAD_COMPLETE 0X07	
 // ��ȡ�ն����к�
#define PED_CMD_READ_SN 0X08

// PEDAPI ��������ʼֵ
#define PED_RET_ERR_START -300
// PEDAPI ���������ֵ
#define PED_RET_ERR_END	-500
// PED����������ȷ
#define PED_RET_OK 0  
// ��Կ������
#define PED_RET_ERR_NO_KEY (PED_RET_ERR_START-1)  
// ��Կ�����������������ڷ�Χ��
#define PED_RET_ERR_KEYIDX_ERR     (PED_RET_ERR_START-2)  
// ��Կд��ʱ��Դ��Կ�Ĳ�α�Ŀ����Կ��
#define PED_RET_ERR_DERIVE_ERR	   (PED_RET_ERR_START-3)  
// ��Կ��֤ʧ��
#define PED_RET_ERR_CHECK_KEY_FAIL (PED_RET_ERR_START-4)  
// û����PIN
#define PED_RET_ERR_NO_PIN_INPUT   (PED_RET_ERR_START-5) 
// ȡ������PIN
#define PED_RET_ERR_INPUT_CANCEL   (PED_RET_ERR_START-6) 
// ��������С����С���ʱ��
#define PED_RET_ERR_WAIT_INTERVAL  (PED_RET_ERR_START-7) 
 // KCVģʽ����֧��
#define PED_RET_ERR_CHECK_MODE_ERR (PED_RET_ERR_START-8) 
// ��Ȩʹ�ø���Կ����������Կ��ǩ���ԣ�����д����Կʱ,
// Դ��Կ���͵�ֵ����Ŀ����Կ���ͣ����᷵�ظ���Կ
#define PED_RET_ERR_NO_RIGHT_USE   (PED_RET_ERR_START-9) 
// ��Կ���ʹ�
#define PED_RET_ERR_KEY_TYPE_ERR   (PED_RET_ERR_START-10)  
// ����PIN�ĳ����ַ�����
#define PED_RET_ERR_EXPLEN_ERR     (PED_RET_ERR_START-11)  
// Ŀ����Կ���������ڷ�Χ��
#define PED_RET_ERR_DSTKEY_IDX_ERR (PED_RET_ERR_START-12)  
// Դ��Կ���������ڷ�Χ��
#define PED_RET_ERR_SRCKEY_IDX_ERR (PED_RET_ERR_START-13)  
// ��Կ���ȴ�
#define PED_RET_ERR_KEY_LEN_ERR		(PED_RET_ERR_START-14) 
// ����PIN��ʱ
#define PED_RET_ERR_INPUT_TIMEOUT  (PED_RET_ERR_START-15) 
// IC��������
#define PED_RET_ERR_NO_ICC          (PED_RET_ERR_START-16)
// IC��δ��ʼ��
#define PED_RET_ERR_ICC_NO_INIT    (PED_RET_ERR_START-17) 
// DUKPT�������Ŵ�
#define PED_RET_ERR_GROUP_IDX_ERR (PED_RET_ERR_START-18)
// ָ������Ƿ�Ϊ��
#define PED_RET_ERR_PARAM_PTR_NULL    (PED_RET_ERR_START-19)
// PED����
#define PED_RET_ERR_LOCKED (PED_RET_ERR_START-20)		
// PEDͨ�ô���
#define PED_RET_ERROR (PED_RET_ERR_START-21)		
// û�п��еĻ���
#define PED_RET_ERR_NOMORE_BUF (PED_RET_ERR_START-22)	
// ��Ҫȡ�ø߼�Ȩ��
#define PED_RET_ERR_NEED_ADMIN (PED_RET_ERR_START-23)	
// DUKPT�Ѿ����
#define PED_RET_ERR_DUKPT_OVERFLOW (PED_RET_ERR_START-24)
// KCV У��ʧ��
#define PED_RET_ERR_KCV_CHECK_FAIL (PED_RET_ERR_START-25)
// д����Կʱ��Դ��Կid�����Ͳ���Դ��Կ���Ͳ�ƥ��
#define PED_RET_ERR_SRCKEY_TYPE_ERR	(PED_RET_ERR_START-26)
// ���֧��
#define PED_RET_ERR_UNSPT_CMD  (PED_RET_ERR_START-27)
// ͨѶ����
#define PED_RET_ERR_COMM_ERR (PED_RET_ERR_START-28)
// û���û���֤��Կ
#define PED_RET_ERR_NO_UAPUK (PED_RET_ERR_START-29)
// ȡϵͳ���з���ʧ��
#define PED_RET_ERR_ADMIN_ERR (PED_RET_ERR_START-30)
// PED�������طǼ���״̬
#define	PED_RET_ERR_DOWNLOAD_INACTIVE (PED_RET_ERR_START-31)

//KCV ��У��ʧ��
#define PED_RET_ERR_KCV_ODD_CHECK_FAIL (PED_RET_ERR_START-32)
//��ȡPED����ʧ��
#define PED_RET_ERR_PED_DATA_RW_FAIL (PED_RET_ERR_START-33)
//����������(�ѻ����ġ�����������֤)
#define PED_RET_ERR_ICC_CMD_ERR      (PED_RET_ERR_START-34)
//�û���CLEAR���˳�����PIN
#define PED_RET_ERR_INPUT_CLEAR		(PED_RET_ERR_START-39)
//PED�洢�ռ䲻��
#define PED_RET_ERR_NO_FREE_FLASH	(PED_RET_ERR_START-43)
//DUKPT KSN��Ҫ�ȼ�1
#define PED_RET_ERR_DUKPT_NEED_INC_KSN	(PED_RET_ERR_START-44)
//KCV MODE����
#define PED_RET_ERR_KCV_MODE_ERR	(PED_RET_ERR_START-45)
//NO KCV
#define PED_RET_ERR_DUKPT_NO_KCV   (PED_RET_ERR_START-46)
//��FN/ATM4��ȡ��PIN����
#define PED_RET_ERR_PIN_BYPASS_BYFUNKEY		(PED_RET_ERR_START-47)
//����MACУ���
#define PED_RET_ERR_MAC_ERR			(PED_RET_ERR_START-48)
//����CRCУ���
#define PED_RET_ERR_CRC_ERR			(PED_RET_ERR_START-49)

//=============================================================================
// structure for ped operation 
// nicm add 2008-07-25 end
//=============================================================================

//----------------------------------------------------------
// nicm add for new wireless module begin
//----------------------------------------------------------

#define WL_RET_ERR_PORTINUSE -201 // ģ��ڱ�ռ��
#define WL_RET_ERR_NORSP -202 // ģ��û��Ӧ��
#define WL_RET_ERR_RSPERR -203 // ģ��Ӧ�����
#define WL_RET_ERR_PORTNOOPEN -204 // ģ�鴮��û�д�
#define WL_RET_ERR_NEEDPIN -205	// ��ҪPIN��
#define WL_RET_ERR_NEEDPUK -206	// ��ҪPUK��PIN��
#define WL_RET_ERR_PARAMER -207	// ��������
#define WL_RET_ERR_ERRPIN -208 // �������
#define WL_RET_ERR_NOSIM -209 // û�в���SIM��
#define WL_RET_ERR_NOTYPE -210 // ��֧�ֵ�����
#define WL_RET_ERR_NOREG -211 // ����û��ע��
#define WL_RET_ERR_INIT_ONCE -212 // ģ���ѳ�ʼ��
#define WL_RET_ERR_LINEOFF -214	// ���ӶϿ�
#define WL_RET_ERR_TIMEOUT -216	// ��ʱ
#define WL_RET_ERR_REGING -222 // ����ע����
#define WL_RET_ERR_PORTCLOSE -223 // �رմ��ڳ���
#define WL_RET_ERR_MODEVER -225	// �����ģ��汾
#define WL_RET_ERR_DIALING -226	// ������  
#define WL_RET_ERR_ONHOOK -227 // �ػ���
#define WL_RET_ERR_PPP_BRK -228	// ����PPP�Ͽ�
#define WL_RET_ERR_NOSIG -229 // �������ź�
#define WL_RET_ERR_POWEROFF -230 // ģ�����µ�
#define WL_RET_ERR_BUSY -231 // ģ��æ
#define WL_RET_ERR_OTHER -300 // ����δ֪����

#define	NET_OK               0  // �޴�������
#define	NET_ERR_MEM     	 -1  // �ڴ治��
#define	NET_ERR_BUF     	 -2  // ����������
#define	NET_ERR_ABRT    	 -3  // ��ͼ��������ʧ��
#define	NET_ERR_RST     	 -4  // ���ӱ��Է���λ���յ��Է���Reset��
#define	NET_ERR_CLSD    	 -5  // �����ѹر�
#define	NET_ERR_CONN    	 -6  // ����δ�ɹ�����
#define	NET_ERR_VAL     	 -7  // �������
#define	NET_ERR_ARG     	 -8  // �������
#define	NET_ERR_RTE     	 -9  // ����·��(route)
#define	NET_ERR_USE     	 -10 // ��ַ���˿�ʹ����
#define	NET_ERR_IF      	 -11 // �ײ�Ӳ������
#define	NET_ERR_ISCONN  	 -12 // �����ѽ���
#define	NET_ERR_TIMEOUT 	 -13 // ��ʱ
#define	NET_ERR_AGAIN   	 -14 // ������Դ�����ڣ�������
#define	NET_ERR_EXIST   	 -15 // �Ѵ���
#define	NET_ERR_SYS     	 -16 // ϵͳ��֧��
#define	NET_ERR_PASSWD  	 -17 // ��������
#define	NET_ERR_MODEM   	 -18 // ����ʧ��
#define	NET_ERR_LINKDOWN   	 -19 // ������·�ѶϿ��������²���
#define	NET_ERR_LOGOUT	   -20 // Logout
#define	NET_ERR_PPP	       -21 // PPP�Ͽ�
#define NET_ERR_STR        -22 // String Too Long, Illeage
#define NET_ERR_DNS        -23 // DNS Failure: No such Name
#define NET_ERR_INIT       -24 // No Init





//=================================================
//			  for RF card functions
//=================================================
typedef struct
{
	unsigned char  drv_ver[5];  //e.g. "1.01A", read only
	unsigned char drv_date[12]; //e.g. "2006.08.25",read only

	unsigned char a_conduct_w;  //Type A conduct write enable: 1--enable,else disable
	unsigned char a_conduct_val;//Type A output conduct value,0~63

	unsigned char m_conduct_w;  //M1 conduct write enable: 1--enable,else disable
	unsigned char m_conduct_val;//M1 output conduct value,0~63

	unsigned char b_modulate_w;  //Type B modulate index write enable,1--enable,else disable
	unsigned char b_modulate_val;//Type B modulate index value

	uchar card_buffer_w;//added in V1.00C,20061204
	ushort card_buffer_val;//max_frame_size of PICC

	uchar wait_retry_limit_w;//added in V1.00F,20071212
	ushort wait_retry_limit_val;//max retry count for WTX block requests,default 3
	// 20080617 
	uchar card_type_check_w; // ��Ƭ���ͼ��д������1--��������ֵ--��������Ҫ���ڱ�����Ƭ���淶���������
	
	uchar card_type_check_val; // 0-��鿨Ƭ���ͣ�����������鿨Ƭ����(Ĭ��Ϊ��鿨Ƭ����)
	
	//uchar reserved[92];  //�����ֽڣ����ڽ�����չ��д��ʱӦȫ����
	
	//2009-10-30	
	uchar card_RxThreshold_w; // ��Ƭ���ͼ��д������1--��������ֵ--��������Ҫ���ڱ�����Ƭ���淶���������
	
	uchar card_RxThreshold_val;//��Ƭ����������
		
	//2009-11-20

     uchar f_modulate_w; // felica�������д������

     uchar f_modulate_val;//felica�������

	 //add by wls 2011.05.17
	 unsigned char a_modulate_w; // A������ָ��д������1--��������ֵ��������
	 unsigned char a_modulate_val; // A������ָ�����Ʊ�������Ч��Χ0~63,����ʱ��Ϊ63
	 
		//add by wls 2011.05.17
	 unsigned char a_card_RxThreshold_w; //���������ȼ��д������1--��������ֵ--������
	 unsigned char a_card_RxThreshold_val;//A������������
	 
	 //add by liubo 2011.10.25, ���A,B��C������������
	 unsigned char a_card_antenna_gain_w;
	 unsigned char a_card_antenna_gain_val;
	 
	 unsigned char b_card_antenna_gain_w;
	 unsigned char b_card_antenna_gain_val;
	 
	 unsigned char f_card_antenna_gain_w;
	 unsigned char f_card_antenna_gain_val;
	 
	 //added by liubo 2011.10.25�����Felica�Ľ���������
	 unsigned char f_card_RxThreshold_w;
	 unsigned char f_card_RxThreshold_val;
	 
	/* add by wanls 2012.08.14*/
	unsigned char f_conduct_w;  
	unsigned char f_conduct_val; 
	
	/* add by nt for paypass 3.0 test 2013/03/11 */
	unsigned char user_control_w;
	unsigned char user_control_key_val;
	
	unsigned char reserved[72]; //modify by nt 2013/03/11 original 74.�����ֽڣ����ڽ�����չ��д��ʱӦȫ����
	 

}PICC_PARA;


#endif

