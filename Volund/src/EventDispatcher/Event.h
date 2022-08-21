#pragma once

#include "EventType.h"

namespace Volund
{
	class Event
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

		uint32_t GetWidth() { return _Width; }

		uint32_t GetHeight() { return _Height; }

		WindowSizeEvent(uint32_t Width, uint32_t Height) : _Width(Width), _Height(Height) {};

	private:

		uint32_t _Width;
		uint32_t _Height;
	};	
	
	class KeyEvent : public Event
	{
	public:

		const EventType GetType() override { return EventType::KEY; }

		uint32_t GetKey() { return _Key; }

		uint32_t GetScancode() { return _Scancode; }

		uint32_t GetAction() { return _Action; }

		uint32_t GetMods() { return _Mods; }

		KeyEvent(int32_t Key, int32_t Scancode, int32_t Action, uint32_t Mods) : _Key(Key), _Scancode(Scancode), _Action(Action), _Mods(Mods) {};

	private:
		int32_t _Key;
		int32_t _Scancode;
		int32_t _Action;
		int32_t _Mods;
	};

	class MouseButtonEvent : public Event
	{
	public:

		const EventType GetType() override { return EventType::MOUSE_BUTTON; }

		uint32_t GetButton() { return _Button; }

		uint32_t GetAction() { return _Action; }

		uint32_t GetMods() { return _Mods; }

		MouseButtonEvent(int32_t Button, int32_t Action, uint32_t Mods) : _Button(Button), _Action(Action), _Mods(Mods) {};

	private:
		int32_t _Button;
		int32_t _Action;
		int32_t _Mods;
	};

	class ScrollEvent : public Event
	{
	public:

		const EventType GetType() override { return EventType::SCROLL; }

		double GetXOffset() { return _xOffset; }

		double GetYOffset() { return _yOffset; }

		ScrollEvent(double xOffset, double yOffset) : _xOffset(xOffset), _yOffset(yOffset) {};

	private:
		double _xOffset;
		double _yOffset;
	};

	class CursorPosEvent : public Event
	{
	public:

		const EventType GetType() override { return EventType::CURSOR_POS; }

		double GetXPos() { return _xPos; }

		double GetYPos() { return _yPos; }

		CursorPosEvent(double xPos, double yPos) : _xPos(xPos), _yPos(yPos) {};

	private:
		double _xPos;
		double _yPos;
	};
}
