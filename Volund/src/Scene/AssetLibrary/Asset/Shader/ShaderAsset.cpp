#include "PCH/PCH.h"
#include "ShaderAsset.h"

namespace Volund
{
	Ref<Shader> ShaderAsset::Get()
	{
		return this->_Shader;
	}

	ShaderAsset::ShaderAsset(AssetLibrary* Parent, std::string const& FilePath)
	{
		this->_FilePath = FilePath;

		this->_Shader = Shader::Create(FilePath);
	}
}