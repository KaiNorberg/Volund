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
		this->_FilePath = FilePath;

		this->_Shader = Shader::Create(FilePath);
	}
}
