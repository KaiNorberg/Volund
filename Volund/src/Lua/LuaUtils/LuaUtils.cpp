#include "PCH/PCH.h"

#include "Lua/LuaVec/LuaVec.h"

#include "Scene/Component/Components.h"
#include "Filesystem/Filesystem.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include <sol/sol.hpp>
#include "LuaUtils.h"

namespace Volund::LuaUtils
{
    /*Entity DeserializeEntity(Ref<Scene> scene, sol::table entityTable)
    {
        auto entity = scene->RegisterNewEntity();

        for (auto& [componentKey, component] : entityTable)
        {
            if (!component.is<sol::table>())
            {
                VOLUND_WARNING("Component found in scene file is of a non table type!");
                return 0;
            }

            sol::table componentTable = sol::table(component);

            LuaComponentID componentID = componentTable[1];

            //IMPORTANT: Remember to update the code below whenever a new component is implemented.

            switch (componentID)
            {
            case LuaComponentID::Transform:
            {
                auto newComponent = scene->CreateComponent<Transform>(entity);

                if (componentTable["Position"] != sol::lua_nil)
                {
                    newComponent->Position = componentTable["Position"].get<LuaVec3>().GLM();
                }
                if (componentTable["Scale"] != sol::lua_nil)
                {
                    newComponent->Scale = componentTable["Scale"].get<LuaVec3>().GLM();
                }
                if (componentTable["Rotation"] != sol::lua_nil)
                {
                    Vec3 rotation = componentTable["Rotation"].get<LuaVec3>().GLM();
                    newComponent->SetRotation(rotation);
                }
            }
            break;
            case LuaComponentID::Camera:
            {
                auto newComponent = scene->CreateComponent<Camera>(entity);

                VOLUND_SET_COMPONENT(componentTable, newComponent->FOV, "FOV");
                VOLUND_SET_COMPONENT(componentTable, newComponent->NearPlane, "NearPlane");
                VOLUND_SET_COMPONENT(componentTable, newComponent->FarPlane, "FarPlane");

                if (componentTable["TargetBuffer"] != sol::lua_nil)
                {
                    //TODO: Add framebuffer asset
                    //newComponent->SetTargetBuffer(componentTable["TargetBuffer"].get<LuaFramebuffer>().Get());
                }
            }
            break;
            case LuaComponentID::CameraMovement:
            {
                auto newComponent = scene->CreateComponent<CameraMovement>(entity);

                VOLUND_SET_COMPONENT(componentTable, newComponent->Speed, "Speed");
                VOLUND_SET_COMPONENT(componentTable, newComponent->Sensitivity, "Sensitivity");
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

                if (componentTable["Color"] != sol::lua_nil)
                {
                    newComponent->Color = componentTable["Color"].get<LuaVec3>().GLM();
                }

                VOLUND_SET_COMPONENT(componentTable, newComponent->Brightness, "Brightness");
            }
            break;
            case LuaComponentID::Tag:
            {
                std::string string = componentTable["String"];
                auto newComponent = scene->CreateComponent<Tag>(entity, string);
            }
            break;
            case LuaComponentID::SoundSource:
            {
                auto newComponent = scene->CreateComponent<SoundSource>(entity);

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
                    Ref<AudioBuffer> sound = scene->FetchAsset<AudioBuffer>(componentTable["Sound"]);
                    newComponent->SetBuffer(sound);
                }

                if (componentTable["AutoPlay"] != sol::lua_nil)
                {
                    newComponent->AutoPlay = componentTable["AutoPlay"];
                }
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

        return entity;
    }

    void DeserializeScene(Ref<Scene> scene, sol::table sceneTable)
    {
        for (auto& [entityKey, entityTable] : sceneTable)
        {
            if (!entityTable.is<sol::table>())
            {
                VOLUND_WARNING("Invalid entity found in scene file!");
                return;
            }

            auto newEntity = LuaUtils::DeserializeEntity(scene, sol::table(entityTable));
        }
    }*/

    sol::protected_function_result ScriptFile(Ref<sol::state> state, const std::string &filepath)
    {
        sol::protected_function_result result;
        try
		{
            result = state->script_file(filepath, [](lua_State*, sol::protected_function_result pfr)
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

        return result;
    }
}