#pragma once

#include "Math/Vec/Vec.h"

namespace Volund
{
	using UniformInt = int;
	using UniformFloat = float;
	using UniformDouble = double;
	using UniformVec2 = Vec2;
	using UniformVec3 = Vec3;
	using UniformVec4 = Vec4;
	using UniformMat3x3 = Mat3x3;
	using UniformMat4x4 = Mat4x4;
	using UniformTexture = Ref<Texture>;
	using UniformFramebuffer = Ref<Framebuffer>;
}

#define VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY typename = std::enable_if_t<std::is_same<T, UniformInt>::value || std::is_same<T, UniformFloat>::value || \
std::is_same<T, UniformDouble>::value || std::is_same<T, UniformVec2>::value || \
std::is_same<T, UniformVec3>::value || std::is_same<T, UniformVec4>::value || \
std::is_same<T, UniformMat3x3>::value || std::is_same<T, UniformMat4x4>::value || \
std::is_same<T, UniformTexture>::value || std::is_same<T, UniformFramebuffer>::value>