#include "PCH/PCH.h"

#include "Scene.h"

#include "Core/Lua/Lua.h"
#include "Core/Window/Window.h"

#include "Component/Components.h"
#include "Filesystem/Filesystem.h"
#include "Renderer/Renderer.h"

namespace Volund
{	
	std::string Scene::GetFilepath()
	{
		return _Data.Filepath;
	}

	Ref<Framebuffer> Scene::GetTargetBuffer()
	{
		return _Data.TargetBuffer;
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

	void Scene::Render(TimeStep TS)
	{
		Renderer::Begin();

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

	void Scene::ResizeTarget(uint32_t Width, uint32_t Height)
	{
		auto Spec = _Data.TargetBuffer->GetSpec();

		if (_Data.TargetBuffer != nullptr && (Width != Spec.Width || Height != Spec.Height))
		{
			Spec.Width = Width;
			Spec.Height = Height;

			_Data.TargetBuffer->SetSpec(Spec);
		}
	}

	void Scene::EventCallback(Event* E)
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
			Scene::Destroy();
		}

		Window::Reset();

		VOLUND_INFO("Deserializing Scene...");

		VL::FramebufferSpec Spec;
		Spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
		Spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::DEPTH24STENCIL8);
		Spec.Height = Window::GetSize().y;
		Spec.Width = Window::GetSize().x;
		_Data.TargetBuffer = VL::Framebuffer::Create(Spec);

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

	void Scene::Destroy()
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

		_Data = SceneData();
	}

	Scene::~Scene()
	{
		Scene::Destroy();
	}

	uint64_t Scene::FindEntity(Entity entity)
	{
		auto it = std::lower_bound(_Data.Registry.begin(), _Data.Registry.end(), entity, [](const std::pair<Entity, Container<Component>>& A, Entity entity)
		{
			return A.first < entity;
		});

		if (it != _Data.Registry.end())
		{
			return it - _Data.Registry.begin();
		}
		else
		{
			return -1;
		}
	}
}
