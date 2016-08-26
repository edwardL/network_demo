#include "workerthread.h"
#include "threadpool.h"
#include "basetool.h"
#include <string.h>
#include <stdlib.h>

WorkerThread::WorkerThread()
	:m_task(NULL),
	m_task_data(NULL),
	m_manager_pool(NULL)
{
	if(0 != m_task)
	{
		delete m_task;
	}
	m_task = NULL;
	m_task_data = NULL;
	m_manager_pool = NULL;

	Start();
}

WorkerThread::~WorkerThread()
{

}

void WorkerThread::Run()
{
	while(!m_exit)
	{
		while(m_task == NULL)
		{
			MS_SLEEP(50);
		}
		m_task->Run(m_task_data);
		m_task->SetWorkerThread(NULL);
		m_task = NULL;
		free(m_task_data);
		m_task_data = NULL;
		m_manager_pool->MoveToIdleList(this);

		MS_SLEEP(10);
	}
}

void WorkerThread::SetTask(BaseTask *task, void *task_data)
{
	m_task = task;

	m_task_data = malloc(sizeof(task_data));
	memcpy(m_task_data,task_data,sizeof(task_data));
	m_task_data = task_data;	 
}

BaseTask* WorkerThread::GetTask()
{
	return m_task;
}

void WorkerThread::SetManagerPool(ThreadPool *pool)
{
	m_manager_pool = pool;
}

ThreadPool* WorkerThread::GetManagerPool()
{
	return m_manager_pool;
}
