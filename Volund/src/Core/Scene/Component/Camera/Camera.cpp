#include "PCH/PCH.h"

#include "Camera.h"

#include "Core/Scene/Scene.h"
#include "Core/Scene/Component/Transform/Transform.h"

namespace Volund
{
	bool Camera::IsActive() const
	{
		return _ActiveCamera == this;
	}

	void Camera::SetActive()
	{
		_ActiveCamera = this;
	}

	Camera* Camera::GetActiveCamera()
	{
		return _ActiveCamera;
	}

	Mat4x4 Camera::GetViewMatrix() const
	{
		VOLUND_ASSERT(VL::Scene::HasComponent<Transform>(this->GetEntity()), "Camera unable to find a Transform component!");

		Ref<Transform> EntityTransform = VL::Scene::GetComponent<Transform>(this->GetEntity());

		return lookAt(EntityTransform->Position, EntityTransform->Position + EntityTransform->GetFront(),
		              EntityTransform->GetUp());
	}

	Mat4x4 Camera::GetOriginViewMatrix() const
	{
		VOLUND_ASSERT(VL::Scene::HasComponent<Transform>(this->GetEntity()), "Camera unable to find a Transform component!");

		Ref<Transform> EntityTransform = VL::Scene::GetComponent<Transform>(this->GetEntity());

		return lookAt(Vec3(0.0f), EntityTransform->GetFront(), EntityTransform->GetUp());
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

	void Camera::OnCreate()
	{
		if (_ActiveCamera == nullptr)
		{
			_ActiveCamera = this;
		}
	}

	void Camera::OnDelete()
	{
		if (this->IsActive())
		{
			_ActiveCamera = nullptr;
		}
	}
}
