#pragma once

#include "../Vector.h"

namespace Volund
{	
	template<typename T>
	class Vector<2, T>
	{
	public:

		union { T x, r, s; };
		union { T y, g, t; };

		static VectorSize GetSize();

		T Length() const;
		T Length2() const;

		T& operator[](uint8_t index);
		const T& operator[](uint8_t index) const;

		Vector<2, T> operator+(const Vector<2, T>& other) const;
		Vector<2, T> operator+(const T& other) const;

		Vector<2, T> operator-(const Vector<2, T>& other) const;
		Vector<2, T> operator-(const T& other) const;

		Vector<2, T> operator*(const Vector<2, T>& other) const;
		Vector<2, T> operator*(const T& other) const;

		Vector<2, T> operator/(const Vector<2, T>& other) const;
		Vector<2, T> operator/(const T& other) const;

		void operator+=(const Vector<2, T>& other);
		void operator+=(const T& other);

		void operator-=(const Vector<2, T>& other);
		void operator-=(const T& other);

		void operator*=(const Vector<2, T>& other);
		void operator*=(const T& other);

		void operator/=(const Vector<2, T>& other);
		void operator/=(const T& other);

		void operator=(const Vector<2, T>& other);
		void operator=(const T& other);

		template<typename U>
		explicit operator Vector<2, U>() const;

		Vector() = default;

		Vector(const Vector<2, T>& vector);
		Vector(T x, T y);
		Vector(T scalar);
	};

	template<typename T>
	inline T Vector<2, T>::Length() const
	{
		return sqrt(this->Length2());
	}

	template<typename T>
	inline T Vector<2, T>::Length2() const
	{
		return (this->x * this->x) + (this->y * this->y);
	}

	template<typename T>
	inline VectorSize Vector<2, T>::GetSize()
	{
		return 2;
	}

	template<typename T>
	inline T& Vector<2, T>::operator[](uint8_t index)
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
		default:
		{
			VOLUND_ERROR("Inavlid Vector Index");
			return x;
		}
		break;
		}
	}

	template<typename T>
	inline const T& Vector<2, T>::operator[](uint8_t index) const
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
		default:
		{
			VOLUND_ERROR("Inavlid Vector Index");
			return x;
		}
		break;
		}
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator+(const Vector<2, T>& other) const
	{
		return Vector<2, T>(this->x + other.x, this->y + other.y);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator+(const T& other) const
	{
		return Vector<2, T>(this->x + other, this->y + other);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator-(const Vector<2, T>& other) const
	{
		return Vector<2, T>(this->x - other.x, this->y - other.y);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator-(const T& other) const
	{
		return Vector<2, T>(this->x - other, this->y - other);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator*(const Vector<2, T>& other) const
	{
		return Vector<2, T>(this->x * other.x, this->y * other.y);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator*(const T& other) const
	{
		return Vector<2, T>(this->x * other, this->y * other);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator/(const Vector<2, T>& other) const
	{
		return Vector<2, T>(this->x / other.x, this->y / other.y);
	}

	template<typename T>
	inline Vector<2, T> Vector<2, T>::operator/(const T& other) const
	{
		return Vector<2, T>(this->x / other, this->y / other);
	}

	template<typename T>
	inline void Vector<2, T>::operator+=(const Vector<2, T>& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	template<typename T>
	inline void Vector<2, T>::operator+=(const T& other)
	{
		this->x += other;
		this->y += other;
	}

	template<typename T>
	inline void Vector<2, T>::operator-=(const Vector<2, T>& other)
	{
		this->x -= other.x;
		this->y -= other.y;
	}

	template<typename T>
	inline void Vector<2, T>::operator-=(const T& other)
	{
		this->x -= other;
		this->y	-= other;
	}

	template<typename T>
	inline void Vector<2, T>::operator*=(const Vector<2, T>& other)
	{
		this->x *= other.x;
		this->y *= other.y;
	}

	template<typename T>
	inline void Vector<2, T>::operator*=(const T& other)
	{
		this->x *= other;
		this->y *= other;
	}

	template<typename T>
	inline void Vector<2, T>::operator/=(const Vector<2, T>& other)
	{
		this->x /= other.x;
		this->y /= other.y;
	}

	template<typename T>
	inline void Vector<2, T>::operator/=(const T& other)
	{
		this->x /= other;
		this->y /= other;
	}

	template<typename T>
	inline void Vector<2, T>::operator=(const Vector<2, T>& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	template<typename T>
	inline void Vector<2, T>::operator=(const T& other)
	{
		this->x = other;
		this->y = other;
	}

	template<typename T>
	template<typename U>
	inline Vector<2, T>::operator Vector<2, U>() const
	{
		return Vector<2, U>((U)this->x, (U)this->y);
	}

	template<typename T>
	inline Vector<2, T>::Vector(const Vector<2, T>& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}

	template<typename T>
	inline Vector<2, T>::Vector(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template<typename T>
	inline Vector<2, T>::Vector(T scalar)
	{
		this->x = scalar;
		this->y = scalar;
	}

	using Vec2 = Vector<2, float>;
	using DVec2 = Vector<2, double>;
	using IVec2 = Vector<2, int32_t>;
	using I64Vec2 = Vector<2, int64_t>;
}