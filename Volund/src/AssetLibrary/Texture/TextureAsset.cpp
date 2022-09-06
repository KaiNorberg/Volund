#include "PCH/PCH.h"
#include "TextureAsset.h"

namespace Volund
{
	Ref<Texture> TextureAsset::Get()
	{
		return this->_Texture;
	}

	TextureAsset::TextureAsset(AssetLibrary* Parent, std::string const& FilePath)
	{
		this->_FilePath = FilePath;

		this->_Texture = Texture::Create(FilePath);
	}
}