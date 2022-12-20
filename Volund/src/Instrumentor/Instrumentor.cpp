#include "PCH/PCH.h"
#include "Instrumentor.h"

#ifdef VOLUND_PROFILING_ENABLED

namespace Volund
{
	InstrumentorTimer::InstrumentorTimer(uint64_t GroupID, const std::string& Name)
	{
		this->_Name = Name;
		this->_GroupID = GroupID;
		this->_Start = std::chrono::high_resolution_clock::now();
	}

	InstrumentorTimer::~InstrumentorTimer()
	{
		std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - this->_Start;
	
		if (this->_GroupID != 0)
		{
			Instrumentor::_Groups[this->_GroupID].Events[this->_Name].Timings.push_back(Duration.count());
		}
	}

	void Instrumentor::Start(uint64_t GroupID)
	{
		static Instrumentor SingleTon;

		_GroupStart = std::chrono::high_resolution_clock::now();

		_CurrentGroupID = GroupID;
	}

	Ref<InstrumentorTimer> Instrumentor::StartTimer(const std::string& Name)
	{
		return Ref<InstrumentorTimer>(new InstrumentorTimer(_CurrentGroupID, Name));
	}

	void Instrumentor::End()
	{
		std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - _GroupStart;

		Instrumentor::_Groups[_CurrentGroupID].Timings.push_back(Duration.count());

		_CurrentGroupID = 0;
	}

	Instrumentor::~Instrumentor()
	{
		std::ofstream OutFile("Instrumentor.txt");

		for (auto& [GroupID, Group] : this->_Groups)
		{
			OutFile << "NEW GROUP: " << GroupID << std::endl;

			float TotalSessionTime = 0.0f;
			for (auto& Timing : Group.Timings)
			{
				TotalSessionTime += Timing;
			}
			float AverageSessionTime = TotalSessionTime / Group.Timings.size();

			for (auto& [EventName, Event] : Group.Events)
			{
				float TotalEventTime = 0.0f;
				for (auto& Timing : Event.Timings)
				{
					TotalEventTime += Timing;
				}
				float AverageEventTime = TotalEventTime / Event.Timings.size();

				int SpaceCount = 125 - EventName.size();
				OutFile << EventName;
				for (int i = 0; i < SpaceCount; i++)
				{
					OutFile << ' ';
				}
				OutFile << " | " << AverageEventTime << ",s " << (TotalEventTime / TotalSessionTime) * 100.0f << "%" << std::endl;
			}

			OutFile << "END GROUP" << std::endl << std::endl;
		}
	}
}

#endif