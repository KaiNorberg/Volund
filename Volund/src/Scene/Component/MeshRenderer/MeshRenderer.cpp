#include "PCH/PCH.h"
#include "MeshRenderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

#include "Renderer/Renderer.h"

namespace Volund
{
	void MeshRenderer::OnRender()
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->_Mesh != nullptr && this->_Material != nullptr)
		{
			RendererCommand Command;
			Command.mesh = this->_Mesh;
			Command.material = this->_Material;

			auto TransformComponent = this->GetScene()->GetComponent<Transform>(this->GetEntity());
			Command.ModelMatrix = TransformComponent != nullptr ? TransformComponent->GetModelMatrix() : Mat4x4(1.0f);

			Renderer::Submit(Command);
		}
	}

	void MeshRenderer::SetMesh(Ref<Mesh> NewMesh)
	{
		this->_Mesh = NewMesh;
	}

	void MeshRenderer::SetMaterial(Ref<Material> NewMaterial)
	{
		this->_Material = NewMaterial;
	}

	Ref<Mesh> MeshRenderer::GetMesh()
	{
		return this->_Mesh;
	}

	Ref<Material> MeshRenderer::GetMaterial()
	{
		return this->_Material;
	}

	MeshRenderer::MeshRenderer(Ref<Mesh> MeshRef, Ref<Material> MaterialRef)
	{
		this->_Mesh = MeshRef;
		this->_Material = MaterialRef;
	}
}
