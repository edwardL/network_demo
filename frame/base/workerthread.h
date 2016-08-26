#include "basethread.h"
#include "basetask.h"

class ThreadPool;

class WorkerThread : public BaseThread
{
public:
	WorkerThread();
	~WorkerThread();

public:
	virtual void Run();

public:
	void SetTask(BaseTask *task, void *task_data);
	BaseTask* GetTask();

	void SetManagerPool(ThreadPool *pool);
	ThreadPool* GetManagerPool();
private:
	BaseTask *m_task;
	void *m_task_data;
	ThreadPool *m_manager_pool;
};