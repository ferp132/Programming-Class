#pragma once
#include <mutex>
#include <queue>

template<typename T>
class WorkQueue
{
public:
	WorkQueue() {}

	void Push(const T& item);

	bool NonBlocking_Pop(T& WorkItem);
	Blocking_Pop(T& WorkItem);

	bool empty() const;

private:

	std::queue<T> WorkQueueQ;
	mutable std::mutex WorkQueueMutex;
	std::condition_variable WorkQueueCondition;
};

template<typename T>
inline void WorkQueue<T>::Push(const T & item)
{
	std::lock_guard<std::mutex> _lock(WorkQueueMutex);
	WorkQueueQ.push(item);
	WorkQueueCondition.notify_one();
}

template<typename T>
inline bool WorkQueue<T>::NonBlocking_Pop(T & WorkItem)
{
	std::lock_guard<std::mutex>
		_lock(WorkQueueMutex);
	if (WorkQueueQ.empty())
		return false;

	WorkItem = WorkQueueQ.front();
	WorkQueueQ.pop();
	return true;
}

template<typename T>
inline WorkQueue<T>::Blocking_Pop(T & WorkItem)
{
	std::unique_lock<std::mutex> _lock(WorkQueueMutex);

	WorkQueueCondition.wait(_lock, [this] {return !WorkQueueQ.empty(); });

	WorkItem = std::move(WorkQueueQ.front());
	WorkQueueQ.pop();
}

template<typename T>
inline bool WorkQueue<T>::empty() const
{
	return false;
}
