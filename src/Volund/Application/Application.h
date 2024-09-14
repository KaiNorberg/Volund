#pragma once

#include "Module/Module.h"

#include "Time/Time.h"
#include "PolyContainer/PolyContainer.h"
#include "Dispatcher/Dispatcher.h"

#include "Window/Window.h"
#include "GameState/GameState.h"

namespace Volund
{
    class Application
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

        virtual void OnRun() {}
        virtual void OnTerminate() {}
        virtual void Procedure(const Event& e) {}

        Application();

        virtual ~Application();

    private:

        friend class Dispatcher;

        void Loop();

        void EventCallback(const Event& e);

        bool m_ShouldRun = true;

        std::shared_ptr<Window> m_Window;
        std::shared_ptr<Dispatcher> m_Dispatcher;

        PolyContainer<Module> m_Modules;

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
        this->m_Modules.PushBack(newModule);
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

        return this->m_Modules.Get<T>();
    }

    template<typename T>
    inline bool Application::HasModule()
    {
        return this->m_Modules.Contains<T>();
    }
}
