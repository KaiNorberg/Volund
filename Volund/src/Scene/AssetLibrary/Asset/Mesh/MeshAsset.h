#pragma once

#include "Renderer/Mesh/Mesh.h"
#include "Scene/AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class MeshAsset : public Asset
	{
	public:
		Ref<Mesh> Get();

		MeshAsset(AssetLibrary* Parent, const std::string& FilePath);

	private:
		Ref<Mesh> _Mesh;
	};
}
