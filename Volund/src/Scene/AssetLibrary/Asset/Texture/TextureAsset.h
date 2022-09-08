#pragma once

#include "Renderer/Texture/Texture.h"
#include "Scene/AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class TextureAsset : public Asset
	{
	public:
		Ref<Texture> Get();

		TextureAsset(AssetLibrary* Parent, const std::string& FilePath);

	private:
		Ref<Texture> _Texture;
	};
}
