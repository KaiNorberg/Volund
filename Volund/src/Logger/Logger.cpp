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

	void Logger::SetCallback(const LoggerCallback newCallback)
	{
		this->m_Callback = newCallback;
	}

	void Logger::Info(const char* format)
	{
		this->Print(LogSeverity::Info, format);
	}

	void Logger::Warning(const char* format)
	{
		this->Print(LogSeverity::Warning, format);
	}

	void Logger::Error(const char* format)
	{
		this->Print(LogSeverity::Error, format);

		abort();
	}

	void Logger::Print(LogSeverity severity, const std::string& string )
	{		
		std::unique_lock lock(this->m_Mutex);

		std::string output = VOLUND_LOGGERCOLOR_RED;
		output += /*std::format("{:%H:%M:%OS}", std::chrono::system_clock::now()) + " " +*/ this->m_Name + VOLUND_LOGGERCOLOR_WHITE + " - ";

		switch (severity)
		{
		case LogSeverity::Info:
		{
			output += VOLUND_LOGGERCOLOR_GREEN;
		}
		break;
		case LogSeverity::Warning:
		{
			output += VOLUND_LOGGERCOLOR_YELLOW;
		}
		break;
		case LogSeverity::Error:
		{
			output += VOLUND_LOGGERCOLOR_RED;
		}
		break;
		}

		output += string;
	
		if (this->m_Callback != nullptr)
		{
			this->m_Callback(output);
		}

		#ifdef VOLUND_DIST
			if (severity == LogSeverity::Error)
			{
				Dialog::Message("ERROR!", string, "ok", "error");
			}
		#endif

		std::cout << output << '\n';
	}

	Logger::Logger(std::string_view name)
	{
		this->m_Name = name;
		this->m_Callback = nullptr;
	}
	
} //namespace Volund
