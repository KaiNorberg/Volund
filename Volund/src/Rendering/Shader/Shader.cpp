#include "PCH/PCH.h"

#include "Shader.h"

#include "OpenGLShader.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

namespace Volund
{
    const Ref<MaterialBlueprint> Shader::GetMaterialBlueprint()
    {
        return this->m_MaterialBlueprint;
    }

    Ref<Shader> Shader::Create(const std::string& filepath)
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
                return nullptr;
            }

            stringStream << file.rdbuf();
        }

        enum class ShaderType
        {
            None = -1,
            Vertex = 0,
            Fragment = 1,
            Geometry = 2
        };

        std::string line;
        std::stringstream sourceStrings[3];
        ShaderType type = ShaderType::None;
        Ref<MaterialBlueprint> materialBlueprint = std::make_shared<MaterialBlueprint>();
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
                            type = ShaderType::Vertex;
                        }
                        else if (words[1] == "FRAGMENT")
                        {
                            type = ShaderType::Fragment;
                        }
                        else if (words[1] == "GEOMETRY")
                        {
                            type = ShaderType::Geometry;
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
                    else if (words[1] == "float")
                    {
                        uniformType = MaterialUniformType::Float;
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
                    else
                    {
                        VOLUND_WARNING("Corrupt uniform type detected in shader file (%s)!", filepath.c_str());
                    }

                    std::string uniformName = std::string(words[2].begin(), words[2].end() - 1);

                    materialBlueprint->AddUniform(uniformName, uniformType);
                }

                sourceStrings[(int32_t)type] << line << '\n';
            }
        }

        auto newShader = Shader::Create(
            sourceStrings[(uint32_t)ShaderType::Vertex].str(),
            sourceStrings[(uint32_t)ShaderType::Fragment].str(),
            sourceStrings[(uint32_t)ShaderType::Geometry].str());

        newShader->m_MaterialBlueprint = materialBlueprint;

        return newShader;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLShader>(vertexSource, fragmentSource, geometrySource);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Shader without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}

    Shader::Shader()
    {
        this->m_MaterialBlueprint = std::make_shared<MaterialBlueprint>();
    }

} //namespace Volund
