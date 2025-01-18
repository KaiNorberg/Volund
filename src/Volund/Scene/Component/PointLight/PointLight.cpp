
#include "PointLight.h"

//#include "Rendering/Renderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

namespace Volund
{
	void PointLight::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.type)
		{
		case VOLUND_EVENT_RENDER:
		{
			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			/*RendererLight light;
			light.Position = entityTransform->Position;
			light.Brightness = this->Brightness;
			light.Color = this->Color;

			Renderer::Submit(light);*/
		}
		break;
		default:
		{

		}
		break;
		}
	}

	PointLight::PointLight()
	{

	}
}
