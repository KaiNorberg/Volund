#include "Component/MeshRenderer.h"

#include "Scene.h"
#include "Component/Transform.h"

#include "Rendering/Renderer.h"

namespace Volund
{
	bool MeshRenderer::IsValid()
	{
		return this->m_mesh != nullptr && this->m_material != nullptr;
	}

	void MeshRenderer::SetLayer(const uint8_t layer)
	{
		this->m_layerMask = 0;
		if (layer > 0 && layer <= 32)
		{
			this->m_layerMask |= 1UL << (layer - 1);
		}
	}

	uint32_t MeshRenderer::GetLayerMask()
	{
		return this->m_layerMask;
	}

	void MeshRenderer::SetMesh(const std::shared_ptr<Mesh> newMesh)
	{
		this->m_mesh = newMesh;
	}

	void MeshRenderer::SetMaterial(const std::shared_ptr<Material> newMaterial)
	{
		this->m_material = newMaterial;
	}

	std::shared_ptr<Mesh> MeshRenderer::GetMesh()
	{
		return this->m_mesh;
	}

	std::shared_ptr<Material> MeshRenderer::GetMaterial()
	{
		return this->m_material;
	}

	void MeshRenderer::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	{
		this->m_mesh = mesh;
		this->m_material = material;
	}
}