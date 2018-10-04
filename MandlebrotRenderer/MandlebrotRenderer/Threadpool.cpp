#include "Threadpool.h"

Threadpool* Threadpool::Instance = nullptr;

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

Threadpool& Threadpool::GetInstance()
{
		if (Instance == nullptr)
			Instance = new Threadpool();

		return (*Instance);
}

void Threadpool::DestroyInstance()
{
	delete Instance;
	Instance = 0;
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

	std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " -Start-" << std::endl;
	while (!Finished)
	{
		BrotRenderer WorkItem;

		if (Queue->NonBlocking_Pop(WorkItem))
		{
			std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " is working on item " << WorkItem.GetLine() << " in the work queue" << std::endl;
			WorkItem.CalculateBrot();
			std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " finished processing item " << WorkItem.GetLine() << std::endl;
			NumProcessed++;
		}
		else continue;
	}
}

void Threadpool::Submit(BrotRenderer WorkItem)
{
	Queue->Push(WorkItem);
}

std::atomic_int & Threadpool::GetProcessed()
{
	return NumProcessed;
}

