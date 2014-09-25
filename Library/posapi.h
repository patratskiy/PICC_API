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
	// 发散该密钥的源密钥的密钥类型，PED_GMK,PED_TMK,PED_TPK,PED_TAK,PED_TDK, 不得低于ucDstKeyType所在的密钥级别
	uchar ucSrcKeyType; 
	// 发散该密钥的源密钥索引，索引一般从1开始，如果该变量为0，则表示这个密钥的写入是明文形式
	uchar ucSrcKeyIdx; 
	// 目的密钥的密钥类型，PED_GMK,PED_TMK,PED_TPK,PED_TAK,PED_TDK
	uchar ucDstKeyType;
	// 目的密钥索引
	uchar ucDstKeyIdx;
	// 目的密钥长度，8,16,24
	int iDstKeyLen; 
	// 写入密钥的内容
	uchar aucDstKeyValue[24]; 
}ST_KEY_INFO;

typedef struct
{
  int iCheckMode;
  uchar aucCheckBuf[128];
}ST_KCV_INFO;

/**
AES 密钥信息，用于写入AES 密钥信息时传入AES 密钥的相关信息,
与PedWriteKey()函数共用ST_KCV_INFO数据结构。
*/
typedef struct
{
	/** 发散该密钥的源密钥的密钥类型，
	PED_TLK,PED_TMK,PED_TPK,PED_TAK,PED_TDK, PED_TAESK, 
	不得低于ucDstKeyType所在的密钥级别*/
	uchar ucSrcKeyType;
	/** 发散该密钥的源密钥索引，
	索引一般从1开始，如果该变量为0，
	则表示这个密钥的写入是明文形式*/
	uchar ucSrcKeyIdx;
	/** 目的密钥的密钥类型: PED_TAESK */
	uchar ucDstKeyType;
	/*目的密钥索引*/
	uchar ucDstKeyIdx;
	/**目的密钥长度，16,24,32 */
	int iDstKeyLen;
	/**写入密钥的内容 */
	uchar aucDstKeyValue[32];
}ST_AES_KEY_INFO;

#define PED_BKLK  0x01  //BKLK
#define PED_TMK   0x02 //TMK
#define PED_TPK   0x03 //PIN Key
#define PED_TAK	  0x04 //MAC Key
#define PED_TDK   0x05 //DES Key
#define	PED_DUKPT 0X06
#define	PED_TPAK  0X07//(用于TPK/TAK混用的模式)


//define密钥下载命令码定义
#define PED_DOWNLOAD_CMD_TYPE 0X00
// 读取版本
#define PED_CMD_GETVER 0x00
// 请求系统敏感服务授权并读取随机数
#define PED_CMD_REQ_SYS_SSA	0X01
// 回送随机数密文并获取
#define PED_CMD_GET_TEK 0X02
// 格式化ped
#define PED_CMD_FORMAT_PED 0X03//
 // 写入MKSK 密钥
#define PED_CMD_WRITEKEY 0x04//
// 写入TIK
#define PED_CMD_WRITETIK 0x05//
// 设置密钥标签
#define PED_CMD_SETKEYTAG 0X06//
// PED下载完成
#define PED_CMD_DOWNLOAD_COMPLETE 0X07	
 // 读取终端序列号
#define PED_CMD_READ_SN 0X08

// PEDAPI 错误码起始值
#define PED_RET_ERR_START -300
// PEDAPI 错误码结束值
#define PED_RET_ERR_END	-500
// PED函数返回正确
#define PED_RET_OK 0  
// 密钥不存在
#define PED_RET_ERR_NO_KEY (PED_RET_ERR_START-1)  
// 密钥索引错，参数索引不在范围内
#define PED_RET_ERR_KEYIDX_ERR     (PED_RET_ERR_START-2)  
// 密钥写入时，源密钥的层次比目的密钥低
#define PED_RET_ERR_DERIVE_ERR	   (PED_RET_ERR_START-3)  
// 密钥验证失败
#define PED_RET_ERR_CHECK_KEY_FAIL (PED_RET_ERR_START-4)  
// 没输入PIN
#define PED_RET_ERR_NO_PIN_INPUT   (PED_RET_ERR_START-5) 
// 取消输入PIN
#define PED_RET_ERR_INPUT_CANCEL   (PED_RET_ERR_START-6) 
// 函数调用小于最小间隔时间
#define PED_RET_ERR_WAIT_INTERVAL  (PED_RET_ERR_START-7) 
 // KCV模式错，不支持
#define PED_RET_ERR_CHECK_MODE_ERR (PED_RET_ERR_START-8) 
// 无权使用该密钥，当出现密钥标签不对，或者写入密钥时,
// 源密钥类型的值大于目的密钥类型，都会返回该密钥
#define PED_RET_ERR_NO_RIGHT_USE   (PED_RET_ERR_START-9) 
// 密钥类型错
#define PED_RET_ERR_KEY_TYPE_ERR   (PED_RET_ERR_START-10)  
// 期望PIN的长度字符串错
#define PED_RET_ERR_EXPLEN_ERR     (PED_RET_ERR_START-11)  
// 目的密钥索引错，不在范围内
#define PED_RET_ERR_DSTKEY_IDX_ERR (PED_RET_ERR_START-12)  
// 源密钥索引错，不在范围内
#define PED_RET_ERR_SRCKEY_IDX_ERR (PED_RET_ERR_START-13)  
// 密钥长度错
#define PED_RET_ERR_KEY_LEN_ERR		(PED_RET_ERR_START-14) 
// 输入PIN超时
#define PED_RET_ERR_INPUT_TIMEOUT  (PED_RET_ERR_START-15) 
// IC卡不存在
#define PED_RET_ERR_NO_ICC          (PED_RET_ERR_START-16)
// IC卡未初始化
#define PED_RET_ERR_ICC_NO_INIT    (PED_RET_ERR_START-17) 
// DUKPT组索引号错
#define PED_RET_ERR_GROUP_IDX_ERR (PED_RET_ERR_START-18)
// 指针参数非法为空
#define PED_RET_ERR_PARAM_PTR_NULL    (PED_RET_ERR_START-19)
// PED已锁
#define PED_RET_ERR_LOCKED (PED_RET_ERR_START-20)		
// PED通用错误
#define PED_RET_ERROR (PED_RET_ERR_START-21)		
// 没有空闲的缓冲
#define PED_RET_ERR_NOMORE_BUF (PED_RET_ERR_START-22)	
// 需要取得高级权限
#define PED_RET_ERR_NEED_ADMIN (PED_RET_ERR_START-23)	
// DUKPT已经溢出
#define PED_RET_ERR_DUKPT_OVERFLOW (PED_RET_ERR_START-24)
// KCV 校验失败
#define PED_RET_ERR_KCV_CHECK_FAIL (PED_RET_ERR_START-25)
// 写入密钥时，源密钥id的类型不和源密钥类型不匹配
#define PED_RET_ERR_SRCKEY_TYPE_ERR	(PED_RET_ERR_START-26)
// 命令不支持
#define PED_RET_ERR_UNSPT_CMD  (PED_RET_ERR_START-27)
// 通讯错误
#define PED_RET_ERR_COMM_ERR (PED_RET_ERR_START-28)
// 没有用户认证公钥
#define PED_RET_ERR_NO_UAPUK (PED_RET_ERR_START-29)
// 取系统敏感服务失败
#define PED_RET_ERR_ADMIN_ERR (PED_RET_ERR_START-30)
// PED处于下载非激活状态
#define	PED_RET_ERR_DOWNLOAD_INACTIVE (PED_RET_ERR_START-31)

//KCV 奇校验失败
#define PED_RET_ERR_KCV_ODD_CHECK_FAIL (PED_RET_ERR_START-32)
//读取PED数据失败
#define PED_RET_ERR_PED_DATA_RW_FAIL (PED_RET_ERR_START-33)
//卡操作错误(脱机明文、密文密码验证)
#define PED_RET_ERR_ICC_CMD_ERR      (PED_RET_ERR_START-34)
//用户按CLEAR键退出输入PIN
#define PED_RET_ERR_INPUT_CLEAR		(PED_RET_ERR_START-39)
//PED存储空间不足
#define PED_RET_ERR_NO_FREE_FLASH	(PED_RET_ERR_START-43)
//DUKPT KSN需要先加1
#define PED_RET_ERR_DUKPT_NEED_INC_KSN	(PED_RET_ERR_START-44)
//KCV MODE错误
#define PED_RET_ERR_KCV_MODE_ERR	(PED_RET_ERR_START-45)
//NO KCV
#define PED_RET_ERR_DUKPT_NO_KCV   (PED_RET_ERR_START-46)
//按FN/ATM4键取消PIN输入
#define PED_RET_ERR_PIN_BYPASS_BYFUNKEY		(PED_RET_ERR_START-47)
//数据MAC校验错
#define PED_RET_ERR_MAC_ERR			(PED_RET_ERR_START-48)
//数据CRC校验错
#define PED_RET_ERR_CRC_ERR			(PED_RET_ERR_START-49)

//=============================================================================
// structure for ped operation 
// nicm add 2008-07-25 end
//=============================================================================

//----------------------------------------------------------
// nicm add for new wireless module begin
//----------------------------------------------------------

#define WL_RET_ERR_PORTINUSE -201 // 模块口被占用
#define WL_RET_ERR_NORSP -202 // 模块没有应答
#define WL_RET_ERR_RSPERR -203 // 模块应答错误
#define WL_RET_ERR_PORTNOOPEN -204 // 模块串口没有打开
#define WL_RET_ERR_NEEDPIN -205	// 需要PIN码
#define WL_RET_ERR_NEEDPUK -206	// 需要PUK解PIN码
#define WL_RET_ERR_PARAMER -207	// 参数错误
#define WL_RET_ERR_ERRPIN -208 // 密码错误
#define WL_RET_ERR_NOSIM -209 // 没有插入SIM卡
#define WL_RET_ERR_NOTYPE -210 // 不支持的类型
#define WL_RET_ERR_NOREG -211 // 网络没有注册
#define WL_RET_ERR_INIT_ONCE -212 // 模块已初始化
#define WL_RET_ERR_LINEOFF -214	// 连接断开
#define WL_RET_ERR_TIMEOUT -216	// 超时
#define WL_RET_ERR_REGING -222 // 网络注册中
#define WL_RET_ERR_PORTCLOSE -223 // 关闭串口出错
#define WL_RET_ERR_MODEVER -225	// 错误的模块版本
#define WL_RET_ERR_DIALING -226	// 拨号中  
#define WL_RET_ERR_ONHOOK -227 // 关机中
#define WL_RET_ERR_PPP_BRK -228	// 发现PPP断开
#define WL_RET_ERR_NOSIG -229 // 网络无信号
#define WL_RET_ERR_POWEROFF -230 // 模块已下电
#define WL_RET_ERR_BUSY -231 // 模块忙
#define WL_RET_ERR_OTHER -300 // 其他未知错误

#define	NET_OK               0  // 无错误，正常
#define	NET_ERR_MEM     	 -1  // 内存不够
#define	NET_ERR_BUF     	 -2  // 缓冲区错误
#define	NET_ERR_ABRT    	 -3  // 试图建立连接失败
#define	NET_ERR_RST     	 -4  // 连接被对方复位（收到对方的Reset）
#define	NET_ERR_CLSD    	 -5  // 连接已关闭
#define	NET_ERR_CONN    	 -6  // 连接未成功建立
#define	NET_ERR_VAL     	 -7  // 错误变量
#define	NET_ERR_ARG     	 -8  // 错误参数
#define	NET_ERR_RTE     	 -9  // 错误路由(route)
#define	NET_ERR_USE     	 -10 // 地址、端口使用中
#define	NET_ERR_IF      	 -11 // 底层硬件错误
#define	NET_ERR_ISCONN  	 -12 // 连接已建立
#define	NET_ERR_TIMEOUT 	 -13 // 超时
#define	NET_ERR_AGAIN   	 -14 // 请求资源不存在，请重试
#define	NET_ERR_EXIST   	 -15 // 已存在
#define	NET_ERR_SYS     	 -16 // 系统不支持
#define	NET_ERR_PASSWD  	 -17 // 错误密码
#define	NET_ERR_MODEM   	 -18 // 拨号失败
#define	NET_ERR_LINKDOWN   	 -19 // 数据链路已断开，请重新拨号
#define	NET_ERR_LOGOUT	   -20 // Logout
#define	NET_ERR_PPP	       -21 // PPP断开
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
	uchar card_type_check_w; // 卡片类型检查写入允许：1--允许，其它值--不允许，主要用于避免因卡片不规范引起的问题
	
	uchar card_type_check_val; // 0-检查卡片类型，其他－不检查卡片类型(默认为检查卡片类型)
	
	//uchar reserved[92];  //保留字节，用于将来扩展；写入时应全清零
	
	//2009-10-30	
	uchar card_RxThreshold_w; // 卡片类型检查写入允许：1--允许，其它值--不允许，主要用于避免因卡片不规范引起的问题
	
	uchar card_RxThreshold_val;//卡片接收灵敏度
		
	//2009-11-20

     uchar f_modulate_w; // felica调制深度写入允许

     uchar f_modulate_val;//felica调制深度

	 //add by wls 2011.05.17
	 unsigned char a_modulate_w; // A卡调制指数写入允许：1--允许，其它值—不允许
	 unsigned char a_modulate_val; // A卡调制指数控制变量，有效范围0~63,超出时视为63
	 
		//add by wls 2011.05.17
	 unsigned char a_card_RxThreshold_w; //接收灵敏度检查写入允许：1--允许，其它值--不允许
	 unsigned char a_card_RxThreshold_val;//A卡接收灵敏度
	 
	 //add by liubo 2011.10.25, 针对A,B和C卡的天线增益
	 unsigned char a_card_antenna_gain_w;
	 unsigned char a_card_antenna_gain_val;
	 
	 unsigned char b_card_antenna_gain_w;
	 unsigned char b_card_antenna_gain_val;
	 
	 unsigned char f_card_antenna_gain_w;
	 unsigned char f_card_antenna_gain_val;
	 
	 //added by liubo 2011.10.25，针对Felica的接收灵敏度
	 unsigned char f_card_RxThreshold_w;
	 unsigned char f_card_RxThreshold_val;
	 
	/* add by wanls 2012.08.14*/
	unsigned char f_conduct_w;  
	unsigned char f_conduct_val; 
	
	/* add by nt for paypass 3.0 test 2013/03/11 */
	unsigned char user_control_w;
	unsigned char user_control_key_val;
	
	unsigned char reserved[72]; //modify by nt 2013/03/11 original 74.保留字节，用于将来扩展；写入时应全清零
	 

}PICC_PARA;


#endif

