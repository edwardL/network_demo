#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<vector>
#include<queue>
#include "basetask.h"
#include "basethread.h"
#include "mutex.h"

using namespace std;

class WorkerThread;
class ThreadPool;

class QueueOutManager : public BaseThread
{
public:
	QueueOutManager(ThreadPool *pool):m_pool(pool){}
	~QueueOutManager(){}
	void Run();
private:
	ThreadPool *m_pool;
};

class ThreadPool
{
	friend class QueueOutManager;
	friend class WorkerThread;
private:
	struct TaskInfo
	{
		TaskInfo():task(NULL),task_data(NULL){}
		TaskInfo(BaseTask* pTask,void* pdata):task(pTask),task_data(pdata){}
		~TaskInfo(){}
		BaseTask* task;
		void* task_data;
	};
public:
	ThreadPool();
	ThreadPool(int max_num);
	virtual ~ThreadPool();

public:
	void AddTask(BaseTask *task, void* task_data);
protected:
	void Init();
	void ClearAll();
	WorkerThread* GetIdleThread();
	void MoveToWorkList(WorkerThread* idle_thread);
	void MoveToIdleList(WorkerThread* worker_thread);
	void TaskQueueOut();
	int GetIdleListNum();

private:
	int m_max_thread_num;
	Mutex m_work_mutex;
	Mutex m_idle_mutex;
	Mutex m_queue_mutex;
	vector<WorkerThread *>m_work_list;
	vector<WorkerThread *>m_idle_list;
	queue<TaskInfo> m_task_queue;
	QueueOutManager *m_queue_out_manager;
};


#endif