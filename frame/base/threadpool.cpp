#include "threadpool.h"
#include "basetool.h"
#include "workerthread.h"
#include<iostream>
#include<algorithm>

void QueueOutManager::Run()
{
	if(0 != m_pool)
	{
		m_pool->TaskQueueOut();
	}
}

ThreadPool::ThreadPool()
	:m_max_thread_num(10),
	m_queue_out_manager(NULL)
{
	Init();
}
ThreadPool::ThreadPool(int max_num)
	:m_max_thread_num(max_num),
	m_queue_out_manager(NULL)
{
	Init();
}

ThreadPool::~ThreadPool()
{
	ClearAll();
	m_queue_out_manager->Join();
	delete m_queue_out_manager;

	m_idle_mutex.Destroy();
	m_work_mutex.Destroy();
	m_queue_mutex.Destroy();
}

void ThreadPool::Init()
{
	/// 初始化空闲线程，
	m_idle_mutex.Lock();
	for(int i = 0; i < m_max_thread_num; ++i)
	{
		WorkerThread *thread = new WorkerThread();
		thread->SetManagerPool(this);
		m_idle_list.push_back(thread);

	}
	m_idle_mutex.UnLock();

	/// 开始一个线程执行任务。
	m_queue_out_manager = new QueueOutManager(this);
	m_queue_out_manager->Start();
}

void ThreadPool::ClearAll()
{
	for(int i = 0; i < (int)m_work_list.size(); ++i)
	{
		m_work_list[i]->Join();
	}
	for(int i = 0; i < (int)m_idle_list.size(); ++i)
	{
		m_idle_list[i]->Join();
	}
}

void ThreadPool::AddTask(BaseTask *task, void* task_data)
{
	if(0 == task)
	{
		return;
	}
	m_queue_mutex.Lock();
	m_task_queue.push(TaskInfo(task,task_data));
	m_queue_mutex.UnLock();
}

int ThreadPool::GetIdleListNum()
{
	return (int)m_idle_list.size();
}

WorkerThread* ThreadPool::GetIdleThread()
{
	while(GetIdleListNum() <= 0)
	{
		MS_SLEEP(50);
	}
	m_idle_mutex.Lock();
	WorkerThread* thread = m_idle_list.front();
	m_idle_mutex.UnLock();
	return thread;
}
void ThreadPool::MoveToWorkList(WorkerThread* idle_thread)
{
	m_work_mutex.Lock();
	m_work_list.push_back(idle_thread);
	m_work_mutex.UnLock();

	m_idle_mutex.Lock();
	vector<WorkerThread*>::iterator it;
	it = find(m_idle_list.begin(), m_idle_list.end(),idle_thread);
	if(it != m_idle_list.end())
	{
		m_idle_list.erase(it);
	}
	m_idle_mutex.UnLock();
}
void ThreadPool::MoveToIdleList(WorkerThread* worker_thread)
{
	m_idle_mutex.Lock();
	m_idle_list.push_back(worker_thread);
	m_idle_mutex.UnLock();

	m_work_mutex.Lock();
	vector<WorkerThread*>::iterator it;
	it = find(m_work_list.begin(), m_work_list.end(), worker_thread);
	if(it != m_work_list.end())
	{
		m_work_list.erase(it);
	}
	m_work_mutex.UnLock();
}
void ThreadPool::TaskQueueOut()
{
	while(1)
	{
		while(m_task_queue.size() > 0)
		{
			WorkerThread* thread = GetIdleThread();
			if(0 != thread)
			{
				m_queue_mutex.Lock();
				TaskInfo info = m_task_queue.front();
				MoveToWorkList(thread);
				thread->SetManagerPool(this);
				thread->SetTask(info.task,info.task_data);
				info.task->SetWorkerThread(thread);
				m_task_queue.pop();
				m_queue_mutex.UnLock();
			}
		}
		MS_SLEEP(10);
	}
}