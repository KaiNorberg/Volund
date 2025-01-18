#pragma once

#include "Scene/Component/Component.h"

namespace Volund
{
    class Tag : public Component
    {
    public:

        std::string string;

        Tag(std::string const& string = "");

    private:
    };
}
