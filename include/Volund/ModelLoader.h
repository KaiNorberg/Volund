#pragma once

#include "AABB.h"

namespace Volund
{
    class VOLUND_API ModelLoader
    {
    public:
        std::vector<float> Vertices;
        std::vector<uint32_t> Indices;
        bool Valid();
        void ParseOBJ(std::string const& content);
        void LoadFile(std::string const& filepath);
    private:
        bool m_valid;
    };
}
