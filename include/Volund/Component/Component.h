#pragma once

#include "../Time.h"

#include "../Event.h"

namespace Volund
{
    class Scene;

    using Entity = uint64_t;

    class Component
    {
    public:
        virtual void Procedure(const Event& e) {}
        Entity GetEntity() const;
        std::shared_ptr<Scene> GetScene() const;
        Component() = default;
        virtual ~Component() = default;
    private:
        friend class Scene;
        void Init(Entity entity, std::weak_ptr<Scene> scene);
        Entity m_entity = 0;
        std::weak_ptr<Scene> m_scene;
    };
}