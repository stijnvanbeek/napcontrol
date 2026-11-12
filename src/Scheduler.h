#pragma once

#include <utility/threading.h>

namespace nap
{

	class Scheduler
	{
	public:
		using Task = std::function<void()>;

		Scheduler() = default;

		void schedule(double time, Task&& task)
		{
			mQueue[time] = std::move(task);
		}

		void process(double currentTime)
		{
			auto it = mQueue.begin();
			while (!mQueue.empty() && it->first < currentTime)
			{
				it->second();
				mQueue.erase(it);
				it = mQueue.begin();
			}
		}

	private:
		std::map<double, Task> mQueue;
	};

}