#include "PCH/PCH.h"

#include "Scene.h"

#include "Window/Window.h"

#include "Component/Components.h"
#include "Filesystem/Filesystem.h"
#include "Renderer/Renderer.h"

#include "ThreadPool/ThreadPool.h"

namespace Volund
{
	CHRONO_TIME_POINT Scene::GetStartTime()
	{
		return this->m_StartTime;
	}

	Ref<Framebuffer> Scene::GetTargetBuffer()
	{
		return this->m_TargetBuffer;
	}

	Entity Scene::CreateEntity()
	{
		Entity newEntity = this->m_NewEntity;

		this->m_Registry.push_back(std::pair<Entity, Container<Component>>(newEntity, Container<Component>()));

		this->m_NewEntity++;
		return newEntity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		const uint64_t index = FindEntity(entity);

		if (index != -1)
		{
			this->m_Registry.erase(this->m_Registry.begin() + index);
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

	void Scene::ResizeTarget(const uint32_t width, const uint32_t height)
	{
		auto spec = this->m_TargetBuffer->GetSpec();

		if (this->m_TargetBuffer != nullptr && (width != spec.Width || height != spec.Height))
		{
			spec.Width = width;
			spec.Height = height;

			this->m_TargetBuffer->SetSpec(spec);
		}
	}

	void Scene::Procedure(const Event& e)
	{
		for (const auto& [entity, Container] : this->m_Registry)
		{
			for (auto& [TypeID, Components] : Container)
			{
				for (const auto& component : Components)
				{
					component->Procedure(e);
				}
			}
		}
	}

	Registry::iterator Scene::begin()
	{
		return this->m_Registry.begin();
	}

	Registry::iterator Scene::end()
	{
		return this->m_Registry.end();
	}

	Scene::Scene()
	{
		VL::FramebufferSpec spec;
		spec.ColorAttachments = { VL::TextureSpec(VL::TextureFormat::RGBA16F) };
		spec.DepthAttachment = VL::TextureSpec(VL::TextureFormat::Depth24Stencil8);
		spec.Height = 1080;
		spec.Width = 1920;					
		this->m_TargetBuffer = VL::Framebuffer::Create(spec);
	
		this->m_StartTime = std::chrono::high_resolution_clock::now();
	}

	uint64_t Scene::FindEntity(Entity entity)
	{
		VOLUND_PROFILE_FUNCTION();

		auto it = std::lower_bound(this->m_Registry.begin(), this->m_Registry.end(), entity, [](const std::pair<Entity, Container<Component>>& a, Entity entity)
		{
			return a.first < entity;
		});

		if (it != this->m_Registry.end())
		{
			return it - this->m_Registry.begin();
		}
		else
		{
			return -1;
		}
	}

	Scene::~Scene()
	{
		for (const auto& [entity, Container] : this->m_Registry)
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
