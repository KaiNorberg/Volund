#pragma once

#include "Math/Vec/Vec.h"

namespace Volund::Console
{
    /// <summary>
    /// Console color codes
    /// </summary>
    enum class ConsoleColor 
    {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };

    std::ostream& operator<<(std::ostream& os, ConsoleColor code);

    /// <summary>
    /// Returns the current time in as a string.
    /// </summary>
    const std::string GetStringTime();

    /// <summary>
    /// Moves the console down one line.
    /// </summary>
    void EndLog();

    /// <summary>
    /// Prints the given vector to the console.
    /// </summary>
    template<int L, typename T>
    void Log(Vec<L, T> const& Vec)
    {
        std::cout << ConsoleColor::FG_RED << GetStringTime() << ConsoleColor::FG_GREEN << " ";

        for (uint32_t i = 0; i < Vec.Length(); i++)
        {
            if (i < 3)
            {
                std::cout << ((char)('X' + i)) << ": " << Vec[i] << " | ";
            }
            else
            {
                std::cout << "W: " << Vec[i] << " ";
            }
        }

        std::cout << "\n";
    }

    /// <summary>
    /// Prints the given variables to the console.
    /// </summary>
    template<class... ARGS>
    void Log(ARGS... Args)
    {
        std::cout << ConsoleColor::FG_RED << GetStringTime() << ConsoleColor::FG_GREEN << "Volund: ";        
        (std::cout << ... << Args) << '\n';
    }

    /// <summary>
    /// Prints the given variables and and shuts down the program.
    /// </summary>
    template<class... ARGS>
    void LogError(ARGS... Args)
    {
        std::cout << ConsoleColor::FG_RED << GetStringTime() << "Volund Error: ";
        (std::cout << ... << Args) << '\n';
        std::cin.get();
        exit(EXIT_FAILURE);
    }

    /// <summary>
    /// Prints the given variables as a warning.
    /// </summary>
    template<class... ARGS>
    void LogWarning(ARGS... Args)
    {
        std::cout << ConsoleColor::FG_RED << GetStringTime() << ConsoleColor::FG_YELLOW << "Volund Warning: ";
        (std::cout << ... << Args) << '\n';
    }

} //namespace Volund