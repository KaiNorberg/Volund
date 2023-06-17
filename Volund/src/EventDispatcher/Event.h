#pragma once

#include "Utils/Utils.h"

//UPDATE

#define VOLUND_EVENT_UPDATE_SET_TIMESTEP(E, Value) E.Args[0] = Volund::Utils::CastFloatToInt(Value);
#define VOLUND_EVENT_UPDATE_GET_TIMESTEP(E) Volund::Utils::CastIntToFloat(E.Args[0]);

//KEY

#define VOLUND_EVENT_KEY_SET_KEY(E, Value) E.Args[0] = Value
#define VOLUND_EVENT_KEY_GET_KEY(E) E.Args[0]

#define VOLUND_EVENT_KEY_SET_ISDOWN(E, Value) E.Args[1] = Value
#define VOLUND_EVENT_KEY_GET_ISDOWN(E) E.Args[1]

//MOUSE_MOVE

#define VOLUND_EVENT_MOUSE_MOVE_SET_XPOS(E, Value) E.Args[0] = Value
#define VOLUND_EVENT_MOUSE_MOVE_GET_XPOS(E) E.Args[0]

#define VOLUND_EVENT_MOUSE_MOVE_SET_YPOS(E, Value) E.Args[1] = Value
#define VOLUND_EVENT_MOUSE_MOVE_GET_YPOS(E) E.Args[1]

//MOUSE_BUTTON

#define VOLUND_EVENT_MOUSE_BUTTON_SET_BUTTON(E, Value) E.Args[0] = Value
#define VOLUND_EVENT_MOUSE_BUTTON_GET_BUTTON(E) E.Args[0]

#define VOLUND_EVENT_MOUSE_BUTTON_SET_ISDOWN(E, Value) E.Args[1] = Value
#define VOLUND_EVENT_MOUSE_BUTTON_GET_ISDOWN(E) E.Args[1]

//MOUSE_WHEEL

#define VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(E, Value) E.Args[0] = Volund::Utils::CastFloatToInt(Value);
#define VOLUND_EVENT_MOUSE_WHEEL_GET_DELTA(E) Volund::Utils::CastIntToFloat(E.Args[0]);

//WINDOW_SIZE

#define VOLUND_EVENT_WINDOW_SIZE_SET_WIDTH(E, Value) E.Args[0] = Value
#define VOLUND_EVENT_WINDOW_SIZE_GET_WIDTH(E) E.Args[0]

#define VOLUND_EVENT_WINDOW_SIZE_SET_HEIGHT(E, Value) E.Args[1] = Value
#define VOLUND_EVENT_WINDOW_SIZE_GET_HEIGHT(E) E.Args[1]

#define VOLUND_EVENT_TYPE_NONE 0
#define VOLUND_EVENT_TYPE_UPDATE 1
#define VOLUND_EVENT_TYPE_RENDER 2
#define VOLUND_EVENT_TYPE_WINDOW_CLOSE 3
#define VOLUND_EVENT_TYPE_WINDOW_SIZE 4
#define VOLUND_EVENT_TYPE_KEY 5
#define VOLUND_EVENT_TYPE_MOUSE_MOVE 6
#define VOLUND_EVENT_TYPE_MOUSE_BUTTON 7
#define VOLUND_EVENT_TYPE_MOUSE_WHEEL 8
#define VOLUND_HIGHEST_EVENT_TYPE 8

namespace Volund
{
	struct Event
	{
		uint32_t Type;

		uint32_t Args[2] = {0, 0};

		Event(uint32_t t) { Type = t; }
	};

	using Proc = void(const Event&);
}
