#pragma once

#include "PCH/PCH.h"

#include "Camera.h"

#include "Component/Transform/Transform.h"
#include "Entity/Entity.h"

namespace Volund
{
    Camera* Camera::ActiveCamera = nullptr;

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
        return this->_ViewMatrix;
    }

    Mat4x4 Camera::GetOriginViewMatrix() const
    {
        return this->_OriginViewMatrix;
    }

    Mat4x4 Camera::GetProjectionMatrix() const
    {
        return this->_ProjectionMatrix;
    }

    void Camera::OnCreate()
    {
        this->UpdateMatrices();
    }

    void Camera::OnUpdate(TimeStep TS)
    {
        this->UpdateMatrices();
    }

    void Camera::OnDelete()
    {
        if (this->IsActive())
        {
            ActiveCamera = nullptr;
        }
    }

    void Camera::UpdateMatrices()
    {
        VOLUND_ASSERT(this->GetParent()->HasComponent<Transform>(), "Camera unable to find a Transform component!");

        Transform* EntityTransform = this->GetParent()->GetComponent<Transform>();

        this->_ViewMatrix = glm::lookAt(EntityTransform->Position, EntityTransform->Position + EntityTransform->GetFront(), EntityTransform->GetUp());
        this->_OriginViewMatrix = glm::lookAt(Vec3(0.0f), EntityTransform->GetFront(), EntityTransform->GetUp());
        this->_ProjectionMatrix = glm::perspective(glm::radians(this->FOV), this->AspectRatio, this->NearPlane, this->FarPlane);
    }
}