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

		MeshRendererVML.PushBack("Mesh", VMLEntry(this->_Mesh.GetFilePath()));
		MeshRendererVML.PushBack("Material", VMLEntry(this->_Material.GetFilePath()));

		return MeshRendererVML;
	}

	void MeshRenderer::SetMesh(Asset<Mesh> _NewMesh)
	{
		this->_Mesh = _NewMesh;
	}

	void MeshRenderer::SetMaterial(Asset<Material> _NewMaterial)
	{
		this->_Material = _NewMaterial;
	}

	const Asset<Mesh>& MeshRenderer::GetMesh()
	{
		return this->_Mesh;
	}

	const Asset<Material>& MeshRenderer::GetMaterial()
	{
		return this->_Material;
	}

	MeshRenderer::MeshRenderer(std::string_view MeshFilePath, std::string_view MaterialFilePath)
	{
		this->_Mesh = Asset<Mesh>::Load(MeshFilePath);
		this->_Material = Asset<Material>::Load(MaterialFilePath);
	}
}
