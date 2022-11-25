#include "PCH/PCH.h"

#include "Utils.h"

namespace Volund
{
    std::string ReplaceAll(std::string Str, const std::string& From, const std::string& To) 
    {
        size_t start_pos = 0;

        while ((start_pos = Str.find(From, start_pos)) != std::string::npos) 
        {
            Str.replace(start_pos, From.length(), To);
            start_pos += To.length();
        }

        return Str;
    }
}