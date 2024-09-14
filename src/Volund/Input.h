#pragma once

#include "Dispatcher/Event.h"

#include "Math/Math.h"

#include <cstdint>

#define VOLUND_KEY_AMOUNT 348
#define VOLUND_MOUSE_BUTTON_AMOUNT 8

#define VOLUND_MOUSE_BUTTON_MIDDLE 2
#define VOLUND_MOUSE_BUTTON_LEFT 0
#define VOLUND_MOUSE_BUTTON_RIGHT 1

#define VOLUND_KEY_SPACE 32
#define VOLUND_KEY_TAB 258
#define VOLUND_KEY_ENTER 257
#define VOLUND_KEY_SHIFT 340
#define VOLUND_KEY_CONTROL 341
#define VOLUND_KEY_ESCAPE 256

namespace Volund
{
    class Input
    {
    public:

        bool IsHeld(uint16_t keyCode) const;
        bool IsPressed(uint16_t keyCode);

        bool IsMouseButtonHeld(uint16_t button) const;
        bool IsMouseButtonPressed(uint16_t button);

        float GetScrollPosition() const;

        IVec2 GetMousePosition() const;

        void Procedure(const Event& e);

        Input();

    private:

        IVec2 m_MousePosition = IVec2(0);

        float m_ScrollPosition = 0.0f;

        bool m_MouseButtons[VOLUND_MOUSE_BUTTON_AMOUNT];
        bool m_Keys[VOLUND_KEY_AMOUNT];
    };
}
