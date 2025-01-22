#pragma once

#include "Rendering/MaterialBlueprint.h"

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

    class VOLUND_API ShaderLoader
    {
    public:
        ShaderSource GetSource();
        std::shared_ptr<MaterialBlueprint> GetBlueprint();
        void Load(std::string const& filepath);
        ShaderLoader();
        ShaderLoader(std::string const& filepath);
    private:
        ShaderSource m_source;
        std::shared_ptr<MaterialBlueprint> m_materialBlueprint;
    };
}
