#pragma once

#include "../Time.h"
#include "../Event.h"
#include "../Entity.h"

namespace Volund
{
    class Scene;

    class Component
    {
    public:
        virtual void Procedure(const Event& e) {}
        virtual void OnInit() {};
        Entity GetEntity() const;
        std::shared_ptr<Scene> GetScene() const;
        Component() = default;
        virtual ~Component() = default;
    private:
        friend class Scene;
        void Init(Entity entity, std::weak_ptr<Scene> scene);
        Entity m_entity;
        std::weak_ptr<Scene> m_scene;
    };
}