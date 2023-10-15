#pragma once

#include "Vector/Vector2/Vector2.h"
#include "Vector/Vector3/Vector3.h"
#include "Vector/Vector4/Vector4.h"
#include "Matrix/Matrix4x4/Matrix4x4.h"

#define PI 3.14159265359f

namespace Volund::Math
{
	static inline const Vec3 UP = Vec3(0.0f, 1.0f, 0.0f);
	static inline const Vec3 DOWN = Vec3(0.0f, -1.0f, 0.0f);
	static inline const Vec3 FORWARD = Vec3(0.0f, 0.0f, 1.0f);
	static inline const Vec3 BACK = Vec3(0.0f, 0.0f, -1.0f);
	static inline const Vec3 LEFT = Vec3(-1.0f, 0.0f, 0.0f);
	static inline const Vec3 RIGHT = Vec3(1.0f, 0.0f, 0.0f);
	static inline const Vec3 ONE = Vec3(1.0f, 1.0f, 1.0f);
	static inline const Vec3 ZERO = Vec3(0.0f, 0.0f, 0.0f);

	template<VectorSize Size, typename T>
	Vector<Size, T> Normalize(const Vector<Size, T>& vector)
	{
		return vector / vector.Length();
	}

	template<typename T>
	Vector<3, T> Cross(const Vector<3, T>& a, const Vector<3, T>& b)
	{
		return Vector<3, T>(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y);
	}

	template<VectorSize Size, typename T>
	T Dot(const Vector<Size, T>& a, const Vector<Size, T>& b)
	{
		T product;
		for (int i = 0; i < Size; i++)
		{
			product += a[i] * b[i];
		}
		return product;
	}

	template<typename T>
	Matrix<4, 4, T> Translate(Matrix<4, 4, T> const& matrix, Vector<3, T> const& vector)
	{
		Matrix<4, 4, T> result(matrix);
		result[3] = matrix[0] * vector[0] + matrix[1] * vector[1] + matrix[2] * vector[2] + matrix[3];
		return result;
	}

	template<typename T>
	Matrix<4, 4, T> Scale(Matrix<4, 4, T> const& matrix, Vector<3, T> const& vector)
	{
		Matrix<4, 4, T> result;
		result[0] = matrix[0] * vector[0];
		result[1] = matrix[1] * vector[1];
		result[2] = matrix[2] * vector[2];
		result[3] = matrix[3];
		return result;
	}

	template<typename T>
	Matrix<4, 4, T> ViewMatrix(Vector<3, T> const& from, Vector<3, T> const& to, Vector<3, T> const& up)
	{
		Vector<3, T> const f(Normalize(to - from));
		Vector<3, T> const s(Normalize(Cross(f, up)));
		Vector<3, T> const u(Cross(s, f));

		Matrix<4, 4, T> result(1);
		result[0][0] = s.x;
		result[1][0] = s.y;
		result[2][0] = s.z;
		result[0][1] = u.x;
		result[1][1] = u.y;
		result[2][1] = u.z;
		result[0][2] = -f.x;
		result[1][2] = -f.y;
		result[2][2] = -f.z;
		result[3][0] = -Dot(s, from);
		result[3][1] = -Dot(u, from);
		result[3][2] = Dot(f, from);
		return result;
	}

	template<typename T>
	Matrix<4, 4, T> ProjectionMatrix(T fovRadians, T aspectRatio, T near, T far)
	{
		if (abs(aspectRatio - std::numeric_limits<T>::epsilon()) > static_cast<T>(0))
		{
			T const tanHalfFov = tan(fovRadians / static_cast<T>(2));

			Matrix<4, 4, T> result(static_cast<T>(0));
			result[0][0] = static_cast<T>(1) / (aspectRatio * tanHalfFov);
			result[1][1] = static_cast<T>(1) / (tanHalfFov);
			result[2][2] = -(far + near) / (far - near);
			result[2][3] = -static_cast<T>(1);
			result[3][2] = -(static_cast<T>(2) * far * near) / (far - near);
			return result;
		}
		else
		{
			VOLUND_WARNING("Attempted to create a projection matrix using a aspect ratio of 0!");
			return Matrix<4, 4, T>();
		}
	}

	template<typename T>		
	T Radians(const T& degress)
	{
		return degress * (PI / 180.0f);
	}

	template<typename T>
	T Degress(const T& radians)
	{
		return radians * (180.0f / PI);
	}
}