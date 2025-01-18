#include "Time.h"

#include "Logger.h"

namespace Volund
{
	Timer::Timer()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		const std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_Start;
		VOLUND_INFO("Timer destroyed! Time passed: %f | Iterations per second: %f", duration.count(), 1 / duration.count());
	}

	TimeStep::TimeStep(const double step)
	{
		this->m_Step = step;
	}

	TimeStep::operator double() const
	{
		return this->m_Step;
	}

	double TimeStep::GetSeconds() const
	{
		return this->m_Step;
	}

	double TimeStep::GetMilliseconds() const
	{
		return this->m_Step * 1000.0f;
	}
}
