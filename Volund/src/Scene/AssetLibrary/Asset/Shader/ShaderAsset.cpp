#include "PCH/PCH.h"
#include "ShaderAsset.h"

namespace Volund
{
	Ref<Shader> ShaderAsset::Get()
	{
		return this->_Shader;
	}

	ShaderAsset::ShaderAsset(AssetLibrary* Parent, const std::string& FilePath)
	{
		this->_Parent = Parent;

		this->_FilePath = FilePath;

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1,
			GEOMETRY = 2
		};

		VOLUND_INFO("Loading Shader (%s)...", FilePath.c_str());

		std::ifstream File(FilePath);

		VOLUND_ASSERT(File, "Unable to load Shader (%s).", FilePath.c_str());

		std::string Line;
		std::stringstream SourceStrings[3];
		ShaderType Type = ShaderType::NONE;

		while (std::getline(File, Line))
		{
			//Split into words
			std::vector<std::string> Words;
			std::istringstream ISS(Line);
			std::copy(std::istream_iterator<std::string>(ISS), std::istream_iterator<std::string>(),
				std::back_inserter(Words));

			if (Words.size() <= 0)
			{
				continue;
			}

			if (Words.size() >= 2 && Words[0] == "#VOLUND_SHADER_TYPE")
			{
				if (Words[1] == "VERTEX")
				{
					Type = ShaderType::VERTEX;
				}
				else if (Words[1] == "FRAGMENT")
				{
					Type = ShaderType::FRAGMENT;
				}
				else if (Words[1] == "GEOMETRY")
				{
					Type = ShaderType::GEOMETRY;
				}
			}
			else if ((int32_t)Type != -1)
			{
				SourceStrings[(int32_t)Type] << Line << '\n';
			}
		}

		this->_Shader = Shader::Create(
			SourceStrings[(uint32_t)ShaderType::VERTEX].str(), 
			SourceStrings[(uint32_t)ShaderType::FRAGMENT].str(),
			SourceStrings[(uint32_t)ShaderType::GEOMETRY].str());
	}
}
