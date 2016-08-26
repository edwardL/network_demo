#ifndef BASE_TASK_H
#define BASE_TASK_H

class WorkerThread;

class BaseTask
{
public:
	BaseTask();
	virtual ~BaseTask();

public:
	virtual void Run(void* data) = 0;

public:
	void SetWorkerThread(WorkerThread *worker);
	WorkerThread* GetWorkerThread(WorkerThread* worker);

private:
	WorkerThread *m_worker_thread;
};

#endif