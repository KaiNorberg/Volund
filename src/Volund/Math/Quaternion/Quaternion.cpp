#include "Quaternion.h"

#include "Math/Math.h"

namespace Volund
{
	Quat::operator Mat4x4() const
	{
		Mat4x4 result(1.0f);
		float qxx = (this->x * this->x);
		float qyy = (this->y * this->y);
		float qzz = (this->z * this->z);
		float qxz = (this->x * this->z);
		float qxy = (this->x * this->y);
		float qyz = (this->y * this->z);
		float qwx = (this->w * this->x);
		float qwy = (this->w * this->y);
		float qwz = (this->w * this->z);

		result[0][0] = float(1) - float(2) * (qyy + qzz);
		result[0][1] = float(2) * (qxy + qwz);
		result[0][2] = float(2) * (qxz - qwy);

		result[1][0] = float(2) * (qxy - qwz);
		result[1][1] = float(1) - float(2) * (qxx + qzz);
		result[1][2] = float(2) * (qyz + qwx);

		result[2][0] = float(2) * (qxz + qwy);
		result[2][1] = float(2) * (qyz - qwx);
		result[2][2] = float(1) - float(2) * (qxx + qyy);

		return result;
	}

	Vec3 Quat::operator*(const Vec3& point) const
	{
		Vec3 const qVec(this->x, this->y, this->z);
		Vec3 const uv(Math::Cross(qVec, point));
		Vec3 const uuv(Math::Cross(qVec, uv));

		return point + ((uv * this->w) + uuv) * static_cast<float>(2);
	}

	Quat Quat::operator*(const Quat& quaternion) const
	{
		Quat out;
		out.w = this->w * quaternion.w - this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z;
		out.x = this->w * quaternion.x + this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y;
		out.y = this->w * quaternion.y + this->y * quaternion.w + this->z * quaternion.x - this->x * quaternion.z;
		out.z = this->w * quaternion.z + this->z * quaternion.w + this->x * quaternion.y - this->y * quaternion.x;
		return out;
	}

	void Quat::operator*=(const Quat& quaternion)
	{
		Quat temp = (*this) * quaternion;

		this->w = temp.w;
		this->x = temp.x;
		this->y = temp.y;
		this->z = temp.z;
	}

	Vec3 Quat::EulerAngles() const
	{
		return Vec3(this->Pitch(), this->Yaw(), this->Roll());
	}

	float Quat::Pitch() const
	{
		float y = 2.0 * (this->y * this->z + this->w * this->x);
		float x = this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z;

		if (Math::Approximate(x, 0.0f) && Math::Approximate(y, 0.0f))
		{
			return 2.0 * atan2(this->x, this->w);
		}
		else
		{
			return atan2(y, x);
		}
	}

	float Quat::Yaw() const
	{
		return asin(std::clamp(-2.0f * (this->x * this->z - this->w * this->y), -1.0f, 1.0f));
	}

	float Quat::Roll() const
	{
		float y = 2.0f * (this->x * this->y + this->w * this->z);
		float x = this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z;

		if (Math::Approximate(x, 0.0f) && Math::Approximate(y, 0.0f))
		{
			return 0.0f;
		}
		else
		{
			return atan2(y, x);
		}
	}

	Quat::Quat(const Vec3& eulerAngles)
	{
		Vec3 halfAngles = eulerAngles / 2.0f;

		Vec3 c = Vec3(cos(halfAngles.x), cos(halfAngles.y), cos(halfAngles.z));
		Vec3 s = Vec3(sin(halfAngles.x), sin(halfAngles.y), sin(halfAngles.z));

		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
	}

	Quat::Quat(float w, float x, float y, float z)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}
}
