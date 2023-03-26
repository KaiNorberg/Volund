#include "PCH/PCH.h"
#include "LuaEntity.h"

#include "Scene/Component/Components.h"

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaMesh/LuaMesh.h"
#include "Lua/LuaSound/LuaSound.h"

namespace Volund
{
	Entity LuaEntity::Get()
	{
		return this->m_Entity;
	}

	void LuaEntity::AddComponent(sol::this_state s, LuaComponentID ComponentID, sol::table table)
	{
		if (!this->m_Scene->HasEntity(this->m_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->m_Entity);

			return;
		}

		switch (ComponentID)
		{
		case LuaComponentID::Camera:
		{
			auto newComponent = this->m_Scene->CreateComponent<Camera>(this->m_Entity);

			if (table["FOV"] != sol::lua_nil)
			{
				newComponent->FOV = table["FOV"];
			}

			if (table["NearPlane"] != sol::lua_nil)
			{
				newComponent->NearPlane = table["NearPlane"];
			}

			if (table["FarPlane"] != sol::lua_nil)
			{
				newComponent->FarPlane = table["FarPlane"];
			}

			if (table["TargetBuffer"] != sol::lua_nil)
			{
				newComponent->SetTargetBuffer(((LuaFramebuffer)table["TargetBuffer"]).Get());
			}
			else
			{
				newComponent->SetTargetBuffer(this->m_Scene->GetTargetBuffer());
			}
		}
		break;
		case LuaComponentID::CameraMovement:
		{
			auto newComponent = this->m_Scene->CreateComponent<CameraMovement>(this->m_Entity);

			if (table["Speed"] != sol::lua_nil)
			{
				newComponent->Speed = table["Speed"];
			}

			if (table["Sensitivity"] != sol::lua_nil)
			{
				newComponent->Sensitivity = table["Sensitivity"];
			}
		}
		break;
		case LuaComponentID::MeshRenderer:
		{
			if (table["Mesh"] != sol::lua_nil && table["Material"] != sol::lua_nil)
			{
				LuaMesh meshAsset = table["Mesh"];
				LuaMaterial materialAsset = table["Material"];

				auto newComponent = this->m_Scene->CreateComponent<MeshRenderer>(this->m_Entity, meshAsset.Get(), materialAsset.Get());			
				
				if (table["Layer"] != sol::lua_nil)
				{
					newComponent->SetLayer(table["Layer"]);
				}
			}
			else
			{
				VOLUND_WARNING("Unable to read mesh or material from MeshRenderer table!");
			}
		}
		break;
		case LuaComponentID::PointLight:
		{
			auto newComponent = this->m_Scene->CreateComponent<PointLight>(this->m_Entity);

			if (table["Color"] != sol::lua_nil)
			{
				Vec3 color = table["Color"];
				newComponent->Color = color;
			}

			if (table["Brightness"] != sol::lua_nil)
			{
				newComponent->Brightness = table["Brightness"];
			}
		}
		break;
		case LuaComponentID::Script:
		{
			auto newComponent = this->m_Scene->CreateComponent<Script>(this->m_Entity, s, (*this), table["Script"], table);
		}
		break;
		case LuaComponentID::Tag:
		{
			std::string string = table["String"];

			auto newComponent = this->m_Scene->CreateComponent<Tag>(this->m_Entity, string);
		}
		break;
		case LuaComponentID::Transform:
		{
			auto newComponent = this->m_Scene->CreateComponent<Transform>(this->m_Entity);

			if (table["Position"] != sol::lua_nil)
			{
				Vec3 position = table["Position"];
				newComponent->Position = position;
			}

			if (table["Rotation"] != sol::lua_nil)
			{
				Vec3 rotation = table["Rotation"];
				newComponent->SetRotation(rotation);
			}

			if (table["Scale"] != sol::lua_nil)
			{
				Vec3 scale = table["Scale"];
				newComponent->Scale = scale;
			}
		}
		break;
		case LuaComponentID::SoundSource:
		{
			auto newComponent = this->m_Scene->CreateComponent<SoundSource>(this->m_Entity);

			if (table["Looping"] != sol::lua_nil)
			{
				bool looping = table["Looping"];
				newComponent->SetLooping(looping);
			}

			if (table["Pitch"] != sol::lua_nil)
			{
				float pitch = table["Pitch"];
				newComponent->SetPitch(pitch);
			}

			if (table["Gain"] != sol::lua_nil)
			{
				float gain = table["Gain"];
				newComponent->SetGain(gain);
			}

			if (table["Sound"] != sol::lua_nil)
			{
				LuaSound sound = table["Sound"];
				newComponent->SetBuffer(sound.GetBuffer());
			}

			if (table["Play"] != sol::lua_nil && table["Play"] == true)
			{
				newComponent->Play();
			}
		}
		break;
		case LuaComponentID::SoundListener:
		{
			auto newComponent = this->m_Scene->CreateComponent<SoundListener>(this->m_Entity);
		}
		break;
		default:
		{
			VOLUND_WARNING("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}
	}

	void LuaEntity::DeleteComponent(sol::this_state s, LuaComponentID ComponentID, uint64_t index)
	{
		if (!this->m_Scene->HasEntity(this->m_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->m_Entity);

			return;
		}

		switch (ComponentID)
		{
		case LuaComponentID::Camera:
		{
			this->m_Scene->DeleteComponent<Camera>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::CameraMovement:
		{
			this->m_Scene->DeleteComponent<CameraMovement>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::MeshRenderer:
		{
			this->m_Scene->DeleteComponent<MeshRenderer>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::PointLight:
		{
			this->m_Scene->DeleteComponent<PointLight>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::Script:
		{
			this->m_Scene->DeleteComponent<Script>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::Tag:
		{
			this->m_Scene->DeleteComponent<Tag>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::Transform:
		{
			this->m_Scene->DeleteComponent<Transform>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::SoundSource:
		{
			this->m_Scene->DeleteComponent<SoundSource>(this->m_Entity, index);
		}
		break;
		case LuaComponentID::SoundListener:
		{
			this->m_Scene->DeleteComponent<SoundListener>(this->m_Entity, index);
		}
		break;
		default:
		{
			VOLUND_ERROR("Unknown ComponentID type (%d)!", ComponentID);
		}
		break;
		}
	}

	bool LuaEntity::HasComponent(sol::this_state s, LuaComponentID ComponentID)
	{
		if (!this->m_Scene->HasEntity(this->m_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->m_Entity);

			return false;
		}

		switch (ComponentID)
		{
		case LuaComponentID::Camera:
		{
			return this->m_Scene->HasComponent<Camera>(this->m_Entity);
		}
		break;
		case LuaComponentID::CameraMovement:
		{
			return this->m_Scene->HasComponent<CameraMovement>(this->m_Entity);
		}
		break;
		case LuaComponentID::MeshRenderer:
		{
			return this->m_Scene->HasComponent<MeshRenderer>(this->m_Entity);
		}
		break;
		case LuaComponentID::PointLight:
		{
			return this->m_Scene->HasComponent<PointLight>(this->m_Entity);
		}
		break;
		case LuaComponentID::Script:
		{
			return this->m_Scene->HasComponent<Script>(this->m_Entity);
		}
		break;
		case LuaComponentID::Tag:
		{
			return this->m_Scene->HasComponent<Tag>(this->m_Entity);
		}
		break;
		case LuaComponentID::Transform:
		{
			return this->m_Scene->HasComponent<Transform>(this->m_Entity);
		}
		break;
		case LuaComponentID::SoundSource:
		{
			return this->m_Scene->HasComponent<SoundSource>(this->m_Entity);
		}
		break;
		case LuaComponentID::SoundListener:
		{
			return this->m_Scene->HasComponent<SoundListener>(this->m_Entity);
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

	uint64_t LuaEntity::ComponentAmount(sol::this_state s, LuaComponentID ComponentID)
	{
		if (!this->m_Scene->HasEntity(this->m_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->m_Entity);

			return 0;
		}

		switch (ComponentID)
		{
		case LuaComponentID::Camera:
		{
			return this->m_Scene->ComponentAmount<Camera>(this->m_Entity);
		}
		break;
		case LuaComponentID::CameraMovement:
		{
			return this->m_Scene->ComponentAmount<CameraMovement>(this->m_Entity);
		}
		break;
		case LuaComponentID::MeshRenderer:
		{
			return this->m_Scene->ComponentAmount<MeshRenderer>(this->m_Entity);
		}
		break;
		case LuaComponentID::PointLight:
		{
			return this->m_Scene->ComponentAmount<PointLight>(this->m_Entity);
		}
		break;
		case LuaComponentID::Script:
		{
			return this->m_Scene->ComponentAmount<Script>(this->m_Entity);
		}
		break;
		case LuaComponentID::Tag:
		{
			return this->m_Scene->ComponentAmount<Tag>(this->m_Entity);
		}
		break;
		case LuaComponentID::Transform:
		{
			return this->m_Scene->ComponentAmount<Transform>(this->m_Entity);
		}
		break;
		case LuaComponentID::SoundSource:
		{
			return this->m_Scene->ComponentAmount<SoundSource>(this->m_Entity);
		}
		break;
		case LuaComponentID::SoundListener:
		{
			return this->m_Scene->ComponentAmount<SoundListener>(this->m_Entity);
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

	sol::table LuaEntity::GetComponent(sol::this_state s, LuaComponentID ComponentID, uint64_t index)
	{
		if (!this->m_Scene->HasEntity(this->m_Entity))
		{
			VOLUND_WARNING("Invalid this->_Entity %d!", this->m_Entity);

			return nullptr;
		}

		switch (ComponentID)
		{
		case LuaComponentID::Camera:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<Camera>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::CameraMovement:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<CameraMovement>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::MeshRenderer:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<MeshRenderer>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::PointLight:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<PointLight>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::Script:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<Script>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::Tag:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<Tag>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::Transform:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<Transform>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::SoundSource:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<SoundSource>(this->m_Entity, index));
		}
		break;
		case LuaComponentID::SoundListener:
		{
			return GenerateComponentTable(s, (*this), this->m_Scene->GetComponent<SoundListener>(this->m_Entity, index));
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

	sol::table LuaEntity::GetScript(sol::this_state s, sol::table table)
	{
		for (int i = 0; i < this->m_Scene->ComponentAmount<Script>(this->m_Entity); i++)
		{
			auto entityScript = this->m_Scene->GetComponent<Script>(this->m_Entity, i);
			if (entityScript->Compare(table))
			{
				return entityScript->Table;
			}
		}

		VOLUND_WARNING("Entity does not conntain Script!");

		return nullptr;
	}

	LuaEntity::LuaEntity(Ref<Scene> scene, Entity entity)
	{
		this->m_Scene = scene;
		this->m_Entity = entity;
	}
}