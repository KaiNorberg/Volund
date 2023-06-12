#include "PCH/PCH.h"

#include "Camera.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"
#include "Window/Window.h"

//#include "Rendering/Renderer.h"

namespace Volund
{
	void Camera::SetLayerMask(const uint8_t index, const bool enabled)
	{
		if (index > 0 && index <= 16)
		{
			if (enabled)
			{
				this->m_LayerMask |= 1UL << (index - 1);
			}
			else
			{
				this->m_LayerMask &= ~(1UL << (index - 1));
			}
		}
	}

	uint16_t Camera::GetLayerMask()
	{
		return this->m_LayerMask;
	}

	void Camera::SetTargetBuffer(const Ref<Framebuffer> newTargetBuffer)
	{
		this->m_TargetBuffer = newTargetBuffer;
	}

	Ref<Framebuffer> Camera::GetTargetBuffer()
	{
		return this->m_TargetBuffer;
	}

	Mat4x4 Camera::GetViewMatrix() const
	{
		const Ref<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		if (entityTransform != nullptr)
		{
			return lookAt(entityTransform->Position, entityTransform->Position + entityTransform->GetFront(),
				entityTransform->GetUp());
		}
		else
		{
			return lookAt(Vec3(0.0f), Vec3(0.0f, 1.0, 0.0),
				Vec3(0.0f));
		}
	}

	Mat4x4 Camera::GetOriginViewMatrix() const
	{
		const Ref<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		if (entityTransform != nullptr)
		{
			return lookAt(Vec3(0.0f), entityTransform->GetFront(), entityTransform->GetUp());
		}
		else
		{
			return lookAt(Vec3(0.0f), Vec3(0.0f),
				Vec3(0.0f));
		}
	}

	Mat4x4 Camera::GetProjectionMatrix(const float aspectRatio) const
	{
		if (abs(aspectRatio - std::numeric_limits<float>::epsilon()) > 0.0f)
		{
			return glm::perspective(glm::radians(this->FOV), aspectRatio, this->NearPlane, this->FarPlane);
		}
		else
		{
			return Mat4x4(1.0f);
		}
	}

	void Camera::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Render:
		{				
			/*const Ref<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			VOLUND_ASSERT(entityTransform != nullptr, "Camera component unable to retrive transform component!");		

			RendererEye eye;
			eye.Target = this->m_TargetBuffer;
			eye.ProjectionMatrix = this->GetProjectionMatrix((float)spec.Width / (float)spec.Height);
			eye.ViewMatrix = this->GetViewMatrix();
			eye.Position = entityTransform->Position;
			eye.LayerMask = this->m_LayerMask;

			Renderer::Submit(eye);*/
		}
		break;
		default:
		{

		}
		break;
		}
	}

	void Camera::OnCreate()
	{

	}
}
