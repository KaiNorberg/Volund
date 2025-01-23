#include "Lua/LuaAPI.hpp"

#include "Component/Components.hpp"

namespace Volund
{
    void LuaAPI::RegisterUsertype(std::string const& name, UsertypeRegisterFunc usertypeFunc, ComponentRegisterFunc componentFunc)
    {    
        m_records.push_back(UsertypeRecord(name, usertypeFunc, componentFunc));
    }

    void LuaAPI::Bind(LuaState* state)
    {
        state->m_state.open_libraries(sol::lib::base);

        state->m_state.set_function("require", [state](std::string const& filepath) {
            return state->m_state.script_file(state->AbsolutePath(filepath));
        });

        state->m_state.set_function("print", [state](std::string const& string) {
            VOLUND_INFO("{}", string);
        });

        for (auto& record : m_records)
        {
            VOLUND_INFO("Binding usertype '{}'", record.name);
            record.usertypeFunc(state);
        }
        
        state->m_state.new_usertype<Entity>("Entity");

        sol::usertype<Scene> sceneType = state->m_state.new_usertype<Scene>("Scene", sol::constructors<Scene()>(),
            "new", []() { return std::make_shared<Scene>(); },
            "register", &Scene::Register,
            "unregister", &Scene::Unregister,
            "is_registered", &Scene::IsRegistered
        );

        for (auto& record : m_records)
        {
            if (record.componentFunc != nullptr)
            {
                record.componentFunc(state, &sceneType);
            }
        }
    }
}
