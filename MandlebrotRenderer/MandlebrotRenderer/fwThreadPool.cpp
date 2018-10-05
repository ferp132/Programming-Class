//Library Includes
#include <iostream>
#include <thread>
#include <functional>

//Local Includes
#include "fwWorkQueue.h"
#include "BrotRenderer.h"

//This Include
#include "fwThreadPool.h"

//Static Variables
ThreadPool* ThreadPool::s_pThreadPool = nullptr;

ThreadPool::ThreadPool()
{
	m_iNumberOfThreads = std::thread::hardware_concurrency();
}


ThreadPool::ThreadPool(unsigned int _size)
{
	//Create a pool of threads equal to specified size
	m_iNumberOfThreads = _size;
}

ThreadPool::~ThreadPool()
{
	m_bStop = true;
	for (unsigned int i = 0; i < m_iNumberOfThreads; i++)
	{
		m_workerThreads[i].join();
	}

	/*delete m_pWorkQueue;
	m_pWorkQueue = 0;*/
}

ThreadPool& ThreadPool::GetInstance()
{
	if (s_pThreadPool == nullptr)
	{
		s_pThreadPool = new ThreadPool();
	}
	return (*s_pThreadPool);
}

void ThreadPool::DestroyInstance()
{
	delete s_pThreadPool;
	s_pThreadPool = 0;
}

void ThreadPool::Initialize()
{
	//Create a new Work Queue
	m_pWorkQueue = new CWorkQueue<BrotRenderer>();
}

void ThreadPool::Start()
{
	for (unsigned int i = 0; i < m_iNumberOfThreads; i++)
	{
		m_workerThreads.push_back(std::thread(&ThreadPool::DoWork, this));
	}
}

void ThreadPool::Submit(BrotRenderer _fItem)
{
	m_pWorkQueue->push(_fItem);
}

void ThreadPool::Stop()
{
	m_bStop = true;
}


void ThreadPool::DoWork()
{
	//Entry point of  a thread.
	std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << "starting........" << std::endl;
	while (!m_bStop)
	{
		BrotRenderer WorkItem;
		//If there is an item in the queue to be processed; just take it off the q and process it
		//m_pWorkQueue->blocking_pop(WorkItem);
		if (m_pWorkQueue->nonblocking_pop(WorkItem))
		{
			std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " is working on item " << WorkItem.GetLine() << " in the work queue" << std::endl;
			WorkItem.CalculateBrot();
			//Sleep to simulate work being done
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 101));
			std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " finished processing item " << WorkItem.GetLine() << std::endl;
			m_aiItemsProcessed++;
		}
		//Else just continue back to the beginning of the while loop.
		else
		{
			continue;
		}
	}
}

std::atomic_int& ThreadPool::getItemsProcessed()
{
	return m_aiItemsProcessed;
}

