#pragma once

#include "Rendering/Shader/MaterialBlueprint/MaterialBlueprint.h"

namespace Volund
{
    using ShaderSource = std::array<std::string, 3>;

    enum class ShaderSourceType
    {
        None = -1,
        Vertex = 0,
        Fragment = 1,
        Geometry = 2,
    };

    class ShaderLoader
    {
    public:

        ShaderSource GetSource();

        Ref<MaterialBlueprint> GetBlueprint();

        void Load(const std::string& filepath);

        ShaderLoader();

        ShaderLoader(const std::string& filepath);

    private:

        ShaderSource m_Source;

        Ref<MaterialBlueprint> m_MaterialBlueprint;
    };
}

