#include "threadpooltest.h"
#include <iostream>
#include "../frame/base/basetool.h"

void TestTask::Run(void *data)
{
	for(int i = 0; i < 3; i++)
	{
		if(0 == data)
		{
			return;
		}
		std::cout<<"this is thread: "<<*(int *)data << " count:"<< ++m_count <<std::endl;
		MS_SLEEP(1000);
	}
}

void ThreadPoolDemo::Start()
{
	ThreadPool pool(5);
	for(int i = 0; i < 50; i++)
	{
		TestTask* task = new TestTask();
		int *data = new int(i);
		pool.AddTask(task,(void*)data);
		std::cout<<"add "<<i <<std::endl;
	}
	std::cout<<"__________________________Over______________________"<<std::endl;
}