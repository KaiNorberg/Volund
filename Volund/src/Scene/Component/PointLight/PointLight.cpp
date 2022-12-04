#include "PCH/PCH.h"

#include "PointLight.h"

#include "Renderer/Renderer.h"
#include "Scene/Scene.h"

#include "Scene/Component/Transform/Transform.h"

namespace Volund
{
	void PointLight::OnUpdate(TimeStep TS)
	{
		Ref<Transform> EntityTransform = VL::Scene::GetComponent<Transform>(this->GetEntity());

		RendererLight Light;
		Light.Position = EntityTransform->Position;
		Light.Brightness = this->Brightness;
		Light.Color = this->Color;

		Renderer::Submit(Light);
	}

	PointLight::PointLight()
	{

	}
}
