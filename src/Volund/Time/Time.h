#pragma once

#include <chrono>

#ifdef _WIN32
#define CHRONO_TIME_POINT std::chrono::time_point<std::chrono::steady_clock>
#else
#define CHRONO_TIME_POINT std::chrono::_V2::system_clock::time_point
#endif

namespace Volund
{
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
