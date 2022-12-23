#pragma once

namespace Volund
{
	enum class EventType
	{
		NONE,
		UPDATE,
		RENDER,
		WINDOW_CLOSE,
		WINDOW_SIZE,
		KEY,
		MOUSE_MOVE,
		MOUSE_BUTTON,
		MOUSE_WHEEL,
	};
}
