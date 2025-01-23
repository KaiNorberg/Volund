#pragma once

#include "Module.hpp"

#include "Time.hpp"
#include "Dispatcher.hpp"

#include "Window.hpp"

namespace Volund
{
    class VOLUND_API Application
    {
    public:
        void Run();
        bool ShouldRun() const;
        std::shared_ptr<Window> GetWindow();
        std::shared_ptr<Dispatcher> GetDispatcher();
        virtual void Procedure(const Event& e) = 0;
        Application();
        virtual ~Application();
    private:
        friend class Dispatcher;
        void Loop();
        void EventCallback(const Event& e);
        bool m_shouldRun = true;
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Dispatcher> m_dispatcher;
    protected:
        void Terminate();
    };
}
