 #pragma once

#include "Dispatcher/Event/Event.h"
#include "Component/Component.h"
#include "PolyContainer/PolyContainer.h"

#include "Rendering/Framebuffer/Framebuffer.h"

#include "Input/Input.h"

namespace Volund
{
	typedef uint64_t Entity;
}

#define VOLUND_ENTITY_CREATE(id, index) ((uint64_t)id << 32) | ((uint64_t)index)

#define VOLUND_ENTITY_GET_ID(entity) (entity >> 32)
#define VOLUND_ENTITY_GET_INDEX(entity) entity & 0x00000000FFFFFFFF

#define VOLUND_NULL_ENTITY (::VL::Entity)-1

namespace Volund
{
	class Scene
	{
	public:

		struct ComponentEntry
		{
			size_t TypeId = 0;
			Ref<Component> component;

			template<typename T>
			bool Is();

			template<typename T>
			Ref<T> As();
		};

		struct EntityEntry
		{
			Entity entity;
			std::vector<ComponentEntry> Components;

			std::vector<ComponentEntry>::iterator begin();
			std::vector<ComponentEntry>::iterator end();
		};

		CHRONO_TIME_POINT GetStartTime();

		Entity AllocateEntity();

		void DeallocateEntity(Entity entity);

		bool IsAllocated(Entity entity);

		template<typename T, typename... Args>
		Ref<T> CreateComponent(Entity entity, Args&&... args);

		template<typename T>
		void DeleteComponent(Entity entity, uint64_t index = 0);

		template<typename T>
		bool HasComponent(Entity entity, uint64_t index = 0);	

		template<typename T>
		uint64_t ComponentAmount(Entity entity);

		template<typename T>
		Ref<T> GetComponent(Entity entity, uint64_t index = 0);
		
		void Procedure(const Event& e);

		std::vector<EntityEntry>::iterator begin();
		std::vector<EntityEntry>::iterator end();

		static Ref<Scene> Create();

		~Scene();

	private:

		Scene();

		static std::vector<ComponentEntry>::iterator LowerBound(std::vector<ComponentEntry>& components, const size_t& typeId);
		
		static std::vector<ComponentEntry>::iterator UpperBound(std::vector<ComponentEntry>& components, const size_t& typeId);

		std::vector<EntityEntry> m_EntityHeap;
		std::vector<uint32_t> m_FreeEntries;

		CHRONO_TIME_POINT m_StartTime;
	};

	bool operator<(const size_t& a, const Scene::ComponentEntry& b);
	bool operator<(const Scene::ComponentEntry& a, const size_t& b);
}

#include "Scene_Impl.h"