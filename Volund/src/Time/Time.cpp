#pragma once

#include "PCH/PCH.h"
#include "Time.h"

namespace Volund
{
	Timer::Timer()
	{
		Start = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - Start;
		VOLUND_INFO("Timer destroyed! Time passed: %f | Iterations per second: %f", Duration.count(),
		            1 / Duration.count());
	}

	TimeStep::TimeStep(double Step)
	{
		this->Step = Step;
	}

	TimeStep::operator double() const
	{
		return this->Step;
	}

	double TimeStep::GetSeconds() const
	{
		return this->Step;
	}

	double TimeStep::GetMilliseconds() const
	{
		return this->Step * 1000.0f;
	}
} //namespace Volund
