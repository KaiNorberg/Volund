#pragma once

namespace Volund
{
	/// <summary>
	/// Logs the time between its constructor and destructor when deconstructed.
	/// </summary>
	class Timer
	{
	public:
		Timer();

		~Timer();
	private:
		CHRONO_TIME_POINT m_Start;
	};

	class TimeStep
	{
	public:
		TimeStep(double step = 0.0);

		operator double() const;

		double GetSeconds() const;

		double GetMilliseconds() const;

	private:
		double m_Step = 0.0f;
	};
}
