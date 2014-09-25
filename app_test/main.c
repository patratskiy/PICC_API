	
#include <stdio.h>
#include <fcntl.h> 
#include <stdio.h>
#include <errno.h> 
#include <fcntl.h>
#include <termio.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>


#include "../Library/picc_api_quckv4.h"
#include "../Library/posapi_t100.h"
#include "../Library/posapi.h"
#include "../Library/Ctype.h"


void main()
{
	char tmpc; 
	uchar timeout;
	APDU_SEND as; 
	APDU_RESP ar; 

	tmpc=PiccOpen(); 
	if(tmpc)return 1; 

	while(1) 
	{ 
		tmpc=PiccDetect(0, NULL, NULL, NULL, NULL); 
		if(!tmpc)break;//Card has been detected successfully 
		if(tmpc!=3) 
		{ 
			  printf("FAILED TO DETECT CARD:%02X",tmpc); 
			//Beep(); 
			// DelayMs(500); 
			// ScrClrLine(2,3); 
			// ScrPrint(0,2,1, ¡°PLS WAVE CARD¡­¡±); 
		} 
		
	}//while(1), card detect loop 
	
	printf("successfully  DETECT ");  
	// ScrPrint(0,2,0x01,"SELECT PPSE..."); 
	as.Command[0]=0x00;    
	as.Command[1]=0xa4;    
	as.Command[2]=0x04;  //0x00--HANDLE,0x04-FNAME 
	as.Command[3]=0x00;   
	as.Lc=14; //  f o r HANDLE,14 for FNAME 
	as.Le=256;             
	memcpy(as.DataIn,"\x3f\x00",2); 
	strcpy(as.DataIn,"1PAY.SYS.DDF01");//as card 
	//strcpy(as.DataIn,"2PAY.SYS.DDF01");//as standard 
	memset(ar.DataOut,0x00,512); 
	 
	tmpc = PiccIsoCommand(0,&as,&ar); 
	if(tmpc) 
	{ 
	    printf("FAILED TO SELECT PPSE:%02X",tmpc); 
		return 3; 
	} 
	while(1) 
	{ 
		tmpc=PiccRemove('R',0); 
		if(!tmpc)break; 
		if(tmpc>=3) 
		{ 
			 // Beep( ); 
			printf("PLS REMOVE CARD"); 
			//delay(500); 
		} 
	}
	
	PiccClose(); 
	return 0; 

}
