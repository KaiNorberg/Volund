#pragma once

#include "Math/Vec/Vec.h"

namespace Volund
{
    class Logger
    {
    public:

        VOLUND_API static Logger& GetCoreLogger();

        VOLUND_API static Logger& GetClientLogger();

        VOLUND_API void Info(const char* Format, ...);
        
        VOLUND_API void Warning(const char* Format, ...);

        VOLUND_API void Error(const char* Format, ...);

        Logger(std::string const& Name);

    private:   

        static Logger _CoreLogger;
        static Logger _ClientLogger;

        std::string _Name;
    };
}

#define VOLUND_CORE_INFO(...) ::Volund::Logger::GetCoreLogger().Info(__VA_ARGS__)
#define VOLUND_CORE_WARNING(...) ::Volund::Logger::GetCoreLogger().Warning(__VA_ARGS__)
#define VOLUND_CORE_ERROR(...) ::Volund::Logger::GetCoreLogger().Error(__VA_ARGS__)

#define VOLUND_CLIENT_INFO(...) ::Volund::Logger::GetClientLogger().Info(__VA_ARGS__)
#define VOLUND_CLIENT_WARNING(...) ::Volund::Logger::GetClientLogger().Warning(__VA_ARGS__)
#define VOLUND_CLIENT_ERROR(...) ::Volund::Logger::GetClientLogger().Error(__VA_ARGS__)
