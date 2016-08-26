#include <memory>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "netprotocalbuff.h"

#define MAX_MSG_SIZE (8*1024*1024)  /// 最大的消息包不超过8M

char g_protocal_buff[MAX_MSG_SIZE];
int	 g_protocal_cur_len;

namespace Protocal
{
	enum
	{
		MT_INVALID = 0,
	};
	class MessageHeader
	{
	public:
		MessageHeader():msg_type(MT_INVALID){}
		MessageHeader(int type):msg_type(type){}

		int	msg_type;
	};
}

void NetProtocalBuff::WriteBegin(int msg_type)
{
	g_protocal_cur_len = sizeof(Protocal::MessageHeader);
	Protocal::MessageHeader *header = (Protocal::MessageHeader*)g_protocal_buff;
	header->msg_type = msg_type;
}

void NetProtocalBuff::WriteFmt(const char* fmt, ...)
{
	va_list argp;
	va_start(argp,fmt);
	while(*fmt)
	{
		char c = *fmt++;
		switch(c)
		{
		case 'i':
			{
				int v = va_arg(argp,int);
				WriteInt(v);
			}
			break;
		case 'I':
			{
				unsigned int v = va_arg(argp,unsigned int);
				WriteUint(v);
			}
			break;
		case 'h':
			{
				short  v = va_arg(argp,short);
				WriteShort(v);
			}
			break;
		case 'H':
			{
				unsigned short v = va_arg(argp,unsigned short);
				WriteUShort(v);
			}
			break;
		case 'c':
			{
				char v = va_arg(argp,int);
				WriteChar(v);
			}
			break;
		case 'C':
			{
				unsigned char v = va_arg(argp,int);
				WriteUChar(v);
			}
			break;
		case 'l':
			{
				long long v = va_arg(argp,long long);
				WriteLL(v);
			}
			break;
		case 'L':
			{
				unsigned long long v = va_arg(argp,unsigned long long);
				WriteULL(v);
			}
			break;
		case 'f':
			{
				float v = va_arg(argp,float);
				WriteFloat(v);
			}
			break;
		case 'd':
			{
				double v = va_arg(argp,double);
				WriteDouble(v);
			}
			break;
		case 's':
			{
				const char* begin = fmt;
				const char* end = begin;
				while('0' <= *end && *end <= '9')++end;
				if(begin == end)
				{
					return;
				}
				char buf[128];
				memset(buf,0,128);
				memcpy(buf,begin,end-begin);
				int total_len = atoi(buf);

				if (total_len <= 0)
				{
					return;
				}
				const char* tmp_str = (const char*)va_arg(argp,char*);
				WriteString(tmp_str,total_len);
				fmt = end;
			}
			break;
		default:
			return;
		}
	}
	va_end(argp);
}

#define PROTOCAL_BUFF_WRITE_VALUE(T)\
	memcpy(g_protocal_buff + g_protocal_cur_len, &v, sizeof(T));\
	g_protocal_cur_len += sizeof(T);\

void NetProtocalBuff::WriteChar(char v)
{
	PROTOCAL_BUFF_WRITE_VALUE(char);
}

void NetProtocalBuff::WriteUChar(unsigned char v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned char);
}

void NetProtocalBuff::WriteShort(short v)
{
	PROTOCAL_BUFF_WRITE_VALUE(short);
}

void NetProtocalBuff::WriteUShort(unsigned short v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned short);
}

void NetProtocalBuff::WriteInt(int v)
{
	PROTOCAL_BUFF_WRITE_VALUE(int);
}

void NetProtocalBuff::WriteUint(unsigned int v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned int);
}

void NetProtocalBuff::WriteLL(long long v)
{
	PROTOCAL_BUFF_WRITE_VALUE(long long);
}

void NetProtocalBuff::WriteULL(unsigned long long v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned long long);
}

void NetProtocalBuff::WriteFloat(float v)
{
	PROTOCAL_BUFF_WRITE_VALUE(float);
}

void NetProtocalBuff::WriteDouble(double v)
{
	PROTOCAL_BUFF_WRITE_VALUE(double);
}

void NetProtocalBuff::WriteString(const char *v, int len)
{
	strncpy(g_protocal_buff + g_protocal_cur_len, v, len);
	g_protocal_cur_len += len;
	g_protocal_buff[g_protocal_cur_len - 1] = 0;
}


const char * NetProtocalBuff::GetProtocalBuff()
{
	return g_protocal_buff;
}

int NetProtocalBuff::GetProtocalBuffLen()
{
	return g_protocal_cur_len;
}





