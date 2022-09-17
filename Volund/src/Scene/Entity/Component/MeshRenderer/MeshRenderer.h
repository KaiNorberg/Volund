#pragma once

#include "../Component.h"

#include "Scene/AssetLibrary/Asset/Material/MaterialAsset.h"
#include "Scene/AssetLibrary/Asset/Mesh/MeshAsset.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:
		void OnUpdate(TimeStep TS) override;

		VML Serialize() override;

		void SetMesh(Ref<MeshAsset> _NewMesh);

		void SetMaterial(Ref<MaterialAsset> _NewMaterial);

		const Ref<MeshAsset> GetMesh();

		const Ref<MaterialAsset> GetMaterial();

		MeshRenderer(Ref<MeshAsset> ObjectMesh, Ref<MaterialAsset> ObjectMaterial);

	private:
		Ref<MeshAsset> _Mesh;
		Ref<MaterialAsset> _Material;
	};
}
