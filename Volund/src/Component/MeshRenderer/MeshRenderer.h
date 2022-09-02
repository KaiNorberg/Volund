#pragma once

#include "Component/Component.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Material/Material.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void OnUpdate(TimeStep TS) override;

		MeshRenderer(Ref<Mesh> ObjectMesh, Ref<Material> ObjectMaterial);

	private:

		Ref<Mesh> _Mesh;
		Ref<Material> _Material;
	};
}