#include "PCH/PCH.h"

#include "Scene.h"

#include "Window/Window.h"

#include "Component/Components.h"
#include "Filesystem/Filesystem.h"
#include "Renderer/Renderer.h"

#include "ThreadPool/ThreadPool.h"

namespace Volund
{
	std::chrono::time_point<std::chrono::steady_clock> Scene::GetStartTime()
	{
		return this->_StartTime;
	}

	Ref<Framebuffer> Scene::GetTargetBuffer()
	{
		return this->_TargetBuffer;
	}

	Entity Scene::CreateEntity()
	{
		Entity NewEntity = this->_NewEntity;

		this->_Registry.push_back(std::pair<Entity, Container<Component>>(NewEntity, Container<Component>()));

		this->_NewEntity++;
		return NewEntity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		uint64_t Index = FindEntity(entity);

		if (Index != -1)
		{
			this->_Registry.erase(this->_Registry.begin() + Index);
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

	void Scene::ResizeTarget(uint32_t Width, uint32_t Height)
	{
		auto Spec = this->_TargetBuffer->GetSpec();

		if (this->_TargetBuffer != nullptr && (Width != Spec.Width || Height != Spec.Height))
		{
			Spec.Width = Width;
			Spec.Height = Height;

			this->_TargetBuffer->SetSpec(Spec);
		}
	}

	void Scene::Procedure(const Event& E)
	{
		for (const auto& [entity, Container] : this->_Registry)
		{
			for (auto& [TypeID, Components] : Container)
			{
				for (const auto& component : Components)
				{
					component->Procedure(E);
				}
			}
		}
	}

	Registry::iterator Scene::begin()
	{
		return this->_Registry.begin();
	}

	Registry::iterator Scene::end()
	{
		return this->_Registry.end();
	}

	Scene::Scene()
	{
		VL::FramebufferSpec Spec;
		Spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
		Spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::DEPTH24STENCIL8);
		Spec.Height = 1080;
		Spec.Width = 1920;
		this->_TargetBuffer = VL::Framebuffer::Create(Spec);

		this->_StartTime = std::chrono::high_resolution_clock::now();
	}

	uint64_t Scene::FindEntity(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		auto it = std::lower_bound(this->_Registry.begin(), this->_Registry.end(), entity, [](const std::pair<Entity, Container<Component>>& A, Entity entity)
		{
			return A.first < entity;
		});

		if (it != this->_Registry.end())
		{
			return it - this->_Registry.begin();
		}
		else
		{
			return -1;
		}
	}

	Scene::~Scene()
	{
		for (const auto& [entity, Container] : this->_Registry)
		{
			for (auto& [TypeID, Components] : Container)
			{
				for (const auto& component : Components)
				{
					component->OnDestroy();
				}
			}
		}
	}
}
