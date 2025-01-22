#pragma once

#include "Module.h"

#include "Time.h"
#include "PolyContainer.h"
#include "Dispatcher.h"

#include "Window.h"

namespace Volund
{
    class VOLUND_API Application
    {
    public:
        void Run();
        bool ShouldRun() const;
        std::shared_ptr<Window> GetWindow();
        std::shared_ptr<Dispatcher> GetDispatcher();
        template <typename T, typename... Args>
        std::shared_ptr<T> AttachModule(Args&&... args);
        template<typename T>
        std::shared_ptr<T> GetModule();
        template<typename T>
        bool HasModule();
        virtual void Procedure(const Event& e) {}
        Application();
        virtual ~Application();
    private:
        friend class Dispatcher;
        void Loop();
        void EventCallback(const Event& e);
        bool m_shouldRun = true;
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Dispatcher> m_dispatcher;
        PolyContainer<Module> m_modules;
    protected:
        void Terminate();
    };

    template<typename T, typename ...Args>
    inline std::shared_ptr<T> Application::AttachModule(Args && ...args)
    {
        if (this->HasModule<T>())
        {
            VOLUND_ERROR("Module of specifed type already attached!");
        }

        std::shared_ptr<T> newModule = std::make_shared<T>(args...);
        this->m_modules.PushBack(newModule);
        newModule->OnAttach(this);
        return newModule;
    }

    template<typename T>
    inline std::shared_ptr<T> Application::GetModule()
    {
        if (!this->HasModule<T>())
        {
            VOLUND_ERROR("Application does not have Module of specifed type!");
        }

        return this->m_modules.Get<T>();
    }

    template<typename T>
    inline bool Application::HasModule()
    {
        return this->m_modules.Contains<T>();
    }
}
