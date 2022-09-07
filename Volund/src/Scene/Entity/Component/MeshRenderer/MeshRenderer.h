#pragma once

#include "../Component.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Material/Material.h"

#include "Scene/AssetLibrary/Asset/Material/MaterialAsset.h"
#include "Scene/AssetLibrary/Asset/Mesh/MeshAsset.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void OnUpdate(TimeStep TS) override;

		JSON Serialize() override;

		MeshRenderer(Ref<MeshAsset> ObjectMesh, Ref<MaterialAsset> ObjectMaterial);

	private:

		Ref<MeshAsset> _Mesh;
		Ref<MaterialAsset> _Material;
	};
}