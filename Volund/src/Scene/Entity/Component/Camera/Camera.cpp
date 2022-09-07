#pragma once

#include "PCH/PCH.h"

#include "Camera.h"

#include "Scene/Entity/Entity.h"
#include "Scene/Entity/Component/Transform/Transform.h"

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

    void Camera::OnEvent(Event* E)
    {
        switch (E->GetType())
        {
        case EventType::WINDOW_SIZE:
        {
            if (this->IsActive())
            {
                this->AspectRatio = ((float)((WindowSizeEvent*)E)->GetWidth()) / ((float)((WindowSizeEvent*)E)->GetHeight());
            }
        }
        break;
        }
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

    void Camera::UpdateMatrices()
    {
        VOLUND_ASSERT(this->GetEntity()->HasComponent<Transform>(), "Camera unable to find a Transform component!");

        Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

        this->_ViewMatrix = glm::lookAt(EntityTransform->Position, EntityTransform->Position + EntityTransform->GetFront(), EntityTransform->GetUp());
        this->_OriginViewMatrix = glm::lookAt(Vec3(0.0f), EntityTransform->GetFront(), EntityTransform->GetUp());
        this->_ProjectionMatrix = glm::perspective(glm::radians(this->FOV), this->AspectRatio, this->NearPlane, this->FarPlane);
    }
}