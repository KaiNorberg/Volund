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

		Renderer::Submit(ModelMatrix, this->_Mesh->Get(), this->_Material->Get());
	}

	VML MeshRenderer::Serialize()
	{
		VML MeshRendererVML;

		MeshRendererVML.PushBack("Type", VMLEntry("MeshRenderer"));

		MeshRendererVML.PushBack("Mesh", VMLEntry(this->_Mesh->GetFilePath()));
		MeshRendererVML.PushBack("Material", VMLEntry(this->_Material->GetFilePath()));

		return MeshRendererVML;
	}

	MeshRenderer::MeshRenderer(Ref<MeshAsset> ObjectMesh, Ref<MaterialAsset> ObjectMaterial)
	{
		this->_Mesh = ObjectMesh;
		this->_Material = ObjectMaterial;
	}
}
