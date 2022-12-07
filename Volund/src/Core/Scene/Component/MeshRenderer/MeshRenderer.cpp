#include "PCH/PCH.h"
#include "MeshRenderer.h"

#include "Core/Scene/Scene.h"
#include "Core/Scene/Component/Transform/Transform.h"

#include "Renderer/Renderer.h"

namespace Volund
{
	void MeshRenderer::OnUpdate(TimeStep TS)
	{
		if (this->_Mesh != nullptr && this->_Material != nullptr)
		{
			RendererCommand Command;
			Command.mesh = this->_Mesh;
			Command.material = this->_Material;

			if (VL::Scene::HasComponent<Transform>(this->GetEntity()))
			{
				Command.ModelMatrix = VL::Scene::GetComponent<Transform>(this->GetEntity())->GetModelMatrix();
			}
			else
			{
				Command.ModelMatrix = Mat4x4(1.0f);
			}

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
