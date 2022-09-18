#include "PCH/PCH.h"
#include "MeshRenderer.h"

#include "Renderer/Renderer.h"

#include "Scene/Entity/Component/Transform/Transform.h"

namespace Volund
{
	void MeshRenderer::OnUpdate(TimeStep TS)
	{
		VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(),
		              "MeshRenderer unable to find a Transform component!");

		Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();
		Mat4x4 ModelMatrix = EntityTransform->GetModelMatrix();

		Renderer::Submit(ModelMatrix, this->_Mesh, this->_Material);
	}

	VML MeshRenderer::Serialize()
	{
		VML MeshRendererVML;

		MeshRendererVML.PushBack("Type", VMLEntry("MeshRenderer"));

		MeshRendererVML.PushBack("Mesh", VMLEntry(this->_Mesh->GetFilePath()));
		MeshRendererVML.PushBack("Material", VMLEntry(this->_Material->GetFilePath()));

		return MeshRendererVML;
	}

	void MeshRenderer::SetMesh(Ref<Mesh> _NewMesh)
	{
		this->_Mesh = _NewMesh;
	}

	void MeshRenderer::SetMaterial(Ref<Material> _NewMaterial)
	{
		this->_Material = _NewMaterial;
	}

	const Ref<Mesh>& MeshRenderer::GetMesh()
	{
		return this->_Mesh;
	}

	const Ref<Material>& MeshRenderer::GetMaterial()
	{
		return this->_Material;
	}

	MeshRenderer::MeshRenderer(std::string_view MeshFilePath, std::string_view MaterialFilePath)
	{
		this->_Mesh = Mesh::Create(MeshFilePath);
		this->_Material = Material::Create(MaterialFilePath);
	}
}
