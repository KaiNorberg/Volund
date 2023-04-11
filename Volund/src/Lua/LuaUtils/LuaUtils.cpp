#include "PCH/PCH.h"

#include "Lua/LuaComponent/LuaComponentID.h"
#include "Lua/LuaVec/LuaVec.h"

#include "Scene/Component/Components.h"
#include "Filesystem/Filesystem.h"

#include <sol/sol.hpp>
#include "LuaUtils.h"

namespace Volund::LuaUtils
{
    void AddComponentToEntity(Ref<Scene> scene, Entity entity, sol::table componentTable)
    {
        LuaComponentID componentID = componentTable[1];

        switch (componentID)
        {
        case LuaComponentID::Camera:
        {
            auto newComponent = scene->CreateComponent<Camera>(entity);

            VOLUND_SET_COMPONENT(componentTable, newComponent->FOV, "FOV");
            VOLUND_SET_COMPONENT(componentTable, newComponent->NearPlane, "NearPlane");
            VOLUND_SET_COMPONENT(componentTable, newComponent->FarPlane, "FarPlane");

            if (componentTable["TargetBuffer"] != sol::lua_nil)
            {
                //TODO: Add LuaFramebuffer
                //newComponent->SetTargetBuffer(componentTable["TargetBuffer"].get<LuaFramebuffer>().Get());
            }
            else
            {
                newComponent->SetTargetBuffer(scene->GetTargetBuffer());
            }
        }
        break;
        case LuaComponentID::CameraMovement:
        {
            auto newComponent = scene->CreateComponent<CameraMovement>(entity);

            VOLUND_SET_COMPONENT(componentTable, newComponent->Speed, "Speed");

            if (componentTable["Sensitivity"] != sol::lua_nil)
            {
                newComponent->Sensitivity = componentTable["Sensitivity"];
            }
        }
        break;
        case LuaComponentID::MeshRenderer:
        {
            if (componentTable["Mesh"] != sol::lua_nil && componentTable["Material"] != sol::lua_nil)
            {
                std::string meshFilepath = componentTable["Mesh"];
                std::string materialFilepath = componentTable["Material"];

                Ref<Mesh> mesh = scene->FetchAsset<Mesh>(meshFilepath);
                Ref<Material> material = scene->FetchAsset<Material>(materialFilepath);

                auto newComponent = scene->CreateComponent<MeshRenderer>(entity, mesh, material);			
                
                if (componentTable["Layer"] != sol::lua_nil)
                {
                    newComponent->SetLayer(componentTable["Layer"]); 
                }
            }
            else
            {
                VOLUND_WARNING("Unable to read mesh or material from MeshRenderer componentTable!");
            }
        }
        break;
        case LuaComponentID::PointLight:
        {
            auto newComponent = scene->CreateComponent<PointLight>(entity);

            VOLUND_SET_COMPONENT(componentTable, newComponent->Color, "Color");
            VOLUND_SET_COMPONENT(componentTable, newComponent->Brightness, "Brightness");
        }
        break;
        /*case LuaComponentID::Script:
        {
            auto newComponent = scene->CreateComponent<Script>(entity, s, (*this), componentTable["Script"], componentTable);
        }
        break;*/
        case LuaComponentID::Tag:
        {
            std::string string = componentTable["String"];
            auto newComponent = scene->CreateComponent<Tag>(entity, string);
        }
        break;
        case LuaComponentID::Transform:
        {
            auto newComponent = scene->CreateComponent<Transform>(entity);
            
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
            //TODO: fix

            /*auto newComponent = scene->CreateComponent<SoundSource>(entity);

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
            auto newComponent = scene->CreateComponent<SoundListener>(entity);
        }
        break;
        default:
        {
            VOLUND_WARNING("Unknown ComponentID type (%s)! Check for proper capitalization and spelling!", componentID);
        }
        break;
        }
    }

    sol::object ScriptFile(Ref<sol::state> state, const std::string &filepath)
    {
        std::string script = Filesystem::Load(filepath);

        sol::object object;
        try
		{
			object = state->script(script, [](lua_State*, sol::protected_function_result pfr)
			{		
				sol::error err = pfr;
				VOLUND_WARNING(err.what());

				return pfr;
			});
		}
		catch(const sol::error& e)
		{
			VOLUND_WARNING(e.what());
		}    

        return object;
    }
}