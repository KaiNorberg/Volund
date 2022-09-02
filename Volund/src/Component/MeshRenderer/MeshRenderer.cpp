#include "PCH/PCH.h"
#include "MeshRenderer.h"

#include "Renderer/Renderer.h"

#include "Component/Transform/Transform.h"

namespace Volund
{
	void MeshRenderer::OnUpdate(TimeStep TS)
	{
		VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(), "MeshRenderer unable to find a Transform component!");

		Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();
		Mat4x4 ModelMatrix = EntityTransform->GetModelMatrix();

		Renderer::Submit(ModelMatrix, this->_Mesh, this->_Material);
	}

	MeshRenderer::MeshRenderer(Ref<Mesh> ObjectMesh, Ref<Material> ObjectMaterial)
	{
		this->_Mesh = ObjectMesh;
		this->_Material = ObjectMaterial;
	}
}