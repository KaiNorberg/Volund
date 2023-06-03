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
		if (layer > 0 && layer <= 16)
		{
			this->m_LayerMask |= 1UL << (layer - 1);
		}
	}

	uint16_t MeshRenderer::GetLayerMask()
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

		switch (e.Type)
		{
		case EventType::Render:
		{
			if (this->m_Mesh != nullptr && this->m_Material != nullptr)
			{
				/*RendererModel model;
				model.mesh = this->m_Mesh;
				model.material = this->m_Material;
				model.LayerMask = this->m_LayerMask;

				const auto transformComponent = this->GetScene()->GetComponent<Transform>(this->GetEntity());
				model.ModelMatrix = transformComponent != nullptr ? transformComponent->GetModelMatrix() : Mat4x4(1.0f);

				Renderer::Submit(model);*/
			}
		}
		break;
		default:
		{

		}
		break;
		}
	}

	MeshRenderer::MeshRenderer(Ref<Mesh> mesh, Ref<Material> material)
	{
		this->m_Mesh = mesh;
		this->m_Material = material;
	}
}
