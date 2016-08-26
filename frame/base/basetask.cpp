#include "basetask.h"
#include<stdlib.h>

BaseTask::BaseTask()
	:m_worker_thread(0)
{

}

BaseTask::~BaseTask()
{

}

void BaseTask::SetWorkerThread(WorkerThread *worker)
{
	m_worker_thread = worker;
}

WorkerThread* BaseTask::GetWorkerThread(WorkerThread* worker)
{
	return m_worker_thread;
}