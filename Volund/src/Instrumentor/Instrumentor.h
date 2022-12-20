#pragma once

#if VOLUND_ENABLE_PROFILING
	#ifndef VOLUND_DIST
		#define VOLUND_PROFILING_ENABLED
	#endif
#endif

#ifdef VOLUND_PROFILING_ENABLED

namespace Volund
{
	class Instrumentor;

	class InstrumentorTimer
	{
	public:

		~InstrumentorTimer();

	private:

		friend class Instrumentor;

		InstrumentorTimer(uint64_t GroupID, const std::string& Name);

		uint64_t _GroupID;

		std::string _Name;

		std::chrono::time_point<std::chrono::steady_clock> _Start;

	};

	class Instrumentor
	{
	public:

		static void Start(uint64_t GroupID);

		static Ref<InstrumentorTimer> StartTimer(const std::string& Name);

		static void End();

	private:

		friend class InstrumentorTimer;

		static inline uint64_t _CurrentGroupID = 0;

		static inline std::chrono::time_point<std::chrono::steady_clock> _GroupStart;

		struct Event
		{
			std::vector<float> Timings;
		};

		struct Group
		{
			std::map<std::string, Event> Events;
			std::vector<float> Timings;
		};

		static inline std::map<uint64_t, Group> _Groups;

		Instrumentor() = default;

		~Instrumentor();
	};
}

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define VOLUND_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define VOLUND_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define VOLUND_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define VOLUND_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define VOLUND_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define VOLUND_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define VOLUND_FUNC_SIG __func__
#else
#define VOLUND_FUNC_SIG "VOLUND_FUNC_SIG unknown!"
#endif


#define VOLUND_PROFILING_START(ID) Volund::Instrumentor::Start(ID)
#define VOLUND_PROFILING_END() Volund::Instrumentor::End()
#define VOLUND_PROFILE_SCOPE(Name) auto Timer##__LINE__ = Volund::Instrumentor::StartTimer(Name)
#define VOLUND_PROFILE_FUNCTION() VOLUND_PROFILE_SCOPE(VOLUND_FUNC_SIG)

#else

#define VOLUND_PROFILING_START(ID)
#define VOLUND_PROFILING_END()
#define VOLUND_PROFILE_FUNCTION()
#define VOLUND_PROFILE_SCOPE()

#endif