#pragma once

#include "../frame/base/threadpool.h"

class TestTask : public BaseTask
{
public:
	TestTask():m_count(0){}
	virtual void Run(void *data);
	int m_count;
};

class ThreadPoolDemo
{
public:
	void Start();
};