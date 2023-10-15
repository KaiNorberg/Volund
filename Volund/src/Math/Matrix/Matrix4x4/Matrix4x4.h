#pragma once

#include "../Matrix.h"

#include "Math/Vector/Vector4/Vector4.h"

namespace Volund
{
	template<typename T>
	class Matrix<4, 4, T>
	{
	public:

		MatrixWidth GetWidth();
		MatrixHeight GetHeight();

		Vector<4, T>& operator[](uint8_t index);
		const Vector<4, T>& operator[](uint8_t index) const;

		Matrix<4, 4, T> operator+(const Matrix<4, 4, T>& matrix) const;
		Matrix<4, 4, T> operator+(const T& scalar) const;

		Matrix<4, 4, T> operator-(const Matrix<4, 4, T>& matrix) const;
		Matrix<4, 4, T> operator-(const T& scalar) const;

		Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& matrix) const;
		Matrix<4, 4, T> operator*(const T& scalar) const;
		
		Vector<4, T> operator*(const Vector<4, T>& vector) const;
		Vector<3, T> operator*(const Vector<3, T>& vector) const;

		void operator+=(const Matrix<4, 4, T>& matrix);
		void operator+=(const T& scalar);

		void operator-=(const Matrix<4, 4, T>& matrix);
		void operator-=(const T& scalar);

		void operator*=(const Matrix<4, 4, T>& matrix);
		void operator*=(const T& scalar);

		//void operator/=(const Matrix<4, 4, T>& matrix);
		//void operator/=(const T& scalar);

		Matrix(const Vector<4, T>& vector1, const Vector<4, T>& vector2, const Vector<4, T>& vector3, const Vector<4, T>& vector4);
		Matrix(const Matrix<4, 4, T>& matrix);
		Matrix(const T& scalar);

		Matrix();

	private:

		std::array<Vector<4, T>, 4> m_Data;
	};

	template<typename T>
	inline MatrixWidth Matrix<4, 4, T>::GetWidth()
	{
		return 4;
	}
	template<typename T>
	inline MatrixHeight Matrix<4, 4, T>::GetHeight()
	{
		return 4;
	}

	template<typename T>
	inline Vector<4, T>& Matrix<4, 4, T>::operator[](uint8_t index)
	{
		return this->m_Data[index];
	}

	template<typename T>
	inline const Vector<4, T>& Matrix<4, 4, T>::operator[](uint8_t index) const
	{
		return this->m_Data[index];
	}

	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::operator+(const Matrix<4, 4, T>& matrix) const
	{
		return Matrix<4, 4, T>(
			(*this)[0] + matrix[0], 
			(*this)[1] + matrix[1], 
			(*this)[2] + matrix[2], 
			(*this)[3] + matrix[3]);
	}

	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::operator+(const T& scalar) const
	{
		return Matrix<4, 4, T>(
			(*this)[0] + scalar,
			(*this)[1] + scalar,
			(*this)[2] + scalar,
			(*this)[3] + scalar);
	}

	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::operator-(const Matrix<4, 4, T>& matrix) const
	{
		return Matrix<4, 4, T>(
			(*this)[0] - matrix[0],
			(*this)[1] - matrix[1],
			(*this)[2] - matrix[2],
			(*this)[3] - matrix[3]);
	}

	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::operator-(const T& scalar) const
	{
		return Matrix<4, 4, T>(
			(*this)[0] - scalar,
			(*this)[1] - scalar,
			(*this)[2] - scalar,
			(*this)[3] - scalar);
	}

	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::operator*(const Matrix<4, 4, T>& matrix) const
	{
		Matrix<4, 4, T> result;
		result[0] = (*this)[0] * matrix[0][0] + (*this)[1] * matrix[0][1] + (*this)[2] * matrix[0][2] + (*this)[3] * matrix[0][3];
		result[1] = (*this)[0] * matrix[1][0] + (*this)[1] * matrix[1][1] + (*this)[2] * matrix[1][2] + (*this)[3] * matrix[1][3];
		result[2] = (*this)[0] * matrix[2][0] + (*this)[1] * matrix[2][1] + (*this)[2] * matrix[2][2] + (*this)[3] * matrix[2][3];
		result[3] = (*this)[0] * matrix[3][0] + (*this)[1] * matrix[3][1] + (*this)[2] * matrix[3][2] + (*this)[3] * matrix[3][3];
		return result;
	}

	template<typename T>
	inline Matrix<4, 4, T> Matrix<4, 4, T>::operator*(const T& scalar) const
	{
		return Matrix<4, 4, T>(
			(*this)[0] * scalar,
			(*this)[1] * scalar,
			(*this)[2] * scalar,
			(*this)[3] * scalar);
	}

	template<typename T>
	inline Vector<4, T> Matrix<4, 4, T>::operator*(const Vector<4, T>& vector) const
	{
		const Vector<4, T> mov0(vector[0]);
		const Vector<4, T> mov1(vector[1]);
		const Vector<4, T> mul0 = (*this)[0] * mov0;
		const Vector<4, T> mul1 = (*this)[1] * mov1;
		const Vector<4, T> add0 = mul0 + mul1;
		const Vector<4, T> mov2(vector[2]);
		const Vector<4, T> mov3(vector[3]);
		const Vector<4, T> mul2 = (*this)[2] * mov2;
		const Vector<4, T> mul3 = (*this)[3] * mov3;
		const Vector<4, T> add1 = mul2 + mul3;
		const Vector<4, T> add2 = add0 + add1;
		return add2;
	}

	template<typename T>
	inline Vector<3, T> Matrix<4, 4, T>::operator*(const Vector<3, T>& vector) const
	{
		Vector<4, T> result = (*this) * Vector<4, T>(vector.x, vector.y, vector.z, 1.0f);
		return Vector<3, T>(result.x, result.y, result.z);
	}

	template<typename T>
	inline void Matrix<4, 4, T>::operator+=(const Matrix<4, 4, T>& matrix)
	{
		this->m_Data[0] += matrix[0];
		this->m_Data[1] += matrix[1];
		this->m_Data[2] += matrix[2];
		this->m_Data[3] += matrix[3];
	}

	template<typename T>
	inline void Matrix<4, 4, T>::operator+=(const T& scalar)
	{
		this->m_Data[0] += scalar;
		this->m_Data[1] += scalar;
		this->m_Data[2] += scalar;
		this->m_Data[3] += scalar;
	}

	template<typename T>
	inline void Matrix<4, 4, T>::operator-=(const Matrix<4, 4, T>& matrix)
	{
		this->m_Data[0] -= matrix[0];
		this->m_Data[1] -= matrix[1];
		this->m_Data[2] -= matrix[2];
		this->m_Data[3] -= matrix[3];
	}

	template<typename T>
	inline void Matrix<4, 4, T>::operator-=(const T& scalar)
	{
		this->m_Data[0] -= scalar;
		this->m_Data[1] -= scalar;
		this->m_Data[2] -= scalar;
		this->m_Data[3] -= scalar;
	}

	template<typename T>
	inline void Matrix<4, 4, T>::operator*=(const Matrix<4, 4, T>& matrix)
	{
		Matrix<4, 4, T> result;
		result[0] = (*this)[0] * matrix[0][0] + (*this)[1] * matrix[0][1] + (*this)[2] * matrix[0][2] + (*this)[3] * matrix[0][3];
		result[1] = (*this)[0] * matrix[1][0] + (*this)[1] * matrix[1][1] + (*this)[2] * matrix[1][2] + (*this)[3] * matrix[1][3];
		result[2] = (*this)[0] * matrix[2][0] + (*this)[1] * matrix[2][1] + (*this)[2] * matrix[2][2] + (*this)[3] * matrix[2][3];
		result[3] = (*this)[0] * matrix[3][0] + (*this)[1] * matrix[3][1] + (*this)[2] * matrix[3][2] + (*this)[3] * matrix[3][3];
		return result;
	}

	template<typename T>
	inline void Matrix<4, 4, T>::operator*=(const T& scalar)
	{
		this->m_Data[0] *= scalar;
		this->m_Data[1] *= scalar;
		this->m_Data[2] *= scalar;
		this->m_Data[3] *= scalar;
	}

	template<typename T>
	inline Matrix<4, 4, T>::Matrix(const Vector<4, T>& vector1, const Vector<4, T>& vector2, const Vector<4, T>& vector3, const Vector<4, T>& vector4)
	{
		this->m_Data[0] = vector1;
		this->m_Data[1] = vector2;
		this->m_Data[2] = vector3;
		this->m_Data[3] = vector4;
	}

	template<typename T>
	inline Matrix<4, 4, T>::Matrix(const Matrix<4, 4, T>& matrix)
	{
		this->m_Data = matrix.m_Data;
	}

	template<typename T>
	inline Matrix<4, 4, T>::Matrix(const T& scalar)
	{
		this->m_Data[0] = Vector<4, T>(scalar, 0, 0, 0);
		this->m_Data[1] = Vector<4, T>(0, scalar, 0, 0);
		this->m_Data[2] = Vector<4, T>(0, 0, scalar, 0);
		this->m_Data[3] = Vector<4, T>(0, 0, 0, scalar);
	}

	template<typename T>
	inline Matrix<4, 4, T>::Matrix()
	{
		this->m_Data[0] = Vector<4, T>(1, 0, 0, 0);
		this->m_Data[1] = Vector<4, T>(0, 1, 0, 0);
		this->m_Data[2] = Vector<4, T>(0, 0, 1, 0);
		this->m_Data[3] = Vector<4, T>(0, 0, 0, 1);
	}

	using Mat4x4 = Matrix<4, 4, float>;
	using DMat4x4 = Matrix<4, 4, double>;
	using IMat4x4 = Matrix<4, 4, int32_t>;
	using I64Mat4x4 = Matrix<4, 4, int64_t>;
}