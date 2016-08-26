#include "netprotocalbufftest.h"
#include <stdio.h>
#include <stdlib.h>
NetProtocalBuffTest::NetProtocalBuffTest()
{
	NetProtocalBuff::WriteBegin(1500);
	NetProtocalBuff::WriteInt(1500);
	printf("%s",(char*)NetProtocalBuff::GetProtocalBuff());
}