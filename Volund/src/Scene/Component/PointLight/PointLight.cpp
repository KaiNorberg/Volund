#include "PCH/PCH.h"

#include "PointLight.h"

#include "Renderer/Renderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

namespace Volund
{
	void PointLight::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Render:
		{
			const Ref<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			RendererLight light;
			light.Position = entityTransform->Position;
			light.Brightness = this->Brightness;
			light.Color = this->Color;

			Renderer::Submit(light);
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
