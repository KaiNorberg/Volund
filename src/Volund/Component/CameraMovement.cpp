
#include "Component/CameraMovement.h"
#include "Component/Transform.h"
#include "Lua/LuaAPI.h"
#include "Scene.h"

namespace Volund
{
	void CameraMovement::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_input.Procedure(e);

		switch (e.type)
		{
		case VOLUND_EVENT_UPDATE:
		{
			VOLUND_PROFILE_FUNCTION();

			const float ts = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			if (m_input.IsHeld('W'))
			{
				entityTransform->pos += entityTransform->GetFront() * float(ts) * this->speed;
			}
			if (m_input.IsHeld('S'))
			{
				entityTransform->pos -= entityTransform->GetFront() * float(ts) * this->speed;
			}
			if (m_input.IsHeld('A'))
			{
				entityTransform->pos -= entityTransform->GetRight() * float(ts) * this->speed;
			}
			if (m_input.IsHeld('D'))
			{
				entityTransform->pos += entityTransform->GetRight() * float(ts) * this->speed;
			}

			IVec2 delta = m_input.GetMousePosition() - this->m_oldMousePosition;

			delta.x = std::clamp(delta.x, -10, 10) * this->sensitivity;
			delta.y = std::clamp(delta.y, -10, 10) * this->sensitivity;

			m_rotation -= Vec3(delta.y, delta.x, 0.0f) * this->sensitivity;
			m_rotation.x = std::clamp(m_rotation.x, -89.0f, 89.0f);

			entityTransform->SetRotation(m_rotation);
			this->m_oldMousePosition = m_input.GetMousePosition();
		}
		break;
		default:
		{

		}
		break;
		}
	}

    CameraMovement::CameraMovement(float speed, float sensitivity)
    {
		this->speed = speed;
		this->sensitivity = sensitivity;
		this->m_oldMousePosition = this->m_input.GetMousePosition();
	}

    VOLUND_USERTYPE_COMPONENT_REGISTER(CameraMovement,
    [](LuaState* state){
        state->NewUsertype<CameraMovement>("CameraMovement", 
            sol::constructors<>(),
            "speed", &CameraMovement::speed,
            "sensitivity", &CameraMovement::sensitivity
        );
    }, float, float);

} // namespace Volund