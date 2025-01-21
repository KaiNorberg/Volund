#pragma once

#include "Input.h"
#include "Instrumentor.h"
#include "Event.h"
#include "Entity.h"
#include "Component/Component.h"
#include "PolyContainer.h"
#include "Rendering/Framebuffer.h"

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
        class EntityRecord
        {
        public:
            std::vector<ComponentEntry>::iterator begin();
            std::vector<ComponentEntry>::iterator end();
            std::vector<ComponentEntry>::iterator Find(uint64_t typeId, uint64_t index);
            Entity Get() { return this->m_entity; }
            EntityRecord(Entity entity) : m_entity(entity) {}
        private:
            friend class Scene;
            Entity m_entity;
            std::vector<ComponentEntry> m_components;
        };
        struct IndirectionEntry
        {
            uint32_t recordIndex;
            uint32_t generation;
            bool avail;
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
        std::vector<EntityRecord>::iterator begin();
        std::vector<EntityRecord>::iterator end();
        Scene();
        ~Scene();
    private:
        std::vector<EntityRecord> m_entites;
        std::vector<IndirectionEntry> m_indirectionTable;
        uint32_t m_newGeneration = 1;
        CHRONO_TIME_POINT m_startTime;
    };

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
            VOLUND_ERROR("Attempted to add component to unregistered entity!");
            return nullptr;
        }

        EntityRecord& record = m_entites[m_indirectionTable[entity.index].recordIndex];
        uint64_t typeId = Utils::GetTypeId<T>();
        auto it = record.Find(typeId, 0);

        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->Init(record.m_entity, this->weak_from_this());

        record.m_components.insert(it, ComponentEntry(typeId, component));

        return component;
    }

    template <typename T>
    inline void Scene::RemoveComponent(Entity entity, uint64_t index)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            VOLUND_ERROR("Attempted to remove component from unregistered entity!");
        }

        EntityRecord& record = m_entites[m_indirectionTable[entity.index].recordIndex];
        uint64_t typeId = Utils::GetTypeId<T>();
        auto it = record.Find(typeId, index);
        if (it != record.m_components.end())
        {
            record.m_components.erase(it);
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

        EntityRecord& record = m_entites[m_indirectionTable[entity.index].recordIndex];
        uint64_t typeId = Utils::GetTypeId<T>();
        auto it = record.Find(typeId, index);
        return it != record.m_components.end();
    }

    template<typename T>
    inline uint64_t Scene::ComponentAmount(Entity entity)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            return 0;
        }

        EntityRecord& record = m_entites[m_indirectionTable[entity.index].recordIndex];
        uint64_t typeId = Utils::GetTypeId<T>();
        auto it = record.Find(typeId, 0);

        uint64_t count = 0;
        while (it != record.m_components.end() && it->GetTypeId() == typeId)
        {
            count++;
            it++;
        }
        
        return count;
    }

    template<typename T>
    inline std::shared_ptr<T> Scene::GetComponent(Entity entity, uint64_t index)
    {
        VOLUND_PROFILE_FUNCTION();

        if (!IsRegistered(entity))
        {
            VOLUND_ERROR("Attempted to get component from unregistered entity!");
            return nullptr;
        }

        EntityRecord& record = m_entites[m_indirectionTable[entity.index].recordIndex];
        uint64_t typeId = Utils::GetTypeId<T>();
        auto it = record.Find(typeId, index);
        
        if (it != record.m_components.end())
        {
            return std::static_pointer_cast<T>(it->m_component);
        }
        
        VOLUND_ERROR("Component not found!");
        return nullptr;
    }
}
