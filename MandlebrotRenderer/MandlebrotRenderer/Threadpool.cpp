#include "Threadpool.h"

Threadpool::Threadpool()
{
	MaxThreads = std::thread::hardware_concurrency();
	Finished = false;
}

Threadpool::Threadpool(unsigned int InitMaxThreads)
{
	if (InitMaxThreads <= std::thread::hardware_concurrency())
		MaxThreads = InitMaxThreads;
	else
		MaxThreads = std::thread::hardware_concurrency();
	
	Finished = false;
}

Threadpool::~Threadpool()
{
	Finished = true;
	for (unsigned int i = 0; i < MaxThreads; i++)
	{
		WorkerThreads[i].join();
	}

	delete Queue;
	Queue = 0;
}

void Threadpool::Init()
{
	Queue = new WorkQueue<BrotRenderer>();
}

void Threadpool::Start()
{
	for (unsigned int i = 0; i < MaxThreads; i++)
	{
		WorkerThreads.push_back(std::thread(&Threadpool::DoWork, this));
	}
}

void Threadpool::Stop()
{
	Finished = true;
}

void Threadpool::DoWork()
{
	while (!Finished)
	{
		Queue->Blocking_Pop(WorkItem);
	}
}

void Threadpool::Submit(BrotRenderer WorkItem)
{
	Queue->Push(WorkItem);
}
