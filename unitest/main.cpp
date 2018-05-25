#include<iostream>
using namespace std;
#include "../frame/base/smartptr.h"
#include "../frame/base/basetool.h"
#include "serversockettest.h"
#include "threadpooltest.h"
#include "xfiletest.h"
#include "populartest.h"
#include "netprotocalbufftest.h"
#include "../frame/timer/timer.h"
#include "../frame/timer/timerquest.h"

#include "jpstest.h"

#ifdef WIN32
#pragma comment(lib, "pthreadVC2.lib")
#pragma comment(lib, "frame.lib")

#endif

void quest_func(void* )
{
	printf(" hello world from 10 secconds\n");
}

void Update(unsigned long interval, unsigned long nowTime)
{
//	printf("interval :%ld, nowTime: %ld\n",interval,nowTime);
	TimerQuest::getInstance()->Update(nowTime / 1000.0 , interval / 1000.0);
}
int main(int argc , char* argv[])
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
	//NetProtocalBuffTest test;
	//SingleManagerTest test;
	//MysqlTest test;
	//StringUtilTest utiltest;
//	StringConvertTest stringconvertertest;
//	Vector2Test vec2test;
//	TixmlTest tinyxmltext;
	//TimerTest timertest;

/*
	TimerQuest::getInstance()->AddDelayQuest(quest_func,10,false);

	while(true)
	{
		// enter main loop
		static unsigned long lastTime = Timer::getInstance()->getMilliseconds();
		unsigned long nowTime = Timer::getInstance()->getMilliseconds();
		if(nowTime - lastTime > 100)
		{
			Update(nowTime - lastTime,nowTime);
			lastTime = nowTime;
		}else{
			Sleep(5);
		}

	}
*/
//	SerializeTest serTest;

	DijkstraTest test;

	system("pause");
	return 0;
}