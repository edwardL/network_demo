#include "tinyxml_demo.h"
#include <iostream>
#include "configcommon.h"


TinyXmlDemo::TinyXmlDemo(const string configname)
{
	Init(configname);
}

bool TinyXmlDemo::Init(const string configname)
{
	TiXmlDocument m_document;
	if(!m_document.LoadFile(configname.c_str()))
	{
		printf("%s : load config file error",configname.c_str());
		return false;
	}
	TiXmlElement *RootElement = m_document.RootElement();
	if(!RootElement)
	{
		printf("%s xml root node error");
		return false;
	}

	

	for(TiXmlElement* element = RootElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		string elementName = element->Value();
		const char* attr;
		attr = element->Attribute("priority");
		if(strcmp(attr,"1") == 0)
		{
			TiXmlElement* e1 = element->FirstChildElement("bold");
			TiXmlNode* e2 = e1->FirstChild();
			std::cout <<"priority=1\t" << e2->ToText()->Value()<<std::endl;
		}
		else if(strcmp(attr,"2") == 0)
		{
			TiXmlNode* e1 = element->FirstChild();
			std::cout << "priority=2\t" << e1->ToText()->Value() << std::endl;
		}
	}
	m_document.Clear();
	
	printf("=-=");
	return true;
}