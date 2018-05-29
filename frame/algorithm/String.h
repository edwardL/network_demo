#include <stdio.h>
http://www.cnblogs.com/polly333/p/4739037.html

//* 暴力匹配算法
int bf(const char* text, const char *find)
{
	if(*text == '\0' || *find == '\0')
	{
		return -1;
	}
	int find_len = strlen(find);
	int text_len = strlen(text);
	if(text_len < find_len)
	{
		return -1;
	}
	// 去除const 属性
	char *s = const_cast<char*>(text);
	char *p = s;
	char *q = const_cast<char*>(find);

	// 执行BF算法
	while(*p != '\0')
	{
		// 匹配成功
		if(*p == *q)
		{
			p++;
			q++;
		}
		else
		{
			s++;
			p = s;
			q = const_cast<char*>(find);
		}
		// 执行成功，返回位置
		if(*q == '\0')
		{
			return (p - text) - (q - find);
		}
	}
	return -1;
}