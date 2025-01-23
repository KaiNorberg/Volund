#pragma once

#define SOL_NO_EXCEPTIONS 0
#define SOL_PRINT_ERRORS 0
#define SOL_SAFE_NUMERICS 1

//#define VOLUND_ENABLE_PROFILING
//#define VOLUND_DISABLE_MULTITHREADING

#ifdef _WIN32
    #define VOLUND_PATH_SEPERATOR '\\'
    #define VOLUND_INVALID_PATH_SEPERATOR '/'
#else
    #define VOLUND_PATH_SEPERATOR '/'
    #define VOLUND_INVALID_PATH_SEPERATOR '\\'
#endif

#if defined(_MSC_VER)
    #ifdef VOLUND_BUILD
        #define VOLUND_API __declspec(dllexport)
    #else
        #define VOLUND_API __declspec(dllimport)
    #endif
#else
    #ifdef VOLUND_BUILD
        #define VOLUND_API __attribute__((visibility("default")))
    #else
        #define VOLUND_API
    #endif
#endif