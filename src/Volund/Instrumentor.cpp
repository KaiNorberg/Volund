#include "Instrumentor.hpp"

#ifdef VOLUND_ENABLE_PROFILING

namespace Volund
{
	std::string InstrumentorNode::FormatTime()
	{
		std::chrono::duration<double> Duration = this->End - this->Start;

		double Count = Duration.count();

		return std::to_string(Count);
	}

	std::string InstrumentorNode::FormatName()
	{
		auto StartOfName = this->Name.find("__cdecl") + 8;
		auto EndOfName = this->Name.find_first_of('(');

		if (StartOfName != std::string::npos && EndOfName != std::string::npos)
		{
			return this->Name.substr(StartOfName, EndOfName - StartOfName);
		}
		else
		{
			return this->Name;
		}
	}

	std::string InstrumentorNode::Serialize(int Depth)
	{
		std::string Output;

		if (Depth >= 0)
		{
			Output += std::string(Depth, '\t') + this->FormatName() + " - " + this->FormatTime() + "s\n";
		}

		for (auto& Child : this->Children)
		{
			Output += Child->Serialize(Depth + 1);
		}

		return Output;
	}

	InstrumentorTimer::InstrumentorTimer(std::string const& Name)
	{
		static Instrumentor Singleton;

		this->_Node = std::make_shared<InstrumentorNode>();
		this->_Node->Name = Name;
		this->_Node->Start = std::chrono::high_resolution_clock::now();

		this->_Node->Parent = Instrumentor::CurrentNode;
		Instrumentor::CurrentNode->Children.push_back(this->_Node);
		Instrumentor::CurrentNode = this->_Node;
	}

	InstrumentorTimer::~InstrumentorTimer()
	{
		if (Instrumentor::CurrentNode == this->_Node)
		{
			Instrumentor::CurrentNode->End = std::chrono::high_resolution_clock::now();
			Instrumentor::CurrentNode = Instrumentor::CurrentNode->Parent;
		}
		else
		{
			VOLUND_ERROR("Invalid Node");
		}
	}

	Instrumentor::Instrumentor()
	{
		Instrumentor::CurrentNode = std::make_shared<InstrumentorNode>();
		Instrumentor::FirstNode = Instrumentor::CurrentNode;

	}

	Instrumentor::~Instrumentor()
	{
		std::ofstream OutFile("Instrumentor.txt");

		OutFile << Instrumentor::FirstNode->Serialize(-1);
	}
}

#endif
