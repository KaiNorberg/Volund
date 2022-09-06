#pragma once

#include "Component/Component.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Material/Material.h"

#include "AssetLibrary/Material/MaterialAsset.h"
#include "AssetLibrary/Mesh/MeshAsset.h"

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