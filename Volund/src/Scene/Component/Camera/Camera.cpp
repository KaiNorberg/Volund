#include "PCH/PCH.h"

#include "Camera.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

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
		return glm::perspective(glm::radians(this->FOV), AspectRatio, this->NearPlane, this->FarPlane);
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

	VML Camera::Serialize()
	{
		VML CameraVML;

		CameraVML.PushBack("Type", VMLEntry("Camera"));

		CameraVML.PushBack("IsActive", VMLEntry(this->IsActive()));
		CameraVML.PushBack("FOV", VMLEntry(this->FOV));
		CameraVML.PushBack("NearPlane", VMLEntry(this->NearPlane));
		CameraVML.PushBack("FarPlane", VMLEntry(this->FarPlane));

		return CameraVML;
	}
}
