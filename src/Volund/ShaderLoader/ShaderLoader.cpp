#include "ShaderLoader.h"

#include "ResourceLibrary/ResourceLibrary.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Shader/Shader.h"

#include <fstream>

namespace Volund
{
	ShaderSource ShaderLoader::GetSource()
	{
		return this->m_source;
	}

	std::shared_ptr<MaterialBlueprint> ShaderLoader::GetBlueprint()
	{
		return this->m_materialBlueprint;
	}

	void ShaderLoader::Load(std::string const& filepath)
	{
        std::stringstream stringStream;
        if (ResourceLibrary::IsResource(filepath))
        {
            stringStream << ResourceLibrary::Fetch(filepath);
        }
        else
        {
            std::ifstream file(filepath);

            if (!file)
            {
                VOLUND_WARNING("Failed to load shader %s!", filepath.c_str());
                return;
            }

            stringStream << file.rdbuf();
        }

        std::string line;
        ShaderSourceType type = ShaderSourceType::None;
        bool inMaterial = false;

        while (std::getline(stringStream, line))
        {
            if (line.empty())
            {
                continue;
            }

            auto words = Utils::SplitString(line, ' ');

            if (words[0].starts_with("#VOLUND"))
            {
                if (words[0] == "#VOLUND_SHADER_TYPE")
                {
                    if (words.size() == 2)
                    {
                        if (words[1] == "VERTEX")
                        {
                            type = ShaderSourceType::Vertex;
                        }
                        else if (words[1] == "FRAGMENT")
                        {
                            type = ShaderSourceType::Fragment;
                        }
                        else if (words[1] == "GEOMETRY")
                        {
                            type = ShaderSourceType::Geometry;
                        }
                    }
                    else
                    {
                        VOLUND_WARNING("Corrupt volund directive detected in shader file (%s), unknown shader type!", filepath.c_str());
                    }
                }
                else if (words[0] == "#VOLUND_MATERIAL_START")
                {
                    if (!inMaterial)
                    {
                        inMaterial = true;
                    }
                    else
                    {
                        VOLUND_WARNING("Corrupt volund directive detected in shader file (%s), inMaterial = true!", filepath.c_str());
                    }
                }
                else if (words[0] == "#VOLUND_MATERIAL_END")
                {
                    if (inMaterial)
                    {
                        inMaterial = false;
                    }
                    else
                    {
                        VOLUND_WARNING("Corrupt volund directive detected in shader file (%s), inMaterial = false!", filepath.c_str());
                    }
                }
                else
                {
                    VOLUND_WARNING("Corrupt volund directive detected in shader file (%s), unknown volund directive!", filepath.c_str());
                }
            }
            else
            {
                if (inMaterial && words.size() == 3 && words[0] == "uniform")
                {
                    std::string uniformName = std::string(words[2].begin(), words[2].end() - 1);
                    std::string uniformType = std::string(words[1]);

                    if (words[1] == "int" || words[1] == "bool")
                    {
                        this->m_materialBlueprint->Insert<IntUniformType>(uniformName);
                    }
                    else if (words[1] == "float")
                    {
                        this->m_materialBlueprint->Insert<FloatUniformType>(uniformName);
                    }
                    else if (words[1] == "double")
                    {
                        this->m_materialBlueprint->Insert<DoubleUniformType>(uniformName);
                    }
                    else if (words[1].ends_with("vec2"))
                    {
                        this->m_materialBlueprint->Insert<Vec2UniformType>(uniformName);
                    }
                    else if (words[1].ends_with("vec3"))
                    {
                        this->m_materialBlueprint->Insert<Vec3UniformType>(uniformName);
                    }
                    else if (words[1].ends_with("vec4"))
                    {
                        this->m_materialBlueprint->Insert<Vec4UniformType>(uniformName);
                    }
                    else if (words[1].starts_with("sampler"))
                    {
                        this->m_materialBlueprint->Insert<TextureUniformType>(uniformName);
                    }
                    /*else if (words[1].starts_with("mat3"))
                    {
                        this->m_materialBlueprint->Insert<UniformMat3x3>(uniformName);
                    }*/
                    else if (words[1].starts_with("mat4"))
                    {
                        this->m_materialBlueprint->Insert<Mat4x4UniformType>(uniformName);
                    }
                    else
                    {
                        VOLUND_WARNING("Corrupt uniform type detected in shader file (%s)!", filepath.c_str());
                    }
                }

                m_source[(int32_t)type] += line + '\n';
            }
        }
	}

    ShaderLoader::ShaderLoader()
    {
        this->m_materialBlueprint = std::make_shared<MaterialBlueprint>();
    }

	ShaderLoader::ShaderLoader(std::string const& filepath)
	{
        this->m_materialBlueprint = std::make_shared<MaterialBlueprint>();

		this->Load(filepath);
	}
}
