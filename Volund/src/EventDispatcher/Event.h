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

		uint32_t GetWidth() const { return _Width; }

		uint32_t GetHeight() const { return _Height; }

		WindowSizeEvent(uint32_t Width, uint32_t Height) : _Width(Width), _Height(Height)
		{
		};

	private:
		uint32_t _Width;
		uint32_t _Height;
	};

	class KeyEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::KEY; }

		uint32_t GetKey() const { return _Key; }

		bool GetIsDown() const { return _IsDown; }

		KeyEvent(int32_t Key, bool IsDown) : _Key(Key), _IsDown(IsDown)
		{
		};

	private:
		int32_t _Key;
		bool _IsDown;
	};

	class MouseButtonEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::MOUSE_BUTTON; }

		uint32_t GetButton() const { return _Button; }

		uint32_t GetIsDown() const { return _IsDown; }

		MouseButtonEvent(int32_t Button, bool IsDown) : _Button(Button), _IsDown(IsDown)
		{
		};

	private:
		int32_t _Button;
		bool _IsDown;
	};

	class ScrollEvent : public Event
	{
	public:
		const EventType GetType() override { return EventType::SCROLL; }

		uint32_t GetXOffset() const { return _xOffset; }

		uint32_t GetYOffset() const { return _yOffset; }

		ScrollEvent(uint32_t xOffset, uint32_t yOffset) : _xOffset(xOffset), _yOffset(yOffset)
		{
		};

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

		MouseMoveEvent(int32_t xPos, int32_t yPos) : _xPos(xPos), _yPos(yPos)
		{
		};

	private:
		int32_t _xPos;
		int32_t _yPos;
	};
}
