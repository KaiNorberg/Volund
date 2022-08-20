#pragma once

#include "PCH/PCH.h"
#include "Console.h"

namespace Volund::Console
{
	std::ostream& operator<<(std::ostream& os, ConsoleColor code)
	{
		return os << "\033[" << static_cast<int>(code) << "m";
	}

	const std::string GetStringTime()
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
		std::string str(buffer);

		return "[" + str + "] ";
	}

	void EndLog()
	{
		std::cout << "\n";
	}

} //namespace Volund