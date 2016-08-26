#include<string.h>
#include<ctype.h>
#include "commonfunc.h"

void ZTStrCpy(char* dest_str, const char* src_str, int len)
{
	if(len <= 0)
	{
		return;
	}
	strncpy(dest_str,src_str,len);
	dest_str[len-1] = 0;
}

int ZTStrCmp(char* dest_str, const char* src_str)
{
	return strcmp(dest_str,src_str);
}

char ConvertChar(char src)
{
	if(src >= '0' && src <= '9')
	{
		return src - '0';
	}
	if(src >= 'A' && src <= 'F')
	{
		return src - 'A' + 10;
	}
	if(src >= 'a' && src <= 'f')
	{
		return src - 'a' + 10;
	}
	return 0;
}

const char *UrlDecode(const char *url) 
{ 
	if (url == 0)
	{
		return "";
	}

	static char strDecoded[1024 * 1024];
	char *cur_str = strDecoded;
	char ch, ch1, ch2; 

	while((ch = *url++) != 0)
	{
		switch(ch)
		{
		case '+': 
			*cur_str = ' '; 
			break;   
		case '%':
			ch1 = *url++;
			if (ch1 == 0)
			{
				*cur_str = 0;
				return strDecoded; 
			}
			ch2 = *url++;
			if (ch2 == 0)
			{
				*cur_str = 0;
				return strDecoded; 
			}
			ch1 = ConvertChar(ch1);
			ch2 = ConvertChar(ch2);
			ch1 = ch1 * 16 + ch2;

			*cur_str = ch1;
			break; 
		default:
			*cur_str = ch;
		}
		++cur_str;
	}

	*cur_str = 0;
	return   strDecoded; 
} 

const char *UrlEncode(const char *url, int *len_out)
{
	static const int url_out_len = 1024 * 1024;
	static char url_out[url_out_len];
	if (url == 0)
	{
		return "";
	}

	url_out[url_out_len - 1] = 0;

	static const char hex_map[] = "0123456789ABCDEF";

	const char *p = url;
	char c;
	int cur_len = 0;
	while (cur_len < url_out_len && (c = *p++) != '\0')
	{
		if (c == ' ')
		{
			url_out[cur_len++] = '+';
		}
		else if (c < 0 || ( !isalpha(c) && !isdigit(c)))
		{
			if (cur_len >= url_out_len - 2)
			{
				url_out[cur_len] = 0;
				if (len_out != 0) *len_out = cur_len;
				return url_out;
			}

			url_out[cur_len++] = '%';
			url_out[cur_len++] = hex_map[(int)((unsigned char)c / 16)];
			url_out[cur_len++] = hex_map[(int)((unsigned char)c % 16)];
		}
		else
		{
			url_out[cur_len++] = c;
		}
	}

	if (cur_len < url_out_len)
	{
		url_out[cur_len] = 0;
	}
	if (len_out != 0) *len_out = cur_len;

	return url_out;
}


