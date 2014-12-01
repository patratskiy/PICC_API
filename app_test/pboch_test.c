

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
#define IOC_SPI_PBOC_DEBUG   _IOW(SPI_RFID_IOC_MAGIC,1, int )
#define IOCTL_STATUS_IRQ   _IOWR(SPI_RFID_IOC_MAGIC,2,int )

#define AS3911_IRQ_OFF() { ioctl(iAS3911_Fd, IOC_SPI_PBOC_DEBUG, (void*)&cmd);  }
int iAS3911_Fd = -1; 
const char version[]={ "as3911_v1.3_dpth_aj["__TIME__"]\r\n"};
static int AS3911_Spi_open(void)
{
	if (( iAS3911_Fd  =  open( "/dev/spi_rfid", O_RDWR ) )  <  0 ) 
	{
		printf("open %s failed \n", "/dev/spi_rfid");
		return -1;	
	}
	
	return 0;
	
}
int main(int argc, char **argv)
{
	int cmd=0;
	printf(version);
	AS3911_Spi_open();
	AS3911_IRQ_OFF();
//	while(1);
}


