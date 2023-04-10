#include "PCH/PCH.h"
#include "LuaScene.h"

#include "Filesystem/Filesystem.h"
#include "Lua/LuaComponent/LuaComponentID.h"
#include "Scene/Component/Components.h"

#include <sol/sol.hpp>

#define VOLUND_SET_COMPONENT(table, member, name) if (table[name] != sol::nil) {member = table[name];}

namespace Volund
{
    Ref<Scene> LuaScene::Get()
    {
        return this->m_Scene;
    }

    LuaScene::LuaScene(const std::string& filepath)
    {           
        std::string script = Filesystem::Load(filepath);

        sol::table sceneTable;
        try
		{
			sceneTable = this->m_SolState->script(script, [](lua_State*, sol::protected_function_result pfr)
			{		
				sol::error err = pfr;
				VOLUND_WARNING(err.what());

				return pfr;
			});
		}
		catch(const sol::error& e)
		{
			VOLUND_WARNING(e.what());
            return;
		}

        this->m_Scene = std::make_shared<Scene>();

        VOLUND_ASSERT(sceneTable != sol::nil && sceneTable.is<sol::table>(), "Scene files must return a valid Lua table!");
        for (auto& [entityKey, entity] : sceneTable)
        {                
            VOLUND_ASSERT(entity != sol::nil && entity.is<sol::table>(), "Invalid entity found in scene file!");

            auto newEntity = this->m_Scene->CreateEntity();

            sol::table entityTable = sol::table(entity);
            for (auto& [componentKey, component] : entityTable)
            {                        
                VOLUND_ASSERT(component != sol::nil && component.is<sol::table>(), "Invalid component found in scene file!");
                sol::table componentTable = sol::table(component);            
                VOLUND_ASSERT(componentTable.size() >= 1, "Invalid component found in scene file!");

                LuaComponentID componentID = componentTable[1];

                switch (componentID)
                {
                case LuaComponentID::Camera:
                {
                    auto newComponent = this->m_Scene->CreateComponent<Camera>(newEntity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->FOV, "FOV");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->NearPlane, "NearPlane");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->FarPlane, "FarPlane");

                    if (componentTable["TargetBuffer"] != sol::lua_nil)
                    {
                        //newComponent->SetTargetBuffer(componentTable["TargetBuffer"].get<LuaFramebuffer>().Get());
                    }
                    else
                    {
                        newComponent->SetTargetBuffer(this->m_Scene->GetTargetBuffer());
                    }
                }
                break;
                case LuaComponentID::CameraMovement:
                {
                    auto newComponent = this->m_Scene->CreateComponent<CameraMovement>(newEntity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Speed, "Speed");

                    if (componentTable["Sensitivity"] != sol::lua_nil)
                    {
                        newComponent->Sensitivity = componentTable["Sensitivity"];
                    }
                }
                break;
                case LuaComponentID::MeshRenderer:
                {
                    /*if (componentTable["Mesh"] != sol::lua_nil && componentTable["Material"] != sol::lua_nil)
                    {
                        LuaMesh meshAsset = componentTable["Mesh"];
                        LuaMaterial materialAsset = componentTable["Material"];

                        auto newComponent = this->m_Scene->CreateComponent<MeshRenderer>(newEntity, meshAsset.Get(), materialAsset.Get());			
                        
                        if (componentTable["Layer"] != sol::lua_nil)
                        {
                            newComponent->SetLayer(componentTable["Layer"]);
                        }
                    }
                    else
                    {
                        VOLUND_WARNING("Unable to read mesh or material from MeshRenderer componentTable!");
                    }*/
                }
                break;
                case LuaComponentID::PointLight:
                {
                    auto newComponent = this->m_Scene->CreateComponent<PointLight>(newEntity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Color, "Color");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->Brightness, "Brightness");
                }
                break;
                /*case LuaComponentID::Script:
                {
                    auto newComponent = this->m_Scene->CreateComponent<Script>(newEntity, s, (*this), componentTable["Script"], componentTable);
                }
                break;*/
                case LuaComponentID::Tag:
                {
                    std::string string = componentTable["String"];
                    auto newComponent = this->m_Scene->CreateComponent<Tag>(newEntity, string);
                }
                break;
                case LuaComponentID::Transform:
                {
                    auto newComponent = this->m_Scene->CreateComponent<Transform>(newEntity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Position, "Position");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->Scale, "Scale");

                    if (componentTable["Rotation"] != sol::lua_nil)
                    {
                        Vec3 rotation = componentTable["Rotation"];
                        newComponent->SetRotation(componentTable["Rotation"]);
                    }
                }
                break;
                case LuaComponentID::SoundSource:
                {
                    /*auto newComponent = this->m_Scene->CreateComponent<SoundSource>(newEntity);

                    if (componentTable["Looping"] != sol::lua_nil)
                    {
                        bool looping = componentTable["Looping"];
                        newComponent->SetLooping(looping);
                    }

                    if (componentTable["Pitch"] != sol::lua_nil)
                    {
                        float pitch = componentTable["Pitch"];
                        newComponent->SetPitch(pitch);
                    }

                    if (componentTable["Gain"] != sol::lua_nil)
                    {
                        float gain = componentTable["Gain"];
                        newComponent->SetGain(gain);
                    }

                    if (componentTable["Sound"] != sol::lua_nil)
                    {
                        LuaSound sound = componentTable["Sound"];
                        newComponent->SetBuffer(sound.GetBuffer());
                    }

                    if (componentTable["Play"] != sol::lua_nil && componentTable["Play"] == true)
                    {
                        newComponent->Play();
                    }*/
                }
                break;
                case LuaComponentID::SoundListener:
                {
                    auto newComponent = this->m_Scene->CreateComponent<SoundListener>(newEntity);
                }
                break;
                default:
                {
                    VOLUND_WARNING("Unknown ComponentID type (%s)! Check for proper capitalization and spelling!", componentID);
                }
                break;
                }
            }
        }
    }
}