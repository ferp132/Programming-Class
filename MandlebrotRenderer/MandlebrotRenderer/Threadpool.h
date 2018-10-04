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

	void Init();
	void Start();
	void Stop();
	void DoWork();
	void Submit(BrotRenderer WorkItem);

private:

	static Threadpool* Instance;

	Threadpool();
	Threadpool(unsigned int);

	std::atomic_bool Finished;

	WorkQueue<BrotRenderer>* Queue;

	std::vector <std::thread> WorkerThreads;

	unsigned int MaxThreads;

};