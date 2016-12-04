#ifndef TINYXML_H
#define TINYXML_H

#include "tinyxml.h"
#include <string>
using namespace std;

class TinyXmlDemo
{
public:
	TinyXmlDemo(const string configname);
	bool Init(const string configname);
};


#endif