#include "PCH/PCH.h"
#include "LuaScene.h"

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	float LuaScene::TimeSinceStart()
	{
		std::chrono::duration<double> Duration = std::chrono::high_resolution_clock::now() - this->_Scene->GetStartTime();

		return Duration.count();
	}

	LuaEntity LuaScene::CreateEntity()
	{
		return LuaEntity(this, this->_Scene->CreateEntity());
	}

	void LuaScene::DeleteEntity(LuaEntity E)
	{
		this->_Scene->DestroyEntity(E.Get());
	}

	void LuaScene::AddComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID, sol::table Table)
	{
		if (!this->_Scene->HasEntity(entity))
		{
			VOLUND_WARNING("Invalid entity %d!", entity);

			return;
		}

		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			auto NewComponent = this->_Scene->CreateComponent<Camera>(entity);

			if (Table["FOV"] != sol::lua_nil)
			{
				NewComponent->FOV = Table["FOV"];
			}

			if (Table["NearPlane"] != sol::lua_nil)
			{
				NewComponent->NearPlane = Table["NearPlane"];
			}

			if (Table["FarPlane"] != sol::lua_nil)
			{
				NewComponent->FarPlane = Table["FarPlane"];
			}
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			auto NewComponent = this->_Scene->CreateComponent<CameraMovement>(entity);

			if (Table["Speed"] != sol::lua_nil)
			{
				NewComponent->Speed = Table["Speed"];
			}

			if (Table["Sensitivity"] != sol::lua_nil)
			{
				NewComponent->Sensitivity = Table["Sensitivity"];
			}
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			if (Table["Mesh"] != sol::lua_nil && Table["Material"] != sol::lua_nil)
			{
				LuaMesh MeshAsset = Table["Mesh"];
				LuaMaterial MaterialAsset = Table["Material"];

				this->_Scene->CreateComponent<MeshRenderer>(entity, MeshAsset.Get(), MaterialAsset.Get());
			}
			else
			{
				VOLUND_WARNING("Unable to read mesh or material from MeshRenderer table!");
			}
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			auto NewComponent = this->_Scene->CreateComponent<PointLight>(entity);

			if (Table["Color"] != sol::lua_nil)
			{
				Vec3 Color = Table["Color"];
				NewComponent->Color = Color;
			}

			if (Table["Brightness"] != sol::lua_nil)
			{
				NewComponent->Brightness = Table["Brightness"];
			}
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			auto NewComponent = this->_Scene->CreateComponent<Script>(entity, S, LuaEntity(this, entity), Table["Script"], Table);
		}
		break;
		case LuaComponentID::TAG:
		{
			std::string String = Table["String"];

			auto NewComponent = this->_Scene->CreateComponent<Tag>(entity, String);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			auto NewComponent = this->_Scene->CreateComponent<Transform>(entity);

			if (Table["Position"] != sol::lua_nil)
			{
				Vec3 Position = Table["Position"];
				NewComponent->Position = Position;
			}

			if (Table["Rotation"] != sol::lua_nil)
			{
				Vec3 Rotation = Table["Rotation"];
				NewComponent->SetRotation(Rotation);
			}

			if (Table["Scale"] != sol::lua_nil)
			{
				Vec3 Scale = Table["Scale"];
				NewComponent->Scale = Scale;
			}
		}
		break;
		default:
		{
			VOLUND_WARNING("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}
	}

	void LuaScene::DeleteComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID, uint64_t I)
	{
		if (!this->_Scene->HasEntity(entity))
		{
			VOLUND_WARNING("Invalid entity %d!", entity);

			return;
		}

		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			this->_Scene->DeleteComponent<Camera>(entity, I);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			this->_Scene->DeleteComponent<CameraMovement>(entity, I);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			this->_Scene->DeleteComponent<MeshRenderer>(entity, I);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{			
			this->_Scene->DeleteComponent<PointLight>(entity, I);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			this->_Scene->DeleteComponent<Script>(entity, I);
		}
		break;
		case LuaComponentID::TAG:
		{
			this->_Scene->DeleteComponent<Tag>(entity, I);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			this->_Scene->DeleteComponent<Transform>(entity, I);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}
	}

	bool LuaScene::HasComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID)
	{
		if (!this->_Scene->HasEntity(entity))
		{
			VOLUND_WARNING("Invalid entity %d!", entity);

			return false;
		}

		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			return this->_Scene->HasComponent<Camera>(entity);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return this->_Scene->HasComponent<CameraMovement>(entity);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return this->_Scene->HasComponent<MeshRenderer>(entity);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return this->_Scene->HasComponent<PointLight>(entity);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return this->_Scene->HasComponent<Script>(entity);
		}
		break;
		case LuaComponentID::TAG:
		{
			return this->_Scene->HasComponent<Tag>(entity);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return this->_Scene->HasComponent<Transform>(entity);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}

		return false;
	}

	uint64_t LuaScene::ComponentAmount(sol::this_state S, Entity entity, LuaComponentID ComponentID)
	{
		if (!this->_Scene->HasEntity(entity))
		{
			VOLUND_WARNING("Invalid entity %d!", entity);

			return 0;
		}

		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			return this->_Scene->ComponentAmount<Camera>(entity);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return this->_Scene->ComponentAmount<CameraMovement>(entity);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return this->_Scene->ComponentAmount<MeshRenderer>(entity);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return this->_Scene->ComponentAmount<PointLight>(entity);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return this->_Scene->ComponentAmount<Script>(entity);
		}
		break;
		case LuaComponentID::TAG:
		{
			return this->_Scene->ComponentAmount<Tag>(entity);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return this->_Scene->ComponentAmount<Transform>(entity);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}

		return 0;
	}

	sol::table LuaScene::GetScript(sol::this_state S, Entity entity, sol::table Table)
	{
		for (int i = 0; i < this->_Scene->ComponentAmount<Script>(entity); i++)
		{
			auto EntityScript = this->_Scene->GetComponent<Script>(entity, i);
			if (EntityScript->Compare(Table))
			{
				return EntityScript->Table;
			}
		}

		VOLUND_WARNING("Entity does not conntain Script!");

		return nullptr;
	}

	sol::table LuaScene::GetComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID, uint64_t I)
	{
		if (!this->_Scene->HasEntity(entity))
		{
			VOLUND_WARNING("Invalid entity %d!", entity);

			return nullptr;
		}

		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<Camera>(entity, I));
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<CameraMovement>(entity, I));
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<MeshRenderer>(entity, I));
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<PointLight>(entity, I));
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<Script>(entity, I));
		}
		break;
		case LuaComponentID::TAG:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<Tag>(entity, I));
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return GenerateComponentTable(S, LuaEntity(this, entity), this->_Scene->GetComponent<Transform>(entity, I));
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}

		return nullptr;
	}

	sol::table LuaScene::ComponentView(sol::this_state S, LuaComponentID ComponentID)
	{
		switch (ComponentID)
		{
		case LuaComponentID::CAMERA:
		{
			return this->GenerateComponentView<Camera>(S);
		}
		break;
		case LuaComponentID::CAMERA_MOVEMENT:
		{
			return this->GenerateComponentView<CameraMovement>(S);
		}
		break;
		case LuaComponentID::MESH_RENDERER:
		{
			return this->GenerateComponentView<MeshRenderer>(S);
		}
		break;
		case LuaComponentID::POINT_LIGHT:
		{
			return this->GenerateComponentView<PointLight>(S);
		}
		break;
		case LuaComponentID::SCRIPT:
		{
			return this->GenerateComponentView<Script>(S);
		}
		break;
		case LuaComponentID::TAG:
		{
			return this->GenerateComponentView<Tag>(S);
		}
		break;
		case LuaComponentID::TRANSFORM:
		{
			return this->GenerateComponentView<Transform>(S);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}

		return 0;
	}

	sol::table LuaScene::ScriptView(sol::this_state S, sol::table ScriptTable)
	{
		sol::state_view StateView = S;

		sol::table Output = StateView.create_table_with();

		std::vector<Ref<Script>> View;
		this->_Scene->View(View);

		for (auto& ComponentID : View)
		{
			if (ComponentID->Compare(ScriptTable))
			{
				Output.add(ComponentID->Table);
			}
		}

		return Output;
	}

	LuaScene::LuaScene(Ref<Scene> scene)
	{
		this->_Scene = scene;
	}
}