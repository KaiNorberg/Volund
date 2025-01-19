#include "Logger.h"

#include "Dialog.h"

namespace Volund
{
	Logger Logger::m_coreLogger = Logger("VOLUND");
	Logger Logger::m_clientLogger = Logger("CLIENT");

	Logger& Logger::GetCoreLogger()
	{
		return m_coreLogger;
	}

	Logger& Logger::GetClientLogger()
	{
		return m_clientLogger;
	}

	uint64_t Logger::Log(LogSeverity severity, const char* format)
	{
		std::string formatedString = this->FormatString(severity, format);
		return Print(severity, formatedString);
	}

	void Logger::UpdateLine(uint64_t lineId, const char* format)
	{
		m_lines[FindLine(lineId)].Text += format;

		UpdateConsole();
	}

	std::vector<LogLine>::iterator Logger::begin()
	{
		return this->m_lines.begin();
	}

	std::vector<LogLine>::iterator Logger::end()
	{
		return this->m_lines.end();
	}

	uint64_t Logger::Print(LogSeverity severity, std::string const& string)
	{
		std::string line = VOLUND_LOGGERCOLOR_RED;
		line += /*std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()) + " " +*/ this->m_name + VOLUND_LOGGERCOLOR_WHITE + " - ";
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

		if (severity == LogSeverity::Error)
		{
			#ifdef VOLUND_DIST
				Dialog::Message("ERROR!", string, "ok", "error");
			#endif

			abort();
		}

		m_newLineId++;
		m_lines.push_back({m_newLineId, severity, line});

		if (m_lines.size() > 100)
		{
			m_lines.erase(m_lines.begin(), m_lines.begin() + 50);
		}

		return m_newLineId;
	}

	void Logger::UpdateConsole()
	{
		std::cout << "\x1b[H";

		for (const auto& line : m_lines)
		{
			std::cout << line.Text << std::endl;
		}
	}

	uint64_t Logger::FindLine(uint64_t lineId)
	{
		VOLUND_PROFILE_FUNCTION();

		auto it = std::lower_bound(m_lines.begin(), m_lines.end(), lineId, [](const LogLine& a, uint64_t lineId)
		{
			return a.Id < lineId;
		});

		if (it != m_lines.end())
		{
			return it - m_lines.begin();
		}
		else
		{
			return 0;
		}
	}

	Logger::Logger(std::string const& name)
	{
		this->m_name = name;
	}

} //namespace Volund
