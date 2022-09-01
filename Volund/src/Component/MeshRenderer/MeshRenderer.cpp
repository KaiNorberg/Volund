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
		Mat4x4 IdentityMatrix = Mat4x4(1.0f);

		Renderer::Submit(EntityTransform->GetModelMatrix(), this->_Mesh, this->_Shader);
	}

	MeshRenderer::MeshRenderer(Ref<Mesh> DrawMesh, Ref<Shader> DrawShader)
	{
		this->_Mesh = DrawMesh;
		this->_Shader = DrawShader;
	}
}