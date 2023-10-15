#pragma once

#include "../Vector.h"

#include "../Vector3/Vector3.h"

namespace Volund
{	
	template<typename T>
	class Vector<4, T>
	{
	public:

		union { T x, r, s; };
		union { T y, g, t; };
		union { T z, b, p; };
		union { T w, a, q; };

		typedef glm::vec<4, T> GLMType;

		static VectorSize GetSize();

		T Length() const;
		T Length2() const;

		GLMType GLM() const;

		T& operator[](uint8_t index);
		const T& operator[](uint8_t index) const;

		Vector<4, T> operator+(const Vector<4, T>& other) const;
		Vector<4, T> operator+(const T& other) const;

		Vector<4, T> operator-(const Vector<4, T>& other) const;
		Vector<4, T> operator-(const T& other) const;

		Vector<4, T> operator*(const Vector<4, T>& other) const;
		Vector<4, T> operator*(const T& other) const;

		Vector<4, T> operator/(const Vector<4, T>& other) const;
		Vector<4, T> operator/(const T& other) const;

		void operator+=(const Vector<4, T>& other);
		void operator+=(const T& other);

		void operator-=(const Vector<4, T>& other);
		void operator-=(const T& other);

		void operator*=(const Vector<4, T>& other);
		void operator*=(const T& other);

		void operator/=(const Vector<4, T>& other);
		void operator/=(const T& other);

		void operator=(const Vector<4, T>& other);
		void operator=(const T& other);

		template<typename U>
		explicit operator Vector<4, U>() const;

		Vector() = default;

		Vector(const Vector<4, T>& vector);
		Vector(const GLMType& vector);
		Vector(T x, T y, T z, T w);
		Vector(T scalar);
	};

	template<typename T>
	inline T Vector<4, T>::Length() const
	{
		return sqrt(this->Length2());
	}

	template<typename T>
	inline T Vector<4, T>::Length2() const
	{
		return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
	}

	template<typename T>
	inline VectorSize Vector<4, T>::GetSize()
	{
		return 4;
	}

	template<typename T>
	inline Vector<4, T>::GLMType Vector<4, T>::GLM() const
	{
		return glm::vec<4, T>(this->x, this->y, this->z, this->w);
	}

	template<typename T>
	inline T& Vector<4, T>::operator[](uint8_t index)
	{
		switch (index)
		{
		case 0:
		{
			return x;
		}
		break;
		case 1:
		{
			return y;
		}
		break;
		case 2:
		{
			return z;
		}
		break;
		case 3:
		{
			return w;
		}
		break;
		default:
		{
			VOLUND_ERROR("Inavlid Vector Index");
			return x;
		}
		break;
		}
	}

	template<typename T>
	inline const T& Vector<4, T>::operator[](uint8_t index) const
	{
		switch (index)
		{
		case 0:
		{
			return x;
		}
		break;
		case 1:
		{
			return y;
		}
		break;
		case 2:
		{
			return z;
		}
		break;
		case 3:
		{
			return w;
		}
		break;
		default:
		{
			VOLUND_ERROR("Inavlid Vector Index");
			return x;
		}
		break;
		}
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator+(const Vector<4, T>& other) const
	{
		return Vector<4, T>(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator+(const T& other) const
	{
		return Vector<4, T>(this->x + other, this->y + other, this->z + other, this->w + other);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator-(const Vector<4, T>& other) const
	{
		return Vector<4, T>(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator-(const T& other) const
	{
		return Vector<4, T>(this->x - other, this->y - other, this->z - other, this->w - other);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator*(const Vector<4, T>& other) const
	{
		return Vector<4, T>(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator*(const T& other) const
	{
		return Vector<4, T>(this->x * other, this->y * other, this->z * other, this->w * other);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator/(const Vector<4, T>& other) const
	{
		return Vector<4, T>(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
	}

	template<typename T>
	inline Vector<4, T> Vector<4, T>::operator/(const T& other) const
	{
		return Vector<4, T>(this->x / other, this->y / other, this->z / other, this->w / other);
	}

	template<typename T>
	inline void Vector<4, T>::operator+=(const Vector<4, T>& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;
	}

	template<typename T>
	inline void Vector<4, T>::operator+=(const T& other)
	{
		this->x += other;
		this->y += other;
		this->z += other;
		this->w += other;
	}

	template<typename T>
	inline void Vector<4, T>::operator-=(const Vector<4, T>& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;
	}

	template<typename T>
	inline void Vector<4, T>::operator-=(const T& other)
	{
		this->x -= other;
		this->y	-= other;
		this->z -= other;
		this->w -= other;
	}

	template<typename T>
	inline void Vector<4, T>::operator*=(const Vector<4, T>& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		this->w *= other.w;
	}

	template<typename T>
	inline void Vector<4, T>::operator*=(const T& other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
		this->w *= other;
	}

	template<typename T>
	inline void Vector<4, T>::operator/=(const Vector<4, T>& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		this->w /= other.w;
	}

	template<typename T>
	inline void Vector<4, T>::operator/=(const T& other)
	{
		this->x /= other;
		this->y /= other;
		this->z /= other;
		this->w /= other;
	}

	template<typename T>
	inline void Vector<4, T>::operator=(const Vector<4, T>& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	template<typename T>
	inline void Vector<4, T>::operator=(const T& other)
	{
		this->x = other;
		this->y = other;
		this->z = other;
		this->w = other;
	}

	template<typename T>
	template<typename U>
	inline Vector<4, T>::operator Vector<4, U>() const
	{
		return Vector<3, U>((U)this->x, (U)this->y, (U)this->z, (U)this->w);
	}

	template<typename T>
	inline Vector<4, T>::Vector(const Vector<4, T>& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
		this->w = vector.w;
	}

	template<typename T>
	inline Vector<4, T>::Vector(const GLMType& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
		this->w = vector.w;
	}

	template<typename T>
	inline Vector<4, T>::Vector(T x, T y, T z, T w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	template<typename T>
	inline Vector<4, T>::Vector(T scalar)
	{
		this->x = scalar;
		this->y = scalar;
		this->z = scalar;
		this->w = scalar;
	}

	using Vec4 = Vector<4, float>;
	using DVec4 = Vector<4, double>;
	using IVec4 = Vector<4, int32_t>;
	using I64Vec4 = Vector<4, int64_t>;
	using RGBA = Vec4;
}