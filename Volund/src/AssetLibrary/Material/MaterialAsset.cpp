#include "PCH/PCH.h"
#include "MaterialAsset.h"

#include "AssetLibrary/Shader/ShaderAsset.h"

#include "Scene/Scene.h"

namespace Volund
{
	Ref<Material> MaterialAsset::Get()
	{
		return this->_Material;
	}

	MaterialAsset::MaterialAsset(AssetLibrary* Parent, std::string const& FilePath)
	{
		this->_FilePath = FilePath;

		JSON MaterialJSON = JSON::Load(FilePath);

		Ref<Shader> ObjectShader = Parent->GetAsset<ShaderAsset>(MaterialJSON["Shader"].GetAs<std::string>())->Get();

		this->_Material = Material::Create(ObjectShader);
	}
}