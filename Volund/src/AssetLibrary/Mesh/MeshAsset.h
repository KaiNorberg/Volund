#pragma once

#include "Renderer/Mesh/Mesh.h"
#include "AssetLibrary/AssetLibrary.h"

namespace Volund
{
	class MeshAsset : public Asset
	{
	public:

		Ref<Mesh> Get();

		MeshAsset(AssetLibrary* Parent, std::string const& FilePath);

	private:

		Ref<Mesh> _Mesh;
	};
}