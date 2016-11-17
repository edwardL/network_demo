#include "stringutil.h"
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

void StringUtil::trim(string& str, bool left /* = true */, bool right /* = true */)
{
	 static const string delims = "\t\r";
	 if(right)
		 str.erase(str.find_last_not_of(delims) + 1);
	 if(left)
		 str.erase(str.find_first_not_of(delims));
}

vector<string> StringUtil::split(string& str, const string& delims/* = */,unsigned int maxSplits /* = 0 */, bool preserveDelims /* = false */)
{
	vector<string> ret;
	ret.reserve(maxSplits ? maxSplits + 1 : 10);

	unsigned int numSplits = 0;
	// use stl methods
	size_t start,pos;
	start = 0;
	do 
	{
		pos = str.find_first_of(delims,start);
		if(pos == start)
		{
			// do nothing
			start = pos + 1;
		}
		else if(pos == string::npos || (maxSplits && numSplits == maxSplits))
		{
			ret.push_back(str.substr(start));
			break;
		}
		else
		{
			ret.push_back(str.substr(start,pos-start));
			if(preserveDelims)
			{
				size_t delimStart = pos,delimPos;
				delimPos = str.find_first_not_of(delims,delimStart);
				if(delimPos == string::npos)
				{
					ret.push_back(str.substr(delimStart));
				}
				else
				{
					ret.push_back(str.substr(delimStart,delimPos - delimStart));
				}
			}
			start = pos + 1;
		}
		start = str.find_first_not_of(delims,start);
		++numSplits;
	} while (pos != string::npos);

	return ret;
}

void StringUtil::toLowerCase(string& str)
{
	std::transform(
						str.begin(),
						str.end(),
						str.begin(),
						tolower);
}

void StringUtil::toUpperCase(string& str)
{
	std::transform(
					str.begin(),
					str.end(),
					str.begin(),
					toupper
					);
}

bool StringUtil::startsWith(const string& str, const string& pattern, bool lowerCase)
{
	size_t thisLen = str.length();
	size_t patternLen = pattern.length();
	if(thisLen < patternLen || patternLen == 0)
		return false;
	string startOfThis = str.substr(0,patternLen);
	if(lowerCase)
		StringUtil::toLowerCase(startOfThis);
	return (startOfThis == pattern);
}

