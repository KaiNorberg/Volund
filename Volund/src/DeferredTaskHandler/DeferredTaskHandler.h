#pragma once

namespace Volund
{
	class DeferredTaskHandler
	{
	public:

		static void DeferTask(std::function<void()> task);

		static void Execute();

	private:

		static inline std::mutex m_Mutex;

		static inline std::vector<std::function<void()>> m_Tasks;
	};
}