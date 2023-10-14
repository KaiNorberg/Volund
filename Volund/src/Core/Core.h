#pragma once

#define SOL_NO_EXCEPTIONS 0
#define SOL_PRINT_ERRORS 0
#define SOL_SAFE_NUMERICS 1

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

#define VOLUND_SERIAL_FILE_TYPE "FileType"
#define VOLUND_SERIAL_DATA "Data"

#define VOLUND_SERIAL_FILE_TYPE_MATERIAL "Material"
#define VOLUND_SERIAL_FILE_TYPE_SCENE "Scene"

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

	using Vec3 = glm::vec<3, float>;
	using DVec3 = glm::vec<3, double>;
	using IVec3 = glm::vec<3, int32_t>;
	using I64Vec3 = glm::vec<3, int64_t>;
	using RGB = Vec3;
	using Vec4 = glm::vec<4, float>;
	using DVec4 = glm::vec<4, double>;
	using IVec4 = glm::vec<4, int32_t>;
	using I64Vec4 = glm::vec<4, int64_t>;
	using RGBA = Vec4;
	using Mat3x3 = glm::mat<3, 3, float>;
	using DMat3x3 = glm::mat<3, 3, double>;
	using IMat3x3 = glm::mat<3, 3, int32_t>;
	using I64Mat3x3 = glm::mat<3, 3, int64_t>;
	using Mat4x4 = glm::mat<4, 4, float>;
	using DMat4x4 = glm::mat<4, 4, double>;
	using IMat4x4 = glm::mat<4, 4, int32_t>;
	using I64Mat4x4 = glm::mat<4, 4, int64_t>;
	using Quat = glm::qua<float>;
	using DQuat = glm::qua<double>;
}

namespace fs = std::filesystem;

namespace VL = Volund;
