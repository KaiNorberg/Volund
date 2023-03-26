#pragma once

#define VOLUND_LOGGERCOLOR_BLACK   "\033[30m"
#define VOLUND_LOGGERCOLOR_RED     "\033[31m"
#define VOLUND_LOGGERCOLOR_GREEN   "\033[32m"
#define VOLUND_LOGGERCOLOR_YELLOW  "\033[33m"
#define VOLUND_LOGGERCOLOR_BLUE    "\033[34m"
#define VOLUND_LOGGERCOLOR_MAGENTA "\033[35m"
#define VOLUND_LOGGERCOLOR_CYAN    "\033[36m"
#define VOLUND_LOGGERCOLOR_WHITE   "\033[37m"

namespace Volund
{
	enum class LoggerColor
	{
		Black,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White
	};

	using LoggerCallback = void(*)(const std::string&);

	class Logger
	{
	public:

		static Logger& GetCoreLogger();

		static Logger& GetClientLogger();

		void Info(const char* format, ...);

		void Warning(const char* format, ...);

		void Error(const char* format, ...);

		void SetCallback(LoggerCallback newCallback);

		Logger(std::string_view name);

	private:

		static Logger m_CoreLogger;
		static Logger m_ClientLogger;

		std::mutex m_Mutex;

		std::string FormatString(LoggerColor color, const char* format, std::va_list args) const;

		std::string FormatString(const char* format, std::va_list args) const;

		LoggerCallback m_Callback;

		std::string m_Name;
	};
}

#ifdef VOLUND_CORE
	#define VOLUND_INFO(...) ::Volund::Logger::GetCoreLogger().Info(__VA_ARGS__)
	#define VOLUND_WARNING(...) ::Volund::Logger::GetCoreLogger().Warning(__VA_ARGS__)
	#define VOLUND_ERROR(...) ::Volund::Logger::GetCoreLogger().Error(__VA_ARGS__)
#else
    #define VOLUND_INFO(...) ::Volund::Logger::GetClientLogger().Info(__VA_ARGS__)
    #define VOLUND_WARNING(...) ::Volund::Logger::GetClientLogger().Warning(__VA_ARGS__)
    #define VOLUND_ERROR(...) ::Volund::Logger::GetClientLogger().Error(__VA_ARGS__)
#endif
