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
		std::chrono::time_point<std::chrono::steady_clock> Start;
	};

	/// <summary>
	/// Stores how much time has passed between to moments.
	/// </summary>
	class TimeStep
	{
	public:

		TimeStep(double Step = 0.0);

		operator float() const;

		operator double() const;

		double GetSeconds() const;

		double GetMilliseconds() const;

	private:

		double Step = 0.0f;
	};

} //namespace Volund