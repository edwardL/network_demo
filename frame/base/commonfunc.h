#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

/// 定义一些公用的函数实现

void ZTStrCpy(char* dest_str, const char* src_str, int len);
int	 ZTStrCmp(char* dest_str, const char* src_str);

//对一些写文件的字符串时用到的编码解码函数， 预防出现一些潜在非法字符
const char* UrlDecode(const char* url);
const char* UrlEncode(const char* url, int * len_out = 0); /// 编码。
	


#endif