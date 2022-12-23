#include "PCH/PCH.h"

#include "PointLight.h"

#include "Renderer/Renderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

namespace Volund
{
	void PointLight::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::RENDER:
		{
			Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			RendererLight Light;
			Light.Position = EntityTransform->Position;
			Light.Brightness = this->Brightness;
			Light.Color = this->Color;

			Renderer::Submit(Light);
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
