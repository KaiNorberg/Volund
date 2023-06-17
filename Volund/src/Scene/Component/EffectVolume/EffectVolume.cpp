#include "PCH/PCH.h"
#include "EffectVolume.h"

namespace Volund
{
	void EffectVolume::Procedure(const Event& e)
	{
		/*VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case VOLUND_EVENT_TYPE_RENDER:
		{
			if (this->_Mesh != nullptr && this->_Material != nullptr)
			{
				RendererModel Model;
				Model.mesh = this->_Mesh;
				Model.material = this->_Material;
				Model.LayerMask = this->_LayerMask;

				auto TransformComponent = this->GetScene()->GetComponent<Transform>(this->GetEntity());
				Model.ModelMatrix = TransformComponent != nullptr ? TransformComponent->GetModelMatrix() : Mat4x4(1.0f);

				Renderer::Submit(Model);
			}
		}
		break;
		default:
		{

		}
		break;
		}*/
	}
}