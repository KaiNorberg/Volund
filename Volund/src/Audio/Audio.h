#pragma once

#define AL_LIBTYPE_STATIC

#include "OpenAL_Soft/include/al.h"
#include "OpenAL_Soft/include/alext.h"

#define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)
#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)

namespace Volund
{
    bool CheckALCErrors(const std::string& FileName, const std::uint_fast32_t Line, ALCdevice* Device);

    bool CheckALErrors(const std::string& FileName, const std::uint_fast32_t Line);

    template<typename alcFunction, typename... Params>
    auto alcCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alcFunction function,
        ALCdevice* device,
        Params... params)
        ->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
    {
        function(std::forward<Params>(params)...);
        return CheckALCErrors(filename, line, device);
    }

    template<typename alcFunction, typename ReturnType, typename... Params>
    auto alcCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alcFunction function,
        ReturnType& returnValue,
        ALCdevice* device,
        Params... params)
        ->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
    {
        returnValue = function(std::forward<Params>(params)...);
        return CheckALCErrors(filename, line, device);
    }

    template<typename alcFunction, typename... Params>
    auto alCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alcFunction function,
        Params... params)
        ->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
    {
        function(std::forward<Params>(params)...);
        return CheckALErrors(filename, line);
    }

    template<typename alcFunction, typename ReturnType, typename... Params>
    auto alCallImpl(const char* filename,
        const std::uint_fast32_t line,
        alcFunction function,
        ReturnType& returnValue,
        Params... params)
        ->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
    {
        returnValue = function(std::forward<Params>(params)...);
        return CheckALErrors(filename, line);
    }
}