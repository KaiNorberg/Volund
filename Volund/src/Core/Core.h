#pragma once
	
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

//#define VOLUND_ENABLE_PROFILING
//#define VOLUND_DISABLE_MULTITHREADING

#ifdef _WIN32
#define CHRONO_TIME_POINT std::chrono::time_point<std::chrono::steady_clock>
#else
#define CHRONO_TIME_POINT std::chrono::_V2::system_clock::time_point
#endif

#ifdef _WIN32
	#define VOLUND_PATH_SEPERATOR '\\'
	#define VOLUND_INVALID_PATH_SEPERATOR '/'
#else
	#define VOLUND_PATH_SEPERATOR '/'
	#define VOLUND_INVALID_PATH_SEPERATOR '\\'
#endif

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

	/// <summary>
	/// Weak ptr
	/// </summary>
	template <typename T>
	using WeakRef = std::weak_ptr<T>;
}

namespace fs = std::filesystem;

namespace VL = Volund;
