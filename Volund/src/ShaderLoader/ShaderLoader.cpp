#include "PCH/PCH.h"
#include "ShaderLoader.h"

#include "ResourceLibrary/ResourceLibrary.h"

namespace Volund
{
	ShaderSource ShaderLoader::GetSource()
	{
		return this->m_Source;
	}

	Ref<MaterialBlueprint> ShaderLoader::GetBlueprint()
	{
		return this->m_MaterialBlueprint;
	}

	void ShaderLoader::Load(const std::string& filepath)
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
                    MaterialUniformType uniformType;
                    if (words[1] == "int" || words[1] == "uint" || words[1] == "bool")
                    {
                        uniformType = MaterialUniformType::Int;
                    }
                    else if (words[1] == "double")
                    {
                        uniformType = MaterialUniformType::Double;
                    }
                    else if (words[1].ends_with("vec2"))
                    {
                        uniformType = MaterialUniformType::Vec2;
                    }
                    else if (words[1].ends_with("vec3"))
                    {
                        uniformType = MaterialUniformType::Vec3;
                    }
                    else if (words[1].ends_with("vec4"))
                    {
                        uniformType = MaterialUniformType::Vec4;
                    }
                    else if (words[1].starts_with("sampler"))
                    {
                        uniformType = MaterialUniformType::Sampler;
                    }
                    else if (words[1].starts_with("mat4"))
                    {
                        uniformType = MaterialUniformType::Matrix;
                    }
                    else if (words[1] == "float")
                    {
                        VOLUND_WARNING("Float is temporarily not a supported uniform type, for now use double instead (%s)!", filepath.c_str());
                    }
                    else
                    {
                        VOLUND_WARNING("Corrupt uniform type detected in shader file (%s)!", filepath.c_str());
                    }

                    std::string uniformName = std::string(words[2].begin(), words[2].end() - 1);

                    this->m_MaterialBlueprint->AddUniform(uniformName, uniformType);
                }

                m_Source[(int32_t)type] += line + '\n';
            }
        }
	}

    ShaderLoader::ShaderLoader()
    {
        this->m_MaterialBlueprint = std::make_shared<MaterialBlueprint>();
    }

	ShaderLoader::ShaderLoader(const std::string& filepath)
	{
        this->m_MaterialBlueprint = std::make_shared<MaterialBlueprint>();

		this->Load(filepath);
	}
}