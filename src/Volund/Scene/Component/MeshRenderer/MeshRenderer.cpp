#include "MeshRenderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

//#include "Rendering/Renderer.h"

namespace Volund
{
	bool MeshRenderer::IsValid()
	{
		return this->m_Mesh != nullptr && this->m_Material != nullptr;
	}

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

	void MeshRenderer::SetMesh(const std::shared_ptr<Mesh> newMesh)
	{
		this->m_Mesh = newMesh;
	}

	void MeshRenderer::SetMaterial(const std::shared_ptr<Material> newMaterial)
	{
		this->m_Material = newMaterial;
	}

	std::shared_ptr<Mesh> MeshRenderer::GetMesh()
	{
		return this->m_Mesh;
	}

	std::shared_ptr<Material> MeshRenderer::GetMaterial()
	{
		return this->m_Material;
	}

	void MeshRenderer::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	{
		this->m_Mesh = mesh;
		this->m_Material = material;
	}
}
