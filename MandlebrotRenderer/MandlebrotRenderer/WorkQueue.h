#pragma once
#include <mutex>
#include <queue>

template<typename T>
class WorkQueue
{
public:
	WorkQueue() {}

	void Push(const T & item)
	{
		std::lock_guard<std::mutex> _lock(WorkQueueMutex);
		WorkQueueQ.push(std::move(item));
		WorkQueueCondition.notify_one();
	}

	bool NonBlocking_Pop(T & WorkItem)
	{
		std::lock_guard<std::mutex> _lock(WorkQueueMutex);
		if (WorkQueueQ.empty())
		{
			return false;
		}
		WorkItem = std::move(WorkQueueQ.front());
		WorkQueueQ.pop();
		return true;
	}

	void Blocking_Pop(T & WorkItem)
	{
		std::unique_lock<std::mutex> _lock(WorkQueueMutex);

		WorkQueueCondition.wait(_lock, [this] {return !WorkQueueQ.empty(); });

		WorkItem = std::move(WorkQueueQ.front());
		WorkQueueQ.pop();
	}

	bool CheckEmpty() const
	{
		std::lock_guard<std::mutex> _lock(WorkQueueMutex);
		return WorkQueueQ.empty();
	}

private:

	std::queue<T> WorkQueueQ;
	mutable std::mutex WorkQueueMutex;
	std::condition_variable WorkQueueCondition;
};