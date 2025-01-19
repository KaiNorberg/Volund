#include "Math.h"

#include <numeric>
#include <cmath>

namespace Volund::Math
{
	Quat LookAt(const Vec3& front, const Vec3& up)
	{
		return Quat(1.0);
	}

	Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		return Vec3(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y);
	}

	Mat4x4 Translate(Mat4x4 const& matrix, Vec3 const& vector)
	{
		Mat4x4 result(matrix);
		result[3] = matrix[0] * vector[0] + matrix[1] * vector[1] + matrix[2] * vector[2] + matrix[3];
		return result;
	}

	Mat4x4 scale(Mat4x4 const& matrix, Vec3 const& vector)
	{
		Mat4x4 result;
		result[0] = matrix[0] * vector[0];
		result[1] = matrix[1] * vector[1];
		result[2] = matrix[2] * vector[2];
		result[3] = matrix[3];
		return result;
	}

	Mat4x4 ViewMatrix(Vec3 const& from, Vec3 const& to, Vec3 const& up)
	{
		Vec3 const f(Normalize(to - from));
		Vec3 const s(Normalize(Cross(f, up)));
		Vec3 const u(Cross(s, f));

		Mat4x4 result(1.0f);
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

	Mat4x4 ProjectionMatrix(float fovRadians, float aspectRatio, float near, float far)
	{
		if (abs(aspectRatio - std::numeric_limits<float>::epsilon()) > static_cast<float>(0)) // Change to fabs
		{
			float const tanHalfFov = tan(fovRadians / static_cast<float>(2));

			Mat4x4 result(0.0f);
			result[0][0] = 1.0f / (aspectRatio * tanHalfFov);
			result[1][1] = 1.0f / (tanHalfFov);
			result[2][2] = -(far + near) / (far - near);
			result[2][3] = -1.0f;
			result[3][2] = -(2.0f * far * near) / (far - near);
			return result;
		}
		else
		{
			VOLUND_WARNING("Attempted to create a projection matrix using a aspect ratio of 0!");
			return Mat4x4();
		}
	}
}
