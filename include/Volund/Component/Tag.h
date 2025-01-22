#pragma once

#include "Component.h"

namespace Volund
{
    class VOLUND_API Tag : public Component
    {
    public:
        std::string string;
        Tag(std::string const& string = "");
    private:
    };
}