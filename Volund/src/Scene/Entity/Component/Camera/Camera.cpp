#pragma once

#include "PCH/PCH.h"

#include "Camera.h"

#include "Scene/Scene.h"
#include "Scene/Entity/Entity.h"
#include "Scene/Entity/Component/Transform/Transform.h"

namespace Volund
{
	bool Camera::IsActive() const
	{
		Scene* ParentScene = this->GetEntity()->GetScene();

		return ActiveCameras.contains(ParentScene) && ActiveCameras[ParentScene] == this;
	}

	void Camera::SetActive()
	{
		ActiveCameras[this->GetEntity()->GetScene()] = this;
	}

	Camera* Camera::GetActiveCamera(Ref<Scene> ParentScene)
	{
		if (ActiveCameras.contains(ParentScene.get()))
		{
			return ActiveCameras[ParentScene.get()];
		}
		return nullptr;
	}

	Mat4x4 Camera::GetViewMatrix() const
	{
		VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(), "Camera unable to find a Transform component!");

		Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

		return lookAt(EntityTransform->Position, EntityTransform->Position + EntityTransform->GetFront(),
		              EntityTransform->GetUp());
	}

	Mat4x4 Camera::GetOriginViewMatrix() const
	{
		VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(), "Camera unable to find a Transform component!");

		Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

		return lookAt(Vec3(0.0f), EntityTransform->GetFront(), EntityTransform->GetUp());
	}

	Mat4x4 Camera::GetProjectionMatrix(float AspectRatio) const
	{
		return glm::perspective(glm::radians(this->FOV), AspectRatio, this->NearPlane, this->FarPlane);
	}

	void Camera::OnCreate()
	{
		Scene* ParentScene = this->GetEntity()->GetScene();

		if (!ActiveCameras.contains(ParentScene))
		{
			ActiveCameras[ParentScene] = this;
		}
	}

	void Camera::OnDelete()
	{
		if (this->IsActive())
		{
			this->ActiveCameras.erase(this->GetEntity()->GetScene());
		}
	}

	JSON Camera::Serialize()
	{
		JSON CameraJSON;

		CameraJSON.AddEntry("Type", "Camera");

		CameraJSON.AddEntry("IsActive", this->IsActive());
		CameraJSON.AddEntry("FOV", this->FOV);
		CameraJSON.AddEntry("NearPlane", this->NearPlane);
		CameraJSON.AddEntry("FarPlane", this->FarPlane);

		return CameraJSON;
	}
}
