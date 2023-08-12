#include "PCH/PCH.h"
#include "Logger.h"

#include "Dialog/Dialog.h"

namespace Volund
{
	Logger Logger::m_CoreLogger = Logger("VOLUND");
	Logger Logger::m_ClientLogger = Logger("CLIENT");

	Logger& Logger::GetCoreLogger()
	{
		return m_CoreLogger;
	}

	Logger& Logger::GetClientLogger()
	{
		return m_ClientLogger;
	}

	uint64_t Logger::Log(LogSeverity severity, const char* format)
	{		
		std::string formatedString = this->FormatString(severity, format);
		return Print(severity, formatedString);
	}

	void Logger::UpdateLine(uint64_t lineId, const char* format)
	{
		m_Lines[FindLine(lineId)].Text += format;

		UpdateConsole();
	}

	uint64_t Logger::Print(LogSeverity severity, const std::string& string)
	{
		if (severity == LogSeverity::Error)
		{
			std::cout << string << '\n';

			#ifdef VOLUND_DIST
				Dialog::Message("ERROR!", format, "ok", "error");
			#endif

			abort();
		}

		std::string line = VOLUND_LOGGERCOLOR_RED;
		line += /*std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()) + " " +*/ this->m_Name + VOLUND_LOGGERCOLOR_WHITE + " - ";
		switch (severity)
		{
		case LogSeverity::Info:
		{
			line += VOLUND_LOGGERCOLOR_GREEN;
		}
		break;
		case LogSeverity::Warning:
		{
			line += VOLUND_LOGGERCOLOR_YELLOW;
		}
		break;
		case LogSeverity::Error:
		{
			line += VOLUND_LOGGERCOLOR_RED;
		}
		break;
		}
		line += string;

		std::cout << line << '\n';

		m_NewLineId++;
		m_Lines.push_back({m_NewLineId, severity, line});

		return m_NewLineId;
	}

	void Logger::UpdateConsole()
	{
		std::cout << "\x1b[H";

		for (const auto& line : m_Lines) 
		{
			std::cout << line.Text << std::endl;
		}
	}

	uint64_t Logger::FindLine(uint64_t lineId)
	{
		VOLUND_PROFILE_FUNCTION();

		auto it = std::lower_bound(m_Lines.begin(), m_Lines.end(), lineId, [](const LogLine& a, uint64_t lineId)
		{
			return a.Id < lineId;
		});

		if (it != m_Lines.end())
		{
			return it - m_Lines.begin();
		}
		else
		{
			return 0;
		}
	}

	Logger::Logger(std::string_view name)
	{
		this->m_Name = name;
	}

} //namespace Volund
