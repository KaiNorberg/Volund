#pragma once

#include "Core.hpp"

#include <string>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <format>

#define VOLUND_LOGGERCOLOR_BLACK   "\033[30m"
#define VOLUND_LOGGERCOLOR_RED     "\033[31m"
#define VOLUND_LOGGERCOLOR_GREEN   "\033[32m"
#define VOLUND_LOGGERCOLOR_YELLOW  "\033[33m"
#define VOLUND_LOGGERCOLOR_BLUE    "\033[34m"
#define VOLUND_LOGGERCOLOR_MAGENTA "\033[35m"
#define VOLUND_LOGGERCOLOR_CYAN    "\033[36m"
#define VOLUND_LOGGERCOLOR_WHITE   "\033[37m"

// Provide a formatter specialization for unsigned char*
template<>
struct std::formatter<const unsigned char*> : std::formatter<std::string_view> 
{
    auto format(const unsigned char* str, auto& ctx) const 
    {
        if (str == nullptr) 
        {
            return std::formatter<std::string_view>::format("(null)", ctx);
        }
        return std::formatter<std::string_view>::format(
            reinterpret_cast<const char*>(str), 
            ctx
        );
    }
};

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

    class VOLUND_API Logger
    {
    public:
        static Logger& GetCoreLogger();
        static Logger& GetClientLogger();
        void WriteString(LogSeverity severity, std::string const& string);    
        template<typename... Args>
        void Log(LogSeverity severity, std::format_string<Args...> fmt, Args&&... args) 
        {
            this->WriteString(severity, std::format(fmt, std::forward<Args>(args)...));
        }
        void AddListener(std::ostream* stream);
        void RemoveListener(std::ostream* stream);
        Logger(std::string const& name);
    private:
        static Logger m_coreLogger;
        static Logger m_clientLogger;

        std::vector<std::ostream*> m_listeners;
        std::string m_name;
    };

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

#define VOLUND_LOG_LOADING(assetType, path) \
    VOLUND_INFO("Loading {} '{}'", assetType, path)

#define VOLUND_LOG_LOADING_SUCCESS(assetType, path) \
    VOLUND_INFO("Successfully loaded {} '{}'", assetType, path)

#define VOLUND_LOG_LOADING_FAIL(assetType, path, reason) \
    VOLUND_WARNING("Failed to load {} '{}' - {}", assetType, path, reason)
