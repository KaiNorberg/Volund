#include "PCH/PCH.h"

#include "Lua/LuaComponent/LuaComponentID.h"
#include "Lua/LuaState/LuaMaterial/LuaMaterial.h"
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

                //TODO: Fix cache is caching luamaterial not the material itself.
                Ref<Mesh> mesh = scene->FetchAsset<Mesh>(meshFilepath);
                Ref<LuaMaterial> luaMaterial = scene->FetchAsset<LuaMaterial>(materialFilepath);

                auto newComponent = scene->CreateComponent<MeshRenderer>(entity, mesh, luaMaterial->Get());			
                
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

    std::string LuaTableToString(sol::table table, int indentation)
    {
        std::string output;
        output += "{\n";

        for (auto& [key, value] : table)
        {        
            for (int i = 0; i < indentation + 4; i++)
            {
                output += ' ';
            }        
            output += key.as<std::string>() + " = ";
            if (value.is<sol::table>())
            {
                output += LuaTableToString(value, indentation + 4);
            }
            else if (value.is<LuaVec2>())
            {
                LuaVec2 vec2 = value.as<LuaVec2>();
                output += "Vec2:new(" + std::to_string(vec2.x) + ", "  + std::to_string(vec2.y) + ")";
            }
            else if (value.is<LuaVec3>())
            {
                LuaVec3 vec3 = value.as<LuaVec3>();
                output += "Vec3:new(" + std::to_string(vec3.x) + ", "  + std::to_string(vec3.y) + ", "  + std::to_string(vec3.z) + ")";
            }
            else if (value.is<LuaVec4>())
            {
                LuaVec4 vec4 = value.as<LuaVec4>();
                output += "Vec4:new(" + std::to_string(vec4.x) + ", "  + std::to_string(vec4.y) + ", "  + std::to_string(vec4.z) + std::to_string(vec4.w) + ")";
            }
            else
            {
                output += value.as<std::string>();
            }
            output += ",\n";
        }

        for (int i = 0; i < indentation; i++)
        {
            output += ' ';
        }        
        output += "}";

        return output;
    }
}