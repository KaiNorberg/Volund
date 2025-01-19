#include "Time.h"

#include "Logger.h"

namespace Volund
{
	Timer::Timer()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_start;
		VOLUND_INFO("Timer destroyed! Time passed: {} | Iterations per second: {}", duration.count(), 1 / duration.count());
	}

	TimeStep::TimeStep(const double step)
	{
		this->m_step = step;
	}

	TimeStep::operator double() const
	{
		return this->m_step;
	}

	double TimeStep::GetSeconds() const
	{
		return this->m_step;
	}

	double TimeStep::GetMilliseconds() const
	{
		return this->m_step * 1000.0f;
	}
}
