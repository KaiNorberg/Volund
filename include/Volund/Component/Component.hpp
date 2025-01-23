#pragma once

#include "../Time.hpp"
#include "../Event.hpp"
#include "../Entity.hpp"

#include <sol/sol.hpp>

namespace Volund
{
    class VOLUND_API Scene;

    class VOLUND_API Component
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