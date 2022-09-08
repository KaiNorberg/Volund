#pragma once

#include "Renderer/Material/Material.h"
#include "Scene/AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class MaterialAsset : public Asset
	{
	public:
		Ref<Material> Get();

		MaterialAsset(AssetLibrary* Parent, const std::string& FilePath);

	private:
		Ref<Material> _Material;
	};
}
