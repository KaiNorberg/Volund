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
	enum class LogColor
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
	
	enum class LogSeverity
	{
		Info,
		Warning,
		Error
	};

	using LoggerCallback = void(*)(const std::string&);

	class Logger
	{
	public:

		static Logger& GetCoreLogger();

		static Logger& GetClientLogger();

		template<typename... Args>
		void Info(const char* format, Args&&... args);

		template<typename... Args>
		void Warning(const char* format, Args&&... args);

		template<typename... Args>
		void Error(const char* format, Args&&... args);
		
		void Info(const char* format);

		void Warning(const char* format);

		void Error(const char* format);

		void Print(LogSeverity severity, const std::string& string);

		void SetCallback(LoggerCallback newCallback);

		Logger(std::string_view name);

	private:

		static Logger m_CoreLogger;
		static Logger m_ClientLogger;

		std::mutex m_Mutex;

		template<typename... Args>
		std::string FormatString(const char* format, Args&&... args)
		{
			int size_s = std::snprintf( nullptr, 0, format, args... ) + 1;
			if( size_s <= 0 )
			{ 
				throw std::runtime_error( "Error during formatting." ); 
			}

			auto size = static_cast<size_t>( size_s );
			std::unique_ptr<char[]> buf( new char[ size ] );

			std::snprintf( buf.get(), size, format, args ... );
			return std::string( buf.get(), buf.get() + size - 1 );
		}

		LoggerCallback m_Callback;

		std::string m_Name;
	};

	template<typename... Args>
	inline void Logger::Info(const char* format, Args&&... args)
	{
		std::string formatedString = this->FormatString(format, std::forward<Args>(args)...);
		this->Print(LogSeverity::Info, formatedString);
	}

	template<typename... Args>
	inline void Logger::Warning(const char* format, Args&&... args)
	{
		std::string formatedString = this->FormatString(format, std::forward<Args>(args)...);
		this->Print(LogSeverity::Warning, formatedString);
	}

	template<typename... Args>
	inline void Logger::Error(const char* format, Args&&... args)
	{
		std::string formatedString = this->FormatString(format, std::forward<Args>(args)...);
		this->Print(LogSeverity::Error, formatedString);

		abort();
	}
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
