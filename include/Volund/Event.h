#pragma once

#include "Utils.h"

#include <cstdint>

//UPDATE

#define VOLUND_EVENT_UPDATE_SET_TIMESTEP(E, Value) E.args[0] = Volund::Utils::CastFloatToInt(Value);
#define VOLUND_EVENT_UPDATE_GET_TIMESTEP(E) Volund::Utils::CastIntToFloat(E.args[0]);

//KEY

#define VOLUND_EVENT_KEY_SET_KEY(E, Value) E.args[0] = Value
#define VOLUND_EVENT_KEY_GET_KEY(E) E.args[0]

#define VOLUND_EVENT_KEY_SET_ISDOWN(E, Value) E.args[1] = Value
#define VOLUND_EVENT_KEY_GET_ISDOWN(E) E.args[1]

//MOUSE_MOVE

#define VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(E, Value) E.args[0] = Value
#define VOLUND_EVENT_MOUSE_MOVE_GET_XPOS(E) E.args[0]

#define VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(E, Value) E.args[1] = Value
#define VOLUND_EVENT_MOUSE_MOVE_GET_YPOS(E) E.args[1]

//MOUSE_BUTTON

#define VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(E, Value) E.args[0] = Value
#define VOLUND_EVENT_MOUSE_BUTTON_GET_BUTTON(E) E.args[0]

#define VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(E, Value) E.args[1] = Value
#define VOLUND_EVENT_MOUSE_BUTTON_GET_ISDOWN(E) E.args[1]

//MOUSE_WHEEL

#define VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(E, Value) E.args[0] = Volund::Utils::CastFloatToInt(Value);
#define VOLUND_EVENT_MOUSE_WHEEL_GET_DELTA(E) Volund::Utils::CastIntToFloat(E.args[0]);

//RESIZE

#define VOLUND_EVENT_RESIZE_SET_WIDTH(E, Value) E.args[0] = Value
#define VOLUND_EVENT_RESIZE_GET_WIDTH(E) E.args[0]

#define VOLUND_EVENT_RESIZE_SET_HEIGHT(E, Value) E.args[1] = Value
#define VOLUND_EVENT_RESIZE_GET_HEIGHT(E) E.args[1]

//EVENT_TYPE

#define VOLUND_EVENT_FLAG_ASYNC (1 << 8)

#define VOLUND_EVENT_NONE 0
#define VOLUND_EVENT_UPDATE 1
#define VOLUND_EVENT_RENDER 2
#define VOLUND_EVENT_CLOSE 3
#define VOLUND_EVENT_RESIZE 4
#define VOLUND_EVENT_KEY 5
#define VOLUND_EVENT_MOUSE_MOVE 6
#define VOLUND_EVENT_MOUSE_BUTTON 7
#define VOLUND_EVENT_MOUSE_WHEEL 8

#define VOLUND_EVENT_USER (1 << 6)

namespace Volund
{
    struct Event
    {
        uint32_t type;

        uint32_t args[2] = {0, 0};

        Event(uint32_t t) { this->type = t; }
    };

    using Proc = void(const Event&);
}
