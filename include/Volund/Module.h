#pragma once

#include "Time.h"
#include "Event.h"

namespace Volund
{
    class Application;

    class Module
    {
    public:
        virtual void OnAttach(Application* app) = 0;
        virtual void OnDetach() = 0;
        virtual void Procedure(const Event& e) = 0;
        Module();
        virtual ~Module();
    private:
    };
}
