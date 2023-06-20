#include "PCH/PCH.h"
#include "MeshRenderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

//#include "Rendering/Renderer.h"

namespace Volund
{
	void MeshRenderer::SetLayer(const uint8_t layer)
	{
		this->m_LayerMask = 0;
		if (layer > 0 && layer <= 32)
		{
			this->m_LayerMask |= 1UL << (layer - 1);
		}
	}

	uint32_t MeshRenderer::GetLayerMask()
	{
		return this->m_LayerMask;
	}

	void MeshRenderer::SetMesh(const Ref<Mesh> newMesh)
	{
		this->m_Mesh = newMesh;
	}

	void MeshRenderer::SetMaterial(const Ref<Material> newMaterial)
	{
		this->m_Material = newMaterial;
	}

	Ref<Mesh> MeshRenderer::GetMesh()
	{
		return this->m_Mesh;
	}

	Ref<Material> MeshRenderer::GetMaterial()
	{
		return this->m_Material;
	}

	void MeshRenderer::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	MeshRenderer::MeshRenderer(Ref<Mesh> mesh, Ref<Material> material)
	{
		this->m_Mesh = mesh;
		this->m_Material = material;
	}
}
