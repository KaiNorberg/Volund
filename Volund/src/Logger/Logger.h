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
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE
	};

	using LoggerCallback = void(*)(const std::string&);

	class Logger
	{
	public:
		static Logger& GetCoreLogger();

		static Logger& GetClientLogger();

		void Info(const char* Format, ...) const;

		void Warning(const char* Format, ...) const;

		void Error(const char* Format, ...) const;

		void SetCallback(LoggerCallback NewCallback);

		Logger(std::string_view Name);

	private:
		static Logger _CoreLogger;
		static Logger _ClientLogger;

		std::string FormatString(LoggerColor Color, const char* Format, std::va_list Args) const;

		std::string FormatString(const char* Format, std::va_list Args) const;

		static void DefaultCallback(const std::string& String);

		LoggerCallback _Callback;

		std::string _Name;
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
