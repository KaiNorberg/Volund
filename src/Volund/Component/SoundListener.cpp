
#include "Component/SoundListener.hpp"
#include "Component/Transform.hpp"
#include "Scene.hpp"
#include "Lua/LuaAPI.hpp"

namespace Volund
{
	void SoundListener::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.type)
		{
		case VOLUND_EVENT_UPDATE:
		{
			static Vec3 oldPosition = Vec3(0.0f);

			const float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->m_listener.SetPosition(entityTransform->pos);
			this->m_listener.SetVelocity((entityTransform->pos - oldPosition) * timeStep);

			this->m_listener.SetOrientation(entityTransform->GetFront(), entityTransform->GetUp());
		}
		break;
		default:
		{

		}
		break;
		}
	}    
	
	VOLUND_USERTYPE_COMPONENT_REGISTER(SoundListener,
    [](LuaState* state){
        state->NewUsertype<SoundListener>("SoundListener", 
            sol::constructors<>()
        );
    });
}