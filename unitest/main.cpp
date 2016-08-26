#include<iostream>
using namespace std;
#include "../frame/base/smartptr.h"
#include "../frame/base/basetool.h"
#include "serversockettest.h"
#include "threadpooltest.h"
#include "xfiletest.h"
#include "heaptest.h"
#include "netprotocalbufftest.h"

#ifdef WIN32
#pragma comment(lib, "pthreadVC2.lib")
#pragma comment(lib, "frame.lib")
#endif

int main()
{
	/*
	SharedPtr<int> p(new int(10));
	cout<<*p<<endl;
	SharedPtr<int> p2(p);
	cout<<*p2<<endl;
	*/
	//ServerSocketDemo* demo = new ServerSocketDemo();
//	demo->Start();
///	XFileTest xfile(std::string("xfiletest.txt"));
	//XMemFileTest xmemfile(std::string("xfiletest.txt"));
	//HeapTest test;
	NetProtocalBuffTest test;
	cout<<"hello world"<<endl;
	system("pause");
	return 0;
}