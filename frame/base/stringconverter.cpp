#include "stringconverter.h"
#include "stringutil.h"
#include <sstream>
using namespace std;


string StringConverter::toString(float val, unsigned short precision /* = 6 */, unsigned short width /* = 0 */, char fill /* =  */, std::ios::fmtflags flags /* = std::ios::fmtflags */)
{
#ifndef WIN32
	static char buffer[128];
	int n = snprintf(buffer,128,"%f",val);
	return string(buffer,n);
#else
	stringstream stream;
	stream.precision(precision);
	stream.width(width);
	stream.fill(fill);
	if(flags)
		stream.setf(flags);
	stream << val;
	return stream.str();
#endif
}

string StringConverter::toString(int val, unsigned short precision /* = 6 */, unsigned short width /* = 0 */, char fill /* =  */, std::ios::fmtflags flags /* = std::ios::fmtflags */)
{
	stringstream stream;
	stream.width(width);
	stream.fill(fill);
	if(flags)
		stream.setf(flags);
	stream << val;
	return stream.str();
}

string StringConverter::toString(unsigned long val, unsigned short precision /* = 6 */, unsigned short width /* = 0 */, char fill /* =  */, std::ios::fmtflags flags /* = std::ios::fmtflags */)
{
	stringstream stream;
	stream.width(width);
	stream.fill(fill);
	if(flags)
		stream.setf(flags);
	stream << val;
	return stream.str();
}

string StringConverter::toString(bool val)
{
	if(val)
		return "true";
	return false;
}

string StringConverter::toString(const StringVector& val)
{
	stringstream stream;
	StringVector::const_iterator i,ibegin,iend;
	ibegin = val.begin();
	iend   = val.end();
	for(i = ibegin; i != iend; ++i)
	{
		if(i != ibegin)
			stream << " ";
		stream << *i;
	}
	return stream.str();
}

float StringConverter::parseFloat(const string&val, float defaultVal)
{
	float ret = 0;
#ifndef WIN32	
	int n = sscanf(val.c_str(),"%f",&ret);
	if(n == 0)
	{
		int ret2 = 0;
		n = sscanf(val.c_str(),"%d",&ret2);
		if(n == 1)
			ret = (float)ret2;
	}
#else
	stringstream str(val);
	ret = defaultVal;
	if(!(str >> ret))
		return defaultVal;
#endif
	return ret;
}

int StringConverter::parseInt(const string& val, int defaultVal)
{
	stringstream stream(val);
	int ret = defaultVal;
	if(!(stream >> ret))
		return defaultVal;
	return ret;
}

unsigned StringConverter::parseUnsignedInt(const string& val, unsigned int defaultVal)
{
	stringstream stream(val);
	unsigned int ret = defaultVal;
	if(!(stream >> ret))
		return defaultVal;
	return ret;
}

long StringConverter::parseLong(const string& val, long defaultVal)
{
	stringstream stream(val);
	long ret = defaultVal;
	if(!(stream >> ret))
		return defaultVal;
	return ret;
}

unsigned long StringConverter::parseUnsignedLong(const string&val, unsigned long defaultVal)
{
	stringstream stream(val);
	unsigned long ret = defaultVal;
	if(!(stream >> ret))
		return defaultVal;
	return ret;
}

bool StringConverter::parseBool(const string& val, bool defaultVal)
{
	if(StringUtil::startsWith(val,"true") ||  StringUtil::startsWith(val,"yes"))
		return true;
	else if(StringUtil::startsWith(val,"false") || StringUtil::startsWith(val,"no"))
		return false;
	return defaultVal;
}