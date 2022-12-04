#pragma once

#include "../Component.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void OnUpdate(TimeStep TS) override;

		void SetMesh(Ref<Mesh> NewMesh);

		void SetMaterial(Ref<Material> NewMaterial);

		Ref<Mesh> GetMesh();

		Ref<Material> GetMaterial();

		MeshRenderer() = default;

		MeshRenderer(Ref<Mesh> MeshRef, Ref<Material> MaterialRef);

	private:
		Ref<Mesh> _Mesh;
		Ref<Material> _Material;
	};
}
