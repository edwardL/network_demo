#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

/// ����һЩ���õĺ���ʵ��

void ZTStrCpy(char* dest_str, const char* src_str, int len);
int	 ZTStrCmp(char* dest_str, const char* src_str);

//��һЩд�ļ����ַ���ʱ�õ��ı�����뺯���� Ԥ������һЩǱ�ڷǷ��ַ�
const char* UrlDecode(const char* url);
const char* UrlEncode(const char* url, int * len_out = 0); /// ���롣
	


#endif