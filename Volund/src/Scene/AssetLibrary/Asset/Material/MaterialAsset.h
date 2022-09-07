#pragma once

#include "Renderer/Material/Material.h"
#include "Scene/AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class MaterialAsset : public Asset
	{
	public:

		Ref<Material> Get();

		MaterialAsset(AssetLibrary* Parent, std::string const& FilePath);

	private:

		Ref<Material> _Material;
	};
}