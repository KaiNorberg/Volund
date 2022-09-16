#pragma once

namespace Volund
{
	class Logger
	{
	public:
		static Logger& GetCoreLogger();

		static Logger& GetClientLogger();

		void Info(const char* Format, ...) const;

		void Warning(const char* Format, ...) const;

		void Error(const char* Format, ...) const;

		Logger(std::string_view Name);

	private:
		static Logger _CoreLogger;
		static Logger _ClientLogger;

		static std::string FormatString(const char* Format, ...);

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
