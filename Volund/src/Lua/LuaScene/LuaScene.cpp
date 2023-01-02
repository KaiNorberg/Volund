#include "PCH/PCH.h"
#include "LuaScene.h"

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
		return LuaEntity(this->_Scene.get());
	}

	LuaEntity LuaScene::CreateEntityWithComponents(sol::this_state S, sol::table Components)
	{
		LuaEntity NewEntity = this->CreateEntity();

		for (auto& Component : Components)
		{
			sol::table ComponentTable = ((sol::table)Component.second);
			NewEntity.AddComponent(S, ComponentTable[1], ComponentTable[2]);
		}

		return NewEntity;
	}

	sol::table LuaScene::ComponentView(sol::this_state S, LuaComponentID Component)
	{
		switch (Component)
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
			VOLUND_ERROR("Unknown Component type (%d)!", Component);
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

		for (auto& Component : View)
		{
			if (Component->Compare(ScriptTable))
			{
				Output.add(Component->Table);
			}
		}

		return Output;
	}

	LuaScene::LuaScene(Ref<Scene> scene)
	{
		this->_Scene = scene;
	}
}