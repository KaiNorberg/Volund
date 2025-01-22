
#include "Component/Camera.h"

#include "Scene.h"
#include "Component/Transform.h"
#include "Window.h"
#include "Rendering/Renderer.h"
#include "Lua/LuaAPI.h"

namespace Volund
{
	void Camera::SetLayerMask(const uint8_t index, const bool enabled)
	{
		if (index > 0 && index <= 32)
		{
			if (enabled)
			{
				this->m_layerMask |= 1UL << (index - 1);
			}
			else
			{
				this->m_layerMask &= ~(1UL << (index - 1));
			}
		}
	}

	uint32_t Camera::GetLayerMask()
	{
		return this->m_layerMask;
	}

	Mat4x4 Camera::GetViewMatrix() const
	{
		const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		if (entityTransform != nullptr)
		{
			return Math::ViewMatrix(entityTransform->pos, entityTransform->pos + entityTransform->GetFront(),
				entityTransform->GetUp());
		}
		else
		{
			return Mat4x4(1.0f);
		}
	}

	Mat4x4 Camera::GetOriginViewMatrix() const
	{
		const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

		if (entityTransform != nullptr)
		{
			return Math::ViewMatrix(Vec3(0.0f), entityTransform->GetFront(), entityTransform->GetUp());
		}
		else
		{
			return Mat4x4(1.0f);
		}
	}

	Mat4x4 Camera::GetProjectionMatrix(const float aspectRatio) const
	{
		if (abs(aspectRatio - std::numeric_limits<float>::epsilon()) > 0.0f)
		{
			return Math::ProjectionMatrix(Math::Radians(this->fov), aspectRatio, this->nearPlane, this->farPlane);
		}
		else
		{
			return Mat4x4(1.0f);
		}
	}

	void Camera::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.type)
		{
		case VOLUND_EVENT_RENDER:
		{
			/*const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			VOLUND_ASSERT(entityTransform != nullptr, "Camera component unable to retrive transform component!");

			RendererEye eye;
			eye.Target = this->m_targetBuffer;
			eye.ProjectionMatrix = this->GetProjectionMatrix((float)spec.Width / (float)spec.Height);
			eye.ViewMatrix = this->GetViewMatrix();
			eye.pos = entityTransform->pos;
			eye.LayerMask = this->m_layerMask;

			Renderer::Submit(eye);*/
		}
		break;
		default:
		{

		}
		break;
		}
	}

	Camera::Camera(float fov, float nearPlane, float farPlane)
	{
		this->fov = fov;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
	}  

    VOLUND_USERTYPE_COMPONENT_REGISTER(Camera,
    [](LuaState* state){
        state->NewUsertype<Camera>("Camera", 
            sol::constructors<>(),
            "fov", &Camera::fov,
            "nearPlane", &Camera::nearPlane,
            "farPlane", &Camera::farPlane,
            "set_layer_mask", &Camera::SetLayerMask,
            "get_layer_mask", &Camera::GetLayerMask,
            "get_view_matrix", &Camera::GetViewMatrix,
            "get_origin_view_matrix", &Camera::GetOriginViewMatrix,
            "get_projection_matrix", &Camera::GetProjectionMatrix
        );
    }, float, float, float);
}