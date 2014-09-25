

#include "picc_api_quckv4.h"
#include "posapi_t100.h"
#include "posapi.h"
#include "Ctype.h"



uchar PiccOpen(void)
{
	return 1;
}

uchar PiccSetup (uchar mode, PICC_PARA *picc_para)
{
	return 1;
}

uchar PiccDetect(uchar Mode,uchar *CardType,uchar *SerialInfo,uchar *CID,uchar *Other)
{
	return 1;
}

uchar PiccIsoCommand(uchar cid,APDU_SEND *ApduSend,APDU_RESP *ApduRecv)
{
	return 1;
}

uchar PiccRemove(uchar mode,uchar cid)
{
	return 1;
}

void  PiccClose(void)
{
	return ;
}

