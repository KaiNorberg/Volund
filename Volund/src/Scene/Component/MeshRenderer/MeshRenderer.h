#pragma once

#include "../Component.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class MeshRenderer : public Component
	{
	public:

		void SetLayer(uint8_t layer);

		void SetMesh(Ref<Mesh> newMesh);

		void SetMaterial(Ref<Material> newMaterial);

		Ref<Mesh> GetMesh();

		Ref<Material> GetMaterial();

		void Procedure(const Event& e);

		MeshRenderer() = default;

		MeshRenderer(Ref<Mesh> mesh, Ref<Material> material);

	private:

		uint16_t m_LayerMask = 1;

		Ref<Mesh> m_Mesh;
		Ref<Material> m_Material;
	};
}
