#include "PCH/PCH.h"

#include "Camera.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"
#include "Window/Window.h"

#include "Renderer/Renderer.h"

namespace Volund
{
	Mat4x4 Camera::GetViewMatrix() const
	{
		Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		if (EntityTransform != nullptr)
		{
			return lookAt(EntityTransform->Position, EntityTransform->Position + EntityTransform->GetFront(),
				EntityTransform->GetUp());
		}
		else
		{
			return lookAt(Vec3(0.0f), Vec3(0.0f),
				Vec3(0.0f));
		}
	}

	Mat4x4 Camera::GetOriginViewMatrix() const
	{
		Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		if (EntityTransform != nullptr)
		{
			return lookAt(Vec3(0.0f), EntityTransform->GetFront(), EntityTransform->GetUp());
		}
		else
		{
			return lookAt(Vec3(0.0f), Vec3(0.0f),
				Vec3(0.0f));
		}
	}

	Mat4x4 Camera::GetProjectionMatrix(float AspectRatio) const
	{
		if (abs(AspectRatio - std::numeric_limits<float>::epsilon()) > 0.0f)
		{
			return glm::perspective(glm::radians(this->FOV), AspectRatio, this->NearPlane, this->FarPlane);
		}
		else
		{
			return Mat4x4(1.0f);
		}
	}

	void Camera::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::RENDER:
		{
			auto TargetBuffer = this->GetScene()->GetTargetBuffer();
			auto Spec = TargetBuffer->GetSpec();

			RendererEye Eye;
			Eye.Target = TargetBuffer;
			Eye.ProjectionMatrix = this->GetProjectionMatrix((float)Spec.Width / (float)Spec.Height);
			Eye.ViewMatrix = this->GetViewMatrix();

			Renderer::Submit(Eye);
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
