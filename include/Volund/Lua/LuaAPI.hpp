#pragma once

#include "Scene.hpp"
#include "../Lua/LuaState.hpp"

// Note: The scene usertype should not be registered. 
// For the sake of allowing easier component method registration, it is added into the api manually. Registration should only be called once and be in a .cpp file.
// We are implementing the templated methods of LuaState in order to avoid issues with the shared library RTTI barrier.
#ifdef VOLUND_BUILD
#define VOLUND_USERTYPE_REGISTER(type, usertypeFunc) \
struct type##Registrar { \
    type##Registrar() { \
        LuaAPI::RegisterUsertype(#type, (usertypeFunc), nullptr); \
    } \
}; \
template std::string LuaState::GetKey<type>(std::shared_ptr<type> object); \
template void LuaState::GetObjects<type>(std::vector<std::pair<std::string, std::shared_ptr<type>>>*); \
static type##Registrar type##Instance;

#define VOLUND_USERTYPE_COMPONENT_REGISTER(type, usertypeFunc, ...) \
struct type##Registrar { \
    type##Registrar() { \
        LuaAPI::RegisterUsertype(#type, (usertypeFunc), \
            [](LuaState* state, sol::usertype<Scene>* scene) { \
                ComponentRegistration<type>::Register<__VA_ARGS__>(#type, state, scene); \
            } \
        ); \
    } \
}; \
static type##Registrar type##Instance;
#endif

namespace Volund
{
    template<typename T>
    class VOLUND_API ComponentRegistration
    {
    public:
        template<typename... Args>
        static void Register(std::string const& name, LuaState* state, sol::usertype<Scene>* scene) 
        {
            std::string snakeCaseName;
            for (char c : name) 
            {
                if (std::isupper(c) && !snakeCaseName.empty()) 
                {
                    snakeCaseName += '_';
                }
                snakeCaseName += std::tolower(c);
            }
        
            (*scene)[("add_" + snakeCaseName).c_str()] = [](std::shared_ptr<Scene> scene, Entity entity, Args... args) {
                return scene->AddComponent<T>(entity, std::forward<Args>(args)...);
            };
            
            (*scene)[("remove_" + snakeCaseName).c_str()] = [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0) {
                scene->RemoveComponent<T>(entity, index);
            };
            
            (*scene)[("has_" + snakeCaseName).c_str()] = [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0) {
                return scene->HasComponent<T>(entity, index);
            };
            
            (*scene)[(snakeCaseName + "_amount").c_str()] = [](std::shared_ptr<Scene> scene, Entity entity) {
                return scene->ComponentAmount<T>(entity);
            };
            
            (*scene)[("get_" + snakeCaseName).c_str()] = [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0) {
                return scene->GetComponent<T>(entity, index);
            };
        }
    private:
        ComponentRegistration() = default;
    };

    class VOLUND_API LuaAPI
    {
    public:        
        using UsertypeRegisterFunc = std::function<void(LuaState*)>;
        using ComponentRegisterFunc = std::function<void(LuaState*, sol::usertype<Scene>*)>;
        struct UsertypeRecord
        {
            std::string name;
            UsertypeRegisterFunc usertypeFunc;
            ComponentRegisterFunc componentFunc;
        };
        // Note: Specify a componentFunc only if the usertype is a component.
        static void RegisterUsertype(std::string const& name, UsertypeRegisterFunc usertypeFunc, ComponentRegisterFunc componentFunc = nullptr);
        static void Bind(LuaState* state);
    private:
        static inline std::vector<UsertypeRecord> m_records;
        LuaAPI() = default;
    };
}