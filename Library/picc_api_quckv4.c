

#include "picc_api_quckv4.h"
#include "posapi_t100.h"
#include "posapi.h"
#include "Ctype.h"
#include <stdio.h>
#include <fcntl.h> 
#include <stdio.h>
#include <errno.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <termio.h>
#include <unistd.h> 
#include <string.h>
#include <math.h>
#define SPI_RFID_IOC_MAGIC 	               'w'
#define IOC_SPI_PICC_SETUP  _IOWR(SPI_RFID_IOC_MAGIC, 1, int )
#define IOC_SPI_PICC_DETECT _IOWR(SPI_RFID_IOC_MAGIC, 2, int )
#define IOC_SPI_PICC_APDU   _IOWR(SPI_RFID_IOC_MAGIC, 3, int )
#define IOC_SPI_PICC_REMOVE _IOWR(SPI_RFID_IOC_MAGIC, 4, int )
#define IOC_SPI_PICC_OPEN   _IOWR(SPI_RFID_IOC_MAGIC, 5, int )
#define IOC_SPI_PICC_CLOSE  _IOWR(SPI_RFID_IOC_MAGIC, 6, int )

#define PRINTF (!debug_on) ? : printf

#define AS3911_IRQ_OFF() { ioctl(iAS3911_Fd, IOCTL_ENABLE_IRQ, (void*)&cmd);  }



int iAS3911_Fd = -1; 
uchar debug_on =1;
//const char version[]={ "as3911_v1.3_dpth_aj["__TIME__"]\r\n"};


uchar PiccOpen(void)
{
	if(iAS3911_Fd == -1)
	{
		if (( iAS3911_Fd  =  open( "/dev/spi_rfid", O_RDWR ) )  <  0 ) 
		{
			PRINTF("open %s failed 2\n", "/dev/spi_rfid");
			return 0xff;	
		}	
		ioctl(iAS3911_Fd, IOC_SPI_PICC_OPEN, NULL);
	}
	else
	{
		PRINTF("warning:have alreadly opened it \n");
		
	}
	
	PRINTF("PiccOpen:\n");
	return 0;
}

uchar PiccSetup (uchar mode, PICC_PARA *picc_para)
{
	ioctl(iAS3911_Fd, IOC_SPI_PICC_SETUP, (void*)picc_para);
	return 0;
}

uchar PiccDetect(uchar Mode,uchar *CardType,uchar *SerialInfo,uchar *Len_Serical,uchar *Other)
{
	//int i;
	uchar data_buf[20];

	data_buf[0]=*Other;
	if(0 != ioctl(iAS3911_Fd, IOC_SPI_PICC_DETECT, (void*)data_buf))
	{
		return 2;
	}
	*CardType=data_buf[11];
	*Len_Serical=data_buf[10];
#if 0	
	PRINTF("PiccDetect:\n");

	for(i=0;i<12;i++)
	{
		PRINTF(" %02x",data_buf[i]);

	}
	PRINTF(" \n");
	
#endif
	return 0;
}


typedef struct{
   	unsigned int Len;
   	unsigned char  DataIn[600];


}MESSAGE_BOX;

uchar PiccIsoCommand(uchar cid,APDU_SEND *ApduSend,APDU_RESP *ApduRecv)
{
	unsigned int i;
	
	MESSAGE_BOX buf;
	memset(&buf,0,sizeof(buf));
	buf.Len=ApduSend->Lc+5;
	memcpy(buf.DataIn,ApduSend->Command,5);
	memcpy(buf.DataIn+5,ApduSend->DataIn,ApduSend->Lc);
	if(0 != ioctl(iAS3911_Fd, IOC_SPI_PICC_APDU, (void*)&buf) )
	{
		return 2;
	}

	ApduRecv->LenOut=(unsigned char)buf.Len -2;
	ApduRecv->SWA=buf.DataIn[0];
	ApduRecv->SWB=buf.DataIn[1];
	memcpy(ApduRecv->DataOut,buf.DataIn+2,ApduRecv->LenOut);
#if 0	
	PRINTF("PiccIsoCommand:\n");

	for(i=0;i<buf.Len;i++)
	{
		PRINTF(" %02x",buf.DataIn[i]);

	}
	PRINTF(" \n");
	
#endif	
	//memcpy(ApduRecv.DataOut,ApduSend.);
	return 0;
}

uchar PiccRemove(uchar mode,uchar cid)
{

	return ioctl(iAS3911_Fd, IOC_SPI_PICC_REMOVE, &mode);

}

void  PiccClose(void)
{
	
	ioctl(iAS3911_Fd, IOC_SPI_PICC_CLOSE, NULL);
	close(iAS3911_Fd);
	iAS3911_Fd=-1;
	return ;
}

