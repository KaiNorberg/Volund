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

	void Logger::Info(const char* format, ...)
	{
		std::unique_lock lock(this->m_Mutex);

		std::va_list args;
		va_start(args, format);

		std::string formatedString = this->FormatString(LoggerColor::Green, format, args);
		if (this->m_Callback != nullptr)
		{
			this->m_Callback(formatedString);
		}
		std::cout << formatedString << '\n';

		va_end(args);
	}

	void Logger::Warning(const char* format, ...)
	{
		std::unique_lock lock(this->m_Mutex);

		std::va_list args;
		va_start(args, format);

		const std::string formatedString = this->FormatString(LoggerColor::Yellow, format, args);
		if (this->m_Callback != nullptr)
		{
			this->m_Callback(formatedString);
		}
		std::cout << formatedString << '\n';

		va_end(args);
	}

	void Logger::Error(const char* format, ...)
	{
		std::unique_lock Lock(this->m_Mutex);

		std::va_list args;
		va_start(args, format);

		const std::string formatedString = this->FormatString(LoggerColor::Red, format, args);
		if (this->m_Callback != nullptr)
		{
			this->m_Callback(formatedString);
		}
		#ifdef VOLUND_DIST		
		Dialog::MessageBox("ERROR!", formatedString, "ok", "error");
		#else		
		std::cout << formatedString << '\n';
		#endif

		va_end(args);

		abort();
	}

	void Logger::SetCallback(const LoggerCallback newCallback)
	{
		this->m_Callback = newCallback;
	}

	Logger::Logger(std::string_view name)
	{
		this->m_Name = name;
		this->m_Callback = nullptr;
	}

	std::string Logger::FormatString(LoggerColor color, const char* format, std::va_list args) const
	{
		std::string output = VOLUND_LOGGERCOLOR_RED;
		output += /*std::format("{:%H:%M:%OS}", std::chrono::system_clock::now())*/ + " " + this->m_Name + VOLUND_LOGGERCOLOR_WHITE + " - ";

		switch (color)
		{
		case LoggerColor::Black:
		{
			output += VOLUND_LOGGERCOLOR_BLACK;
		}
		break;
		case LoggerColor::Red:
		{
			output += VOLUND_LOGGERCOLOR_RED;
		}
		break;
		case LoggerColor::Green:
		{
			output += VOLUND_LOGGERCOLOR_GREEN;
		}
		break;
		case LoggerColor::Yellow:
		{
			output += VOLUND_LOGGERCOLOR_YELLOW;
		}
		break;
		case LoggerColor::Blue:
		{
			output += VOLUND_LOGGERCOLOR_BLUE;
		}
		break;
		case LoggerColor::Magenta:
		{
			output += VOLUND_LOGGERCOLOR_MAGENTA;
		}
		break;
		case LoggerColor::White:
		{
			output += VOLUND_LOGGERCOLOR_WHITE;
		}
		break;
		}

		output += FormatString(format, args);

		return output;
	}

	std::string Logger::FormatString(const char* format, std::va_list args) const
	{
		size_t size = std::vsnprintf(nullptr, 0, format, args) + 1;
		std::string formatedString;
		formatedString.resize(size);
		std::vsnprintf(formatedString.data(), size, format, args);

		return formatedString;
	}

} //namespace Volund
