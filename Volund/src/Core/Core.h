#pragma once

#define VOLUND_ASSERT(Check, ...) if (!(bool)(Check)) { VOLUND_ERROR(__VA_ARGS__); }

#define VOLUND_KEY_AMOUNT 348
#define VOLUND_MOUSE_BUTTON_AMOUNT 8

#define VOLUND_MOUSE_BUTTON_MIDDLE 2
#define VOLUND_MOUSE_BUTTON_LEFT 0
#define VOLUND_MOUSE_BUTTON_RIGHT 1

namespace Volund
{
	/// <summary>
	/// Unique ptr
	/// </summary>
	template <typename T>
	using Scope = std::unique_ptr<T>;

	/// <summary>
	/// Shared ptr
	/// </summary>
	template <typename T>
	using Ref = std::shared_ptr<T>;
}
