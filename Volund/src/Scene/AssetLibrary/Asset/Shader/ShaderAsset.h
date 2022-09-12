#pragma once

#include "Renderer/Shader/Shader.h"
#include "Scene/AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class ShaderAsset : public Asset
	{
	public:
		Ref<Shader> Get();

		ShaderAsset(AssetLibrary* Parent, const std::string& FilePath);

	private:

		Ref<Shader> _Shader;
	};
}
