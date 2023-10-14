#pragma once

#include "../CommonVec.h"

namespace Volund
{	
	template<typename T>
	class Vec<2, T>
	{
	public:

		T x;
		T y;

		typedef glm::vec<2, T> GLMType;

		static VecSize GetSize();

		T Length() const;
		T Length2() const;

		GLMType GLM() const;

		Vec<2, T> operator+(const Vec<2, T>& other);
		Vec<2, T> operator+(const T& other);

		Vec<2, T> operator-(const Vec<2, T>& other);
		Vec<2, T> operator-(const T& other);

		Vec<2, T> operator*(const Vec<2, T>& other);
		Vec<2, T> operator*(const T& other);

		Vec<2, T> operator/(const Vec<2, T>& other);
		Vec<2, T> operator/(const T& other);

		void operator+=(const Vec<2, T>& other);
		void operator+=(const T& other);

		void operator-=(const Vec<2, T>& other);
		void operator-=(const T& other);

		void operator*=(const Vec<2, T>& other);
		void operator*=(const T& other);

		void operator/=(const Vec<2, T>& other);
		void operator/=(const T& other);

		void operator=(const Vec<2, T>& other);
		void operator=(const T& other);

		template<typename U>
		explicit operator Vec<2, U>();

		Vec() = default;

		Vec(const Vec<2, T>& vector);
		Vec(const GLMType& vector);
		Vec(T x, T y);
		Vec(T scalar);

	protected:

		float m_Data[2];
	};

	template<typename T>
	inline T Vec<2, T>::Length() const
	{
		return sqrt(this->Length2());
	}

	template<typename T>
	inline T Vec<2, T>::Length2() const
	{
		return (this->x * this->x) + (this->y * this->y);
	}

	template<typename T>
	inline VecSize Vec<2, T>::GetSize()
	{
		return 2;
	}

	template<typename T>
	inline Vec<2, T>::GLMType Vec<2, T>::GLM() const
	{
		return glm::vec<2, T>(this->x, this->y);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator+(const Vec<2, T>& other)
	{
		return Vec<2, T>(this->x + other.x, this->y + other.y);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator+(const T& other)
	{
		return Vec<2, T>(this->x + other, this->y + other);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator-(const Vec<2, T>& other)
	{
		return Vec<2, T>(this->x - other.x, this->y - other.y);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator-(const T& other)
	{
		return Vec<2, T>(this->x - other, this->y - other);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator*(const Vec<2, T>& other)
	{
		return Vec<2, T>(this->x * other.x, this->y * other.y);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator*(const T& other)
	{
		return Vec<2, T>(this->x * other, this->y * other);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator/(const Vec<2, T>& other)
	{
		return Vec<2, T>(this->x / other.x, this->y / other.y);
	}

	template<typename T>
	inline Vec<2, T> Vec<2, T>::operator/(const T& other)
	{
		return Vec<2, T>(this->x / other, this->y / other);
	}

	template<typename T>
	inline void Vec<2, T>::operator+=(const Vec<2, T>& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	template<typename T>
	inline void Vec<2, T>::operator+=(const T& other)
	{
		this->x += other;
		this->y += other;
	}

	template<typename T>
	inline void Vec<2, T>::operator-=(const Vec<2, T>& other)
	{
		this->x -= other.x;
		this->y -= other.y;
	}

	template<typename T>
	inline void Vec<2, T>::operator-=(const T& other)
	{
		this->x -= other;
		this->y	-= other;
	}

	template<typename T>
	inline void Vec<2, T>::operator*=(const Vec<2, T>& other)
	{
		this->x *= other.x;
		this->y *= other.y;
	}

	template<typename T>
	inline void Vec<2, T>::operator*=(const T& other)
	{
		this->x *= other;
		this->y *= other;
	}

	template<typename T>
	inline void Vec<2, T>::operator/=(const Vec<2, T>& other)
	{
		this->x /= other.x;
		this->y /= other.y;
	}

	template<typename T>
	inline void Vec<2, T>::operator/=(const T& other)
	{
		this->x /= other;
		this->y /= other;
	}

	template<typename T>
	inline void Vec<2, T>::operator=(const Vec<2, T>& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	template<typename T>
	inline void Vec<2, T>::operator=(const T& other)
	{
		this->x = other;
		this->y = other;
	}

	template<typename T>
	template<typename U>
	inline Vec<2, T>::operator Vec<2, U>()
	{
		return Vec<2, U>((U)this->x, (U)this->y);
	}

	template<typename T>
	inline Vec<2, T>::Vec(const Vec<2, T>& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}

	template<typename T>
	inline Vec<2, T>::Vec(const GLMType& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}

	template<typename T>
	inline Vec<2, T>::Vec(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template<typename T>
	inline Vec<2, T>::Vec(T scalar)
	{
		this->x = scalar;
		this->y = scalar;
	}

	using Vec2 = Vec<2, float>;
	using DVec2 = Vec<2, double>;
	using IVec2 = Vec<2, int32_t>;
	using I64Vec2 = Vec<2, int64_t>;
}