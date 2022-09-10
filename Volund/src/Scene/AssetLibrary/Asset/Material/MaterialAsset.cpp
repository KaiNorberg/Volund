#include "PCH/PCH.h"
#include "MaterialAsset.h"

#include "Scene/AssetLibrary/Asset/Shader/ShaderAsset.h"

namespace Volund
{
	Ref<Material> MaterialAsset::Get()
	{
		return this->_Material;
	}

	MaterialAsset::MaterialAsset(AssetLibrary* Parent, const std::string& FilePath)
	{
		this->_Parent = Parent;

		this->_FilePath = FilePath;

		VML MaterialVML(FilePath);

		Ref<Shader> ObjectShader = Parent->GetAsset<ShaderAsset>(MaterialVML.Get("Shader").GetAs<std::string>())->Get();

		this->_Material = Material::Create(ObjectShader);
	}
}
