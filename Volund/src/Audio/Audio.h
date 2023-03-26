#pragma once

#define AL_LIBTYPE_STATIC

#include "OpenAL_Soft/include/al.h"
#include "OpenAL_Soft/include/alext.h"

#define ALC_CALL(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)
#define AL_CALL(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)

namespace Volund
{
    bool CheckAlcErrors(const std::string& fileName, const std::uint_fast32_t line, ALCdevice* device);

    bool CheckAlErrors(const std::string& fileName, const std::uint_fast32_t line);

    template<typename AlcFunction, typename... Params>
    auto alcCallImpl(const char* filename,
        const std::uint_fast32_t line,
        AlcFunction function,
        ALCdevice* device,
        Params... params)
        ->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
    {
        function(std::forward<Params>(params)...);
        return CheckAlcErrors(filename, line, device);
    }

    template<typename AlcFunction, typename ReturnType, typename... Params>
    auto alcCallImpl(const char* filename,
        const std::uint_fast32_t line,
        AlcFunction function,
        ReturnType& returnValue,
        ALCdevice* device,
        Params... params)
        ->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
    {
        returnValue = function(std::forward<Params>(params)...);
        return CheckAlcErrors(filename, line, device);
    }

    template<typename AlcFunction, typename... Params>
    auto alCallImpl(const char* filename,
        const std::uint_fast32_t line,
        AlcFunction function,
        Params... params)
        ->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
    {
        function(std::forward<Params>(params)...);
        return CheckAlErrors(filename, line);
    }

    template<typename AlcFunction, typename ReturnType, typename... Params>
    auto alCallImpl(const char* filename,
        const std::uint_fast32_t line,
        AlcFunction function,
        ReturnType& returnValue,
        Params... params)
        ->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
    {
        returnValue = function(std::forward<Params>(params)...);
        return CheckAlErrors(filename, line);
    }
}