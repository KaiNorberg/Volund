#pragma once

#include "Renderer/Texture/Texture.h"
#include "AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class TextureAsset : public Asset
	{
	public:

		Ref<Texture> Get();

		TextureAsset(AssetLibrary* Parent, std::string const& FilePath);

	private:

		Ref<Texture> _Texture;
	};
}