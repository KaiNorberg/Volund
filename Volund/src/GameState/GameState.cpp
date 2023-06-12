#include "PCH/PCH.h"
#include "GameState.h"

#include "ThreadPool/ThreadPool.h"

#include "Lua/LuaData/LuaData.h"

#include "Scene/Component/Components.h"

#define VOLUND_SET_COMPONENT(table, member, name) if (table[name] != sol::nil) {member = table[name];}

namespace Volund
{
    enum class LuaComponentID
    {
        Camera = 1,
        CameraMovement = 2,
        MeshRenderer = 3,
        PointLight = 4,
        //Script = 5,
        Tag = 6,
        Transform = 7,
        SoundSource = 8,
        SoundListener = 9
    };

	Ref<Scene> GameState::GetScene()
	{
		return this->m_Scene;
	}

	Ref<AssetManager> GameState::GetAssetManager()
	{
		return this->m_AssetManager;
	}

	void GameState::Procedure(const Event& e)
	{
		this->m_Input->Procedure(e);
		this->m_Scene->Procedure(e);
	}

	GameState::GameState(Ref<Scene> scene)
	{
		while (VOLUND_THREADPOOL_BUSY());

		this->m_AssetManager = AssetManager::Create(".");
		this->m_Input = std::make_shared<Input>();
		this->m_Scene = scene;
	}

	GameState::GameState(const std::string& filepath)
	{	
		while (VOLUND_THREADPOOL_BUSY());	

		this->m_AssetManager = AssetManager::Create(filepath);
		this->m_Input = std::make_shared<Input>();
		this->m_Scene = std::make_shared<Scene>();

        LuaData sceneData = LuaData(filepath);

        //IMPORTANT: Remember to update the code below whenever a new component is implemented.

		for (auto& [key, value] : sceneData)
		{
			if (!value.is<sol::table>())
			{
				VOLUND_WARNING("Invalid entity found in scene file!");
				return;
			}

            sol::table entityTable = value.as<sol::table>();

            Entity entity = this->m_Scene->RegisterNewEntity();

			for (auto& [key, value] : entityTable)
			{
                if (!value.is<sol::table>())
                {
                    VOLUND_WARNING("Invalid component found in scene file!");
                    return;
                }

                sol::table componentTable = value.as<sol::table>();

                int64_t componentId = componentTable["ComponentType"];

                switch ((LuaComponentID)componentId)
                {
                case LuaComponentID::Transform:
                {
                    auto newComponent = this->m_Scene->CreateComponent<Transform>(entity);

                    if (componentTable["Position"] != sol::lua_nil)
                    {
                        newComponent->Position = componentTable["Position"];
                    }
                    if (componentTable["Scale"] != sol::lua_nil)
                    {
                        newComponent->Scale = componentTable["Scale"];
                    }
                    if (componentTable["Rotation"] != sol::lua_nil)
                    {
                        Vec3 rotation = componentTable["Rotation"];
                        newComponent->SetRotation(rotation);
                    }
                }
                break;
                case LuaComponentID::Camera:
                {
                    auto newComponent = this->m_Scene->CreateComponent<Camera>(entity);

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
                    auto newComponent = this->m_Scene->CreateComponent<CameraMovement>(entity);

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

                        Ref<Mesh> mesh = this->m_AssetManager->Fetch<Mesh>(meshFilepath);
                        Ref<Material> material = this->m_AssetManager->Fetch<Material>(materialFilepath);

                        auto newComponent = this->m_Scene->CreateComponent<MeshRenderer>(entity, mesh, material);

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
                    auto newComponent = this->m_Scene->CreateComponent<PointLight>(entity);

                    if (componentTable["Color"] != sol::lua_nil)
                    {
                        newComponent->Color = componentTable["Color"];
                    }

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Brightness, "Brightness");
                }
                break;
                case LuaComponentID::Tag:
                {
                    std::string string = componentTable["String"];
                    auto newComponent = this->m_Scene->CreateComponent<Tag>(entity, string);
                }
                break;
                case LuaComponentID::SoundSource:
                {
                    auto newComponent = this->m_Scene->CreateComponent<SoundSource>(entity);

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
                        Ref<AudioBuffer> sound = this->m_AssetManager->Fetch<AudioBuffer>(componentTable["Sound"]);
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
                    auto newComponent = this->m_Scene->CreateComponent<SoundListener>(entity);
                }
                break;
                default:
                {
                    VOLUND_WARNING("Unknown component id (%s)! Check for proper capitalization and spelling!", componentId);
                }
                break;
                }
			}
		}
	}

	GameState::~GameState()
	{

	}
}