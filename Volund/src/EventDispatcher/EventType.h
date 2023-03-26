#pragma once

namespace Volund
{
	enum class EventType
	{
		None,
		Update,
		Render,
		WindowClose,
		WindowSize,
		Key,
		MouseMove,
		MouseButton,
		MouseWheel,
	};
}
