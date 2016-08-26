#include "xfiletest.h"
#include<iostream>

XFileTest::XFileTest()
{

}

XFileTest::XFileTest(const std::string &filename)
{
	XFile file;
	if(! file.Open(filename,"wb"))
	{
		std::cout <<" open file failed"<<std::endl;
	}
	std::cout<<"file size is:" << file.GetFileSize() <<std::endl;
	char *buf = new char[file.GetFileSize() + 1];
	file.ReadAll(buf);
	buf[file.GetFileSize()] = '\0';
	///std::cout <<" file content is : " << buf <<std::endl;

	char* content2 = "content2 to write";
	file.Write(content2,strlen(content2));
	char* content3 = "hahahaha";
	file.Write(content3,strlen(content3));
	file.Close();
}

XMemFileTest::XMemFileTest()
{

}

XMemFileTest::XMemFileTest(std::string &filename)
{
	XMemFile file;
	file.LoadFromFile(filename);

	file.SaveToFile(std::string("a.txt"));
}

XMemFileTest::~XMemFileTest()
{

}

