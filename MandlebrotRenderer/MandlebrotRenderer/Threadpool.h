#pragma once
#include <vector>
#include <thread>
#include <atomic>


#include "BrotRenderer.h"
#include "WorkQueue.h"

class Threadpool
{
public:
	~Threadpool();
	static Threadpool& GetInstance();
	static void DestroyInstance();

	void Init();
	void Start();
	void Stop();
	void DoWork();
	void Submit(BrotRenderer WorkItem);
	std::atomic_int& GetProcessed();


protected:
	static Threadpool* Instance;

private:
	Threadpool();
	Threadpool(unsigned int);

	std::atomic_bool Finished{ false };

	WorkQueue<BrotRenderer>* Queue;

	std::vector <std::thread> WorkerThreads;

	unsigned int MaxThreads;

	std::atomic_int NumProcessed{ 0 };

};