#include "Logger.h"

#include "Dialog.h"

#include <cstdarg>

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

	void Logger::WriteString(LogSeverity severity, std::string const& string)
	{
		std::string line = VOLUND_LOGGERCOLOR_RED"[" + std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()) + "] [" + this->m_name + "] ";

		switch (severity)
		{
		case LogSeverity::Info:
		{
			line += "[INFO]: " VOLUND_LOGGERCOLOR_GREEN;
		}
		break;
		case LogSeverity::Warning:
		{
			line += "[WARN]: " VOLUND_LOGGERCOLOR_YELLOW;
		}
		break;
		case LogSeverity::Error:
		{
			line += "[ERROR]: " VOLUND_LOGGERCOLOR_RED;
		}
		break;
		}

		line += string + VOLUND_LOGGERCOLOR_WHITE;

		for (std::ostream* stream : this->m_listeners)
		{
			*stream << line << std::endl;
		}

		if (severity == LogSeverity::Error)
		{
			#ifdef VOLUND_DIST
				Dialog::Message("ERROR!", line, "ok", "error");
			#endif

			abort();
		}
	}

    void Logger::AddListener(std::ostream* stream)
    {
		this->m_listeners.push_back(stream);
    }

    void Logger::RemoveListener(std::ostream* stream)
    {
		this->m_listeners.erase(std::remove(this->m_listeners.begin(), this->m_listeners.end(), stream), this->m_listeners.end());
    }

    Logger::Logger(std::string const& name)
	{
		this->AddListener(&std::cout);
		this->m_name = name;
	}

} //namespace Volund
