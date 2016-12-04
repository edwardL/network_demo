#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H
#include <string>
using namespace std;
#include <vector>

typedef vector<string> StringVector;

class StringConverter
{
public:
	static string toString(float val, unsigned short precision = 6,
			unsigned short width = 0, char fill = ' ',
			std::ios::fmtflags flags = std::ios::fmtflags(0) );
	static string toString(int val, unsigned short precision = 6,
			unsigned short width = 0, char fill = ' ',
			std::ios::fmtflags flags = std::ios::fmtflags(0));

	static string toString(unsigned long val, unsigned short precision = 6,
		unsigned short width = 0, char fill = ' ',
			std::ios::fmtflags flags = std::ios::fmtflags(0));

	static string toString(bool val);

	static string toString(const StringVector& val);

	static float parseFloat(const string&val, float defaultVal);
	static int	 parseInt(const string& val, int defaultVal);
	static unsigned int parseUnsignedInt(const string& val, unsigned int defaultVal);
	static long parseLong(const string& val, long defaultVal);
	static unsigned long parseUnsignedLong(const string&val, unsigned long defaultVal);
	static bool parseBool(const string& val, bool defaultVal);
};


#endif