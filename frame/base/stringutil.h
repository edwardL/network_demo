#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <vector>
#include <string>
using namespace std;

class StringUtil
{
public:
		static void trim(string& str, bool left = true, bool right = true);

		static vector<string> split(string& str, const string& delims="\t\n",unsigned int maxSplits = 0, bool preserveDelims = false);

		static void toLowerCase(string& str);
		static void toUpperCase(string& str);

		static bool startsWith(const string& str, const string& pattern, bool lowerCase = true);

		static bool endsWith(const string& str, const string& pattern, bool lowerCase = true);

		static string standardisePath(const string& init);

		static void splitFileName(const string& qualifiedName, string& outBaseName, string &outPath);

		static const string replaceAll(const string& source, const string& replaceWhat, const string replaceWithWhat);
};


#endif