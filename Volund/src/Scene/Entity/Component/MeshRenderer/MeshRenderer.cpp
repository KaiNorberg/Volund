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

	JSON MeshRenderer::Serialize()
	{
		JSON MeshRendererJSON;

		MeshRendererJSON.AddEntry("Type", "MeshRenderer");

		MeshRendererJSON.AddEntry("Mesh", this->_Mesh->GetFilePath());
		MeshRendererJSON.AddEntry("Material", this->_Material->GetFilePath());

		return MeshRendererJSON;
	}

	MeshRenderer::MeshRenderer(Ref<MeshAsset> ObjectMesh, Ref<MaterialAsset> ObjectMaterial)
	{
		this->_Mesh = ObjectMesh;
		this->_Material = ObjectMaterial;
	}
}
