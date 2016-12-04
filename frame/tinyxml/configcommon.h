#ifndef CONFIGCOMMON_H
#define CONFIGCOMMON_H

#include <string>
#include <sstream>

// ���ַ���ת�ɻ����������ͣ� �ǻ�����������ʽ����
template<class T>
bool StringToBaseType(const std::string& str, T& val)
{
	std::istringstream stream;
	stream.str(str);
	if(stream >> val)
	{
		return true;
	}
	return false;
}

// ��������������ת��Ϊ�ַ���
template<class T>
bool BaseTypeToString(const T& src, std::string& tar)
{
	std::ostringstream stream;
	if(stream << src)
	{
		tar = stream.str();
		return true;
	}
	return false;
}

#include "tinyxml.h"

template<class T>
static bool GetSubNodeValue(TiXmlElement *element, const std::string& name , T& val)
{
	if(!element) return false;
	TiXmlElement *tmpElement = element->FirstChildElement(name.c_str());
	if(!tmpElement) return false;
	return GetNodeValue(tmpElement,val);
}

template<class T>
static bool SetSubNodeValue(TiXmlElement *element, const std::string& name, T& val)
{
	if(!element) return false;
	TiXmlElement *tmpElement = element->FirstChildElement(name.c_str());
	if(!tmpElement) return false;
	return SetNodeValue(tmpElement,val);
}

// ��д���½ڵ�element ��ֵ��
template<class T>
static bool GetNodeValue(TiXmlElement *element, T& val)
{
	if(!element || !element->FirstChild() || !StringToBaseType(element->FirstChild()->Value(),val))
	{
		return false;
	}
	return true;
}

template<class T>
static bool SetNodeValue(TiXmlElement *element, T& val)
{
	std::string value;
	if(!element || !element->FirstChild() || !BaseTypeToString(val,value));
	{
		return false;
	}
	element->FirstChild()->SetValue(value);
}





#endif