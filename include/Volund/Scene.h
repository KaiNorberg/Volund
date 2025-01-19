#pragma once

#include "Input.h"
#include "Instrumentor.h"
#include "Event.h"
#include "Component/Component.h"
#include "PolyContainer.h"
#include "Rendering/Framebuffer.h"

namespace Volund
{
    typedef uint64_t Entity;
}

#define VOLUND_ENTITY_CREATE(id, index) ((uint64_t)id << 32) | ((uint64_t)index)

#define VOLUND_ENTITY_GET_ID(entity) (entity >> 32)
#define VOLUND_ENTITY_GET_INDEX(entity) (entity & 0x00000000FFFFFFFF)

#define VOLUND_ENTITY_NULL (::Volund::Entity)-1

namespace Volund
{
    class Scene : public std::enable_shared_from_this<Scene>
    {
    public:

        class ComponentEntry
        {
        public:
            template<typename T>
            bool Is();
            template<typename T>
            std::shared_ptr<T> As();
            uint64_t GetTypeId() const { return this->m_typeId; }
            ComponentEntry(uint64_t typeId, std::shared_ptr<Component> component) : m_typeId(typeId), m_component(component) {}
        private:
            friend class Scene;
            uint64_t m_typeId = 0;
            std::shared_ptr<Component> m_component;
        };

        class EntityEntry
        {
        public:
            std::vector<ComponentEntry>::iterator begin();
            std::vector<ComponentEntry>::iterator end();
            Entity Get() { return this->m_entity; }
            EntityEntry(Entity entity) : m_entity(entity) {}
        private:
            friend class Scene;
            Entity m_entity;
            std::vector<ComponentEntry> m_components;
        };

        CHRONO_TIME_POINT GetStartTime();

        Entity Register();

        void Unregister(Entity entity);

        bool IsRegistered(Entity entity);

        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Entity entity, Args&&... args);

        template<typename T>
        void RemoveComponent(Entity entity, uint64_t index = 0);

        template<typename T>
        bool HasComponent(Entity entity, uint64_t index = 0);

        template<typename T>
        uint64_t ComponentAmount(Entity entity);

        template<typename T>
        std::shared_ptr<T> GetComponent(Entity entity, uint64_t index = 0);

        void Procedure(const Event& e);

        std::vector<EntityEntry>::iterator begin();
        std::vector<EntityEntry>::iterator end();

        Scene();

        ~Scene();

    private:

        static std::vector<ComponentEntry>::iterator LowerBound(std::vector<ComponentEntry>& components, const size_t& typeId);

        static std::vector<ComponentEntry>::iterator UpperBound(std::vector<ComponentEntry>& components, const size_t& typeId);

        std::vector<EntityEntry> m_entityHeap;
        std::vector<uint32_t> m_freeEntries;

        CHRONO_TIME_POINT m_startTime;
    };

    bool operator<(const size_t& a, const Scene::ComponentEntry& b);
    bool operator<(const Scene::ComponentEntry& a, const size_t& b);

    template<typename T>
    inline bool Scene::ComponentEntry::Is()
    {
        return this->m_typeId == Utils::GetTypeId<T>();
    }

    template<typename T>
    inline std::shared_ptr<T> Scene::ComponentEntry::As()
    {
        return std::dynamic_pointer_cast<T>(this->m_component);
    }

    template<typename T, typename ...Args>
    inline std::shared_ptr<T> Scene::AddComponent(Entity entity, Args && ...args)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            VOLUND_ERROR("Unallocated entity detected!");
        }

        uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
        auto& entry = this->m_entityHeap[entityIndex];

        std::shared_ptr<T> newComponent = std::make_shared<T>(args...);
        newComponent->Init(entity, this->weak_from_this());
        
        size_t componentTypeId = Utils::GetTypeId<T>();

        auto insertPos = UpperBound(entry.m_components, componentTypeId);
        ComponentEntry newEntry = ComponentEntry(componentTypeId, newComponent);
        entry.m_components.insert(insertPos, newEntry);

        return newComponent;
    }

    template <typename T>
    inline void Scene::RemoveComponent(Entity entity, uint64_t index)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            VOLUND_ERROR("Unallocated entity detected!");
        }

        uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
        auto& entry = this->m_entityHeap[entityIndex];

        size_t componentTypeId = Utils::GetTypeId<T>();

        auto componentEntry = LowerBound(entry.m_components, componentTypeId) + index;

        if (componentEntry < entry.m_components.end() && componentEntry->m_typeId == componentTypeId)
        {
            entry.m_components.erase(componentEntry);
        }
        else
        {
            VOLUND_ERROR("Component out of bounds!");
        }
    }

    template<typename T>
    inline bool Scene::HasComponent(Entity entity, uint64_t index)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            return false;
        }

        uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
        auto& entry = this->m_entityHeap[entityIndex];

        size_t componentTypeId = Utils::GetTypeId<T>();

        auto componentEntry = LowerBound(entry.m_components, componentTypeId) + index;

        return componentEntry < entry.m_components.end() && componentEntry->m_typeId == componentTypeId;
    }

    template<typename T>
    inline uint64_t Scene::ComponentAmount(Entity entity)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            return false;
        }

        uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
        auto& entry = this->m_entityHeap[entityIndex];

        size_t componentTypeId = Utils::GetTypeId<T>();

        auto lower = LowerBound(entry.m_components, componentTypeId);
        auto upper = UpperBound(entry.m_components, componentTypeId);

        return upper - lower;
    }

    template<typename T>
    inline std::shared_ptr<T> Scene::GetComponent(Entity entity, uint64_t index)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            VOLUND_ERROR("Unallocated entity detected!");
        }

        uint64_t entityIndex = VOLUND_ENTITY_GET_INDEX(entity);
        auto& entry = this->m_entityHeap[entityIndex];

        size_t componentTypeId = Utils::GetTypeId<T>();

        auto componentEntry = LowerBound(entry.m_components, componentTypeId) + index;

        if (componentEntry < entry.m_components.end() && componentEntry->m_typeId == componentTypeId)
        {
            return componentEntry->As<T>();
        }
        else
        {
            VOLUND_ERROR("Component out of bounds!");
            return nullptr;
        }
    }
}
