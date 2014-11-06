	
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

/*
#include "../Library/picc_api_quckv4.h"
#include "../Library/posapi_t100.h"
#include "../Library/posapi.h"
#include "../Library/Ctype.h"

*/
#include "picc_api_quckv4.h"
#include "posapi_t100.h"
#include "posapi.h"
#include "Ctype.h"

EmvPicc_t detect_picc;

int main()
{
	char tmpc; 
	int i;
	uchar timeout;
	APDU_SEND as; 
	APDU_RESP ar; 
	PICC_PARA picc_para; 
	int count =0;
again:
	tmpc=PiccOpen(); 
   
	memset(&picc_para,0x00,sizeof(PICC_PARA)); 
	picc_para.b_modulate_w=1; 
	picc_para.b_modulate_val=3; 
	picc_para.card_buffer_w=1; 
	picc_para.card_buffer_val=64; 
	tmpc=PiccSetup('w', &picc_para); 
	if(tmpc) return 2; 	

	timeout=255;
	
	while(1) 
	{ 
		tmpc=PiccDetect(0, &detect_picc.cardType, detect_picc.uid, &detect_picc.uidLength, &timeout); 
		if(!tmpc)
		{
			break;//Card has been detected successfully 
		}
		
	}//while(1), card detect loop 

	printf("Successfully  detect card!\n");  
	printf("UID [%d] :",detect_picc.uidLength);  

	for(i=0;i<detect_picc.uidLength;i++)
	{
		printf(" %02x",detect_picc.uid[i]);

	}
	printf("\n");	

	printf("Card type : 0x%x\n",detect_picc.cardType);  

	if ((detect_picc.cardType == 'b' ) || (detect_picc.cardType == 'B' ))
		printf("B card found!\n");  

	if ((detect_picc.cardType == 'a' ) || (detect_picc.cardType == 'A' ))
		printf("A card found!\n");  	

	printf("\n\n----- select 1PAY.SYS.DDF01 --------\n");

	//static const u8 emvSelectppseApdu[] = { 0x00, 0xA4, 0x04, 0x00, 0x0E
  //  , '2', 'P', 'A', 'Y', '.', 'S', 'Y', 'S', '.', 'D', 'D', 'F', '0', '1', 0x00 };
	as.Command[0]=0x00;    
	as.Command[1]=0xa4;    
	as.Command[2]=0x04;  //0x00--HANDLE,0x04-FNAME 
	as.Command[3]=0x00;   
	as.Lc=14; //  f o r HANDLE,14 for FNAME 
	as.Le=256;             
	//strcpy(as.DataIn,"1PAY.SYS.DDF01");//as card 
	strcpy(as.DataIn,"2PAY.SYS.DDF01");//as standard 
	memset(ar.DataOut,0x00,512); 
	 
	tmpc = PiccIsoCommand(0,&as,&ar); 

	if(tmpc) 
	{ 
	  	printf("PiccIsoCommand Failed ,error :%02X",tmpc); 
		return -1;
	} 
	
	if ( ar.LenOut > 0)
	{	
		printf("received  data : %d bytes [0x", ar.LenOut);
		
		for (i=0;i<ar.LenOut;i++)
			printf("%02x", ar.DataOut[i]);      

		printf("]\n");	
	}		

	printf("the status of Select 1PAY.SYS.DDF01: 0x%02x%02x\n", ar.SWA, ar.SWB);
	
	printf("\n\n----- select MF --------\n");
	memset(as.DataIn,0x00,512); 
	as.Command[0]=0x00;    
	as.Command[1]=0xa4;    
	as.Command[2]=0x04;  //0x00--HANDLE,0x04-FNAME 
	as.Command[3]=0x00;   
	as.Lc=2; //  f o r HANDLE,14 for FNAME 
	as.Le=256;             
	memcpy(as.DataIn,"\x3f\x00",2); 
	
	memset(ar.DataOut,0x00,512); 	   
 
	tmpc = PiccIsoCommand(0,&as,&ar); 

	if(tmpc) 
	{ 
	  	printf("PiccIsoCommand Failed ,error :%02X",tmpc); 
		return -1;
	} 
	
	if ( ar.LenOut > 0)
	{	
		printf("received  data : %d bytes [0x", ar.LenOut);
		
		for (i=0;i<ar.LenOut;i++)
			printf("%02x", ar.DataOut[i]);      

		printf("]\n");	
	}		

	printf("the status of Select MF: 0x%02x%02x\n", ar.SWA, ar.SWB);

	printf("\n----- get chanllenge --------\n");
	memset(as.DataIn,0x00,512); 
	as.Command[0]=0x00;    
	as.Command[1]=0x84;    
	as.Command[2]=0x00;  //0x00--HANDLE,0x04-FNAME 
	as.Command[3]=0x00;   
	as.Lc=0; //  f o r HANDLE,14 for FNAME 
	as.Le=8;             
	memcpy(as.DataIn,"\x3f\x00",2); 
	
	memset(ar.DataOut,0x00,512); 	   
 
	tmpc = PiccIsoCommand(0,&as,&ar); 

	if(tmpc) 
	{ 
	  	printf("PiccIsoCommand Failed ,error :%02X",tmpc); 
		return -1;
	} 
	
	if ( ar.LenOut > 0)
	{	
		printf("received  data : %d bytes [0x", ar.LenOut);
		
		for (i=0;i<ar.LenOut;i++)
			printf("%02x", ar.DataOut[i]);      

		printf("]\n");	
	}		

	printf("the status of get chanllenge: 0x%02x%02x\n", ar.SWA, ar.SWB);	
	
	while(1) 
	{ 
		tmpc=PiccRemove('R',0); 
		if(!tmpc)break; 
		
		if(tmpc  != 0) 
		{ 
#if 1				 
			printf("REMOVE CARD fail "); 
			//delay(500); 
#endif				
		} 
	}
	
	PiccClose(); 
	if(count++ <10)
	{
		goto again;
	}
	return 0; 
}
