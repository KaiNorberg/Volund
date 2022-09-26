#include "PCH/PCH.h"

#include "PointLight.h"

#include "Renderer/Renderer.h"
#include "Scene/Scene.h"

#include "Scene/Component/Transform/Transform.h"

namespace Volund
{
	void PointLight::OnUpdate(TimeStep TS)
	{
		Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		RendererLight Light;
		Light.Position = EntityTransform->Position;
		Light.Brightness = this->Brightness;
		Light.Color = this->Color;

		Renderer::Submit(Light);
	}

	VML PointLight::Serialize()
	{
		VML PointLightVML;

		PointLightVML.PushBack("Type", VMLEntry("PointLight"));

		PointLightVML.PushBack("Color", VMLEntry({ this->Color.r, this->Color.g, this->Color.b }));

		PointLightVML.PushBack("Brightness", VMLEntry(this->Brightness));

		return PointLightVML;
	}

	PointLight::PointLight(RGB Color, float Brightness)
	{
		this->Color = Color;
		this->Brightness = Brightness;
	}
}
