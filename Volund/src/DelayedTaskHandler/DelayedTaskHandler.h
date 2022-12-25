#pragma once

namespace Volund
{
	class DelayedTaskHandler
	{
	public:

		static void DelayTask(std::function<void()> Task);

		static void Execute();

	private:

		static inline std::mutex _Mutex;

		static inline std::vector<std::function<void()>> _Tasks;
	};
}