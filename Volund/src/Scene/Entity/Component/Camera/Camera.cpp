#pragma once

#include "PCH/PCH.h"

#include "Camera.h"

#include "Scene/Entity/Entity.h"
#include "Scene/Entity/Component/Transform/Transform.h"

#include "Renderer/Renderer.h"

namespace Volund
{
    bool Camera::IsActive() const
    {
        return ActiveCamera == this;
    }

    void Camera::SetActive()
    {
        ActiveCamera = this;
    }

    Camera* Camera::GetActiveCamera()
    {
        return ActiveCamera;
    }

    Mat4x4 Camera::GetViewMatrix() const
    {
        VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(), "Camera unable to find a Transform component!");

        Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

        return glm::lookAt(EntityTransform->Position, EntityTransform->Position + EntityTransform->GetFront(), EntityTransform->GetUp());
    }

    Mat4x4 Camera::GetOriginViewMatrix() const
    {
        VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(), "Camera unable to find a Transform component!");

        Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

        return glm::lookAt(Vec3(0.0f), EntityTransform->GetFront(), EntityTransform->GetUp());
    }

    Mat4x4 Camera::GetProjectionMatrix(float AspectRatio) const
    {
        return glm::perspective(glm::radians(this->FOV), AspectRatio, this->NearPlane, this->FarPlane);
    }

    void Camera::OnDelete()
    {
        if (this->IsActive())
        {
            ActiveCamera = nullptr;
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