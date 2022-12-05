#include "PCH/PCH.h"

#include "Scene.h"

#include "Scene/Component/Components.h"

#include "Filesystem/Filesystem.h"

#include "Renderer/Renderer.h"

#include "Lua/Lua.h"

namespace Volund
{	
	std::string Scene::GetFilepath()
	{
		return _Data.Filepath;
	}

	Input& Scene::GetInput()
	{
		return _Data.MainInput;
	}

	Entity Scene::CreateEntity()
	{
		Entity NewEntity = _Data.NewEntity;

		_Data.Registry.push_back(std::pair<Entity, Container<Component>>(NewEntity, Container<Component>()));

		_Data.NewEntity++;
		return NewEntity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			_Data.Registry.erase(_Data.Registry.begin() + Index);
		}
		else
		{
			VOLUND_ERROR("Unable to find entity (%d)", entity);
		}
	}

	bool Scene::HasEntity(Entity entity)
	{
		return FindEntity(entity) != -1;
	}

	void Scene::DeleteComponent(Component* component)
	{
		for (auto& [entity, Container] : _Data.Registry)
		{
			if (Container.Erase(component))
			{
				return;
			}
		}			
		
		VOLUND_ERROR("Unable to find component (%d)", component);
	}

	void Scene::OnUpdate(TimeStep TS)
	{
		VL::Camera* ActiveCamera = VL::Camera::GetActiveCamera();

		if (ActiveCamera != nullptr)
		{
			IVec2 ViewSize = RenderingAPI::GetViewSize();

			Renderer::Begin(ActiveCamera->GetViewMatrix(), ActiveCamera->GetProjectionMatrix((float)ViewSize.x / (float)ViewSize.y));

		}
		else
		{
			Renderer::Begin(Mat4x4(1.0f), Mat4x4(1.0f));
		}

		for (const auto& [entity, Container] : _Data.Registry)
		{	
			for (const auto& View : Container)
			{
				for (const auto& component : View)
				{
					component->OnUpdate(TS);
				}
			}
		}

		Renderer::End();
	}

	void Scene::OnEvent(Event* E)
	{
		_Data.MainInput.HandleEvent(E);

		for (const auto& [entity, Container] : _Data.Registry)
		{
			for (const auto& View : Container)
			{
				for (const auto& component : View)
				{
					component->OnEvent(E);
				}
			}
		}
	}

	Registry::iterator Scene::begin()
	{
		return _Data.Registry.begin();
	}

	Registry::iterator Scene::end()
	{
		return _Data.Registry.end();
	}

	void Scene::Load(const std::string& Filepath)
	{
		if (!_Data.Filepath.empty())
		{
			for (const auto& [entity, Container] : _Data.Registry)
			{
				for (const auto& View : Container)
				{
					for (const auto& component : View)
					{
						component->OnDelete();
					}
				}
			}

			std::string ParentPath = std::filesystem::path(_Data.Filepath).parent_path().string();
			VL::Filesystem::RemoveRelativeFilepath(ParentPath);
		}

		VOLUND_INFO("Deserializing Scene...");
		
		_Data = SceneData();
		_Data.Filepath = Filepath;

		std::string ParentPath = std::filesystem::path(Filepath).parent_path().string();
		VL::Filesystem::AddRelativeFilepath(ParentPath);

		try
		{
			Lua::Connect(_Data.LuaState);
			_Data.LuaState.script_file(_Data.Filepath);
		}
		catch (sol::error E)
		{
			VOLUND_WARNING(E.what());
		}

		VOLUND_INFO("Finished deserializing Scene!");
	}

	uint64_t Scene::FindEntity(Entity entity) 
	{
		for (int i = 0; i < _Data.Registry.size(); i++)
		{
			if (_Data.Registry[i].first == entity)
			{
				return i;
			}
		}

		return -1;
	}
}
