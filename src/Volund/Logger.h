#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>

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
    using LogCallback = void(*)(std::string const&);

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

    struct LogLine
    {
        uint64_t Id;
        LogSeverity Severity;
        std::string Text;
    };

    class Logger
    {
    public:

        static Logger& GetCoreLogger();
        static Logger& GetClientLogger();

        template<typename... Args>
        uint64_t Log(LogSeverity severity, const char* format, Args&&... args);

        uint64_t Log(LogSeverity severity, const char* format);

        void UpdateLine(uint64_t lineId, const char* format);

        std::vector<LogLine>::iterator begin();
        std::vector<LogLine>::iterator end();

        Logger(std::string const& name);

    private:

        template<typename... Args>
        std::string FormatString(LogSeverity severity, const char* format, Args&&... args);

        uint64_t Print(LogSeverity severity, std::string const& string);

        static void UpdateConsole();

        static uint64_t FindLine(uint64_t lineId);

        static Logger m_CoreLogger;
        static Logger m_ClientLogger;

        static inline std::vector<LogLine> m_Lines;
        static inline uint64_t m_NewLineId;

        std::string m_Name;
    };

    template<typename... Args>
    inline uint64_t Logger::Log(LogSeverity severity, const char* format, Args&&... args)
    {
        std::string formatedString = this->FormatString(severity, format, std::forward<Args>(args)...);
        return Print(severity, formatedString);
    }

    template<typename... Args>
    inline std::string Logger::FormatString(LogSeverity severity, const char* format, Args&&... args)
    {
        int size_s = std::snprintf(nullptr, 0, format, args...) + 1;
        if (size_s <= 0)
        {
            throw std::runtime_error("Error during formatting.");
        }

        auto size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buf(new char[size]);

        std::snprintf(buf.get(), size, format, args ...);
        return std::string(buf.get(), buf.get() + size - 1);
    }
}

#ifdef VOLUND_CORE
#define VOLUND_LOGGER ::Volund::Logger::GetCoreLogger()
#else
#define VOLUND_LOGGER ::Volund::Logger::GetClientLogger()
#endif

#define VOLUND_INFO(...) VOLUND_LOGGER.Log(::Volund::LogSeverity::Info, __VA_ARGS__)
#define VOLUND_WARNING(...) VOLUND_LOGGER.Log(::Volund::LogSeverity::Warning, __VA_ARGS__)
#define VOLUND_ERROR(...) VOLUND_LOGGER.Log(::Volund::LogSeverity::Error, __VA_ARGS__)
#define VOLUND_UPDATE_LINE(...) VOLUND_LOGGER.UpdateLine(__VA_ARGS__)
#define VOLUND_ASSERT(condition, ...) if (!(condition)) {VOLUND_LOGGER.Log(::Volund::LogSeverity::Error, __VA_ARGS__);}
#define VOLUND_SOFT_ASSERT(condition, ...) if (!(condition)) {VOLUND_LOGGER.Log(::Volund::LogSeverity::Warning, __VA_ARGS__);}
