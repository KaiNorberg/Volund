#pragma once

#include "EventType.h"

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

#define VOLUND_EVENT_MOUSE_WHEEL_SET_DELTA(E, Value) E.Args[0] = Value
#define VOLUND_EVENT_MOUSE_WHEEL_GET_DELTA(E) E.Args[0]

//WINDOW_SIZE

#define VOLUND_EVENT_WINDOW_SIZE_SET_WIDTH(E, Value) E.Args[0] = Value
#define VOLUND_EVENT_WINDOW_SIZE_GET_WIDTH(E) E.Args[0]

#define VOLUND_EVENT_WINDOW_SIZE_SET_HEIGHT(E, Value) E.Args[1] = Value
#define VOLUND_EVENT_WINDOW_SIZE_GET_HEIGHT(E) E.Args[1]

namespace Volund
{
	struct Event
	{
		EventType Type;

		uint32_t Args[2] = {0, 0};

		Event(EventType t) { Type = t; }
	};

	using Proc = void(const Event&);

	/*class Event
	{
	public:
		const virtual EventType GetType() { return EventType::NONE; }

		virtual ~Event() = default;

	private:
	};

	class WindowCloseEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::WINDOW_CLOSE; }

	private:
	};

	class WindowSizeEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::WINDOW_SIZE; }

		uint32_t GetWidth() const { return _Width; }

		uint32_t GetHeight() const { return _Height; }

		WindowSizeEvent(uint32_t Width, uint32_t Height) : _Width(Width), _Height(Height) {}

	private:
		uint32_t _Width;
		uint32_t _Height;
	};

	class KeyEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::KEY; }

		uint32_t GetKey() const { return _Key; }

		bool IsDown() const { return _IsDown; }

		KeyEvent(uint32_t Key, bool IsDown) : _Key(Key), _IsDown(IsDown) {}

	private:
		uint32_t _Key;
		bool _IsDown;
	};

	class MouseButtonEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::MOUSE_BUTTON; }

		uint32_t GetButton() const { return _Button; }

		bool IsDown() const { return _IsDown; }

		MouseButtonEvent(uint32_t Button, bool IsDown) : _Button(Button), _IsDown(IsDown) {}

	private:
		uint32_t _Button;
		bool _IsDown;
	};

	class ScrollEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::SCROLL; }

		uint32_t GetXOffset() const { return _xOffset; }

		uint32_t GetYOffset() const { return _yOffset; }

		ScrollEvent(uint32_t xOffset, uint32_t yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}

	private:
		uint32_t _xOffset;
		uint32_t _yOffset;
	};

	class MouseMoveEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::MOUSE_MOVE; }

		int32_t GetXPos() const { return _xPos; }

		int32_t GetYPos() const { return _yPos; }

		MouseMoveEvent(int32_t xPos, int32_t yPos) : _xPos(xPos), _yPos(yPos) {}

	private:
		int32_t _xPos;
		int32_t _yPos;
	};*/
}
