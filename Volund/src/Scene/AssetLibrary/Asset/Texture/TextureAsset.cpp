#include "PCH/PCH.h"
#include "TextureAsset.h"

namespace Volund
{
	Ref<Texture> TextureAsset::Get()
	{
		return this->_Texture;
	}

	TextureAsset::TextureAsset(AssetLibrary* Parent, const std::string& FilePath)
	{
		this->_Parent = Parent;

		this->_FilePath = FilePath;

		this->_Texture = Texture::Create(FilePath);
	}
}
