#pragma once

#include "Renderer/Shader/Shader.h"
#include "AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class ShaderAsset : public Asset
	{
	public:

		Ref<Shader> Get();

		ShaderAsset(AssetLibrary* Parent, std::string const& FilePath);

	private:

		Ref<Shader> _Shader;
	};
}