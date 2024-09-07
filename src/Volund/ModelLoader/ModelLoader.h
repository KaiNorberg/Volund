#pragma once

#include "AABB/AABB.h"

namespace Volund
{
    class ModelLoader
    {
    public:
        
        std::vector<float> Vertices;
        std::vector<uint32_t> Indices;

        bool Valid();

        void ParseOBJ(const std::string& content);
        
        void LoadFile(const std::string& filepath);

    private:
        
        bool m_Valid;
    };
}
