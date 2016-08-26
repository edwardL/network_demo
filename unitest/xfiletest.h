#ifndef XFILE_TEST_H
#define XFILE_TEST_H

#include "../frame/file/DreamXFile.h"

class XFileTest
{
public:
	XFileTest();
	XFileTest(const std::string &filename);
};

class XMemFileTest
{
public:
	XMemFileTest();
	XMemFileTest(std::string &filename);
	~XMemFileTest();
};

#endif