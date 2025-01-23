#include "Matrix4x4.hpp"

#include "Lua/LuaAPI.hpp"

namespace Volund
{
	Vec4& Mat4x4::operator[](uint8_t index)
	{
		return this->m_data[index];
	}

	const Vec4& Mat4x4::operator[](uint8_t index) const
	{
		return this->m_data[index];
	}

	Mat4x4 Mat4x4::operator+(const Mat4x4& matrix) const
	{
		return Mat4x4(
			(*this)[0] + matrix[0],
			(*this)[1] + matrix[1],
			(*this)[2] + matrix[2],
			(*this)[3] + matrix[3]);
	}

	Mat4x4 Mat4x4::operator+(const float& scalar) const
	{
		return Mat4x4(
			(*this)[0] + scalar,
			(*this)[1] + scalar,
			(*this)[2] + scalar,
			(*this)[3] + scalar);
	}

	Mat4x4 Mat4x4::operator-(const Mat4x4& matrix) const
	{
		return Mat4x4(
			(*this)[0] - matrix[0],
			(*this)[1] - matrix[1],
			(*this)[2] - matrix[2],
			(*this)[3] - matrix[3]);
	}

	Mat4x4 Mat4x4::operator-(const float& scalar) const
	{
		return Mat4x4(
			(*this)[0] - scalar,
			(*this)[1] - scalar,
			(*this)[2] - scalar,
			(*this)[3] - scalar);
	}

	Mat4x4 Mat4x4::operator*(const Mat4x4& matrix) const
	{
		Vec4 const SrcA0 = (*this)[0];
		Vec4 const SrcA1 = (*this)[1];
		Vec4 const SrcA2 = (*this)[2];
		Vec4 const SrcA3 = (*this)[3];

		Vec4 const SrcB0 = matrix[0];
		Vec4 const SrcB1 = matrix[1];
		Vec4 const SrcB2 = matrix[2];
		Vec4 const SrcB3 = matrix[3];

		Mat4x4 Result;
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
	}

	Mat4x4 Mat4x4::operator*(const float& scalar) const
	{
		return Mat4x4(
			(*this)[0] * scalar,
			(*this)[1] * scalar,
			(*this)[2] * scalar,
			(*this)[3] * scalar);
	}

	Vec4 Mat4x4::operator*(const Vec4& vector) const
	{
		const Vec4 mov0(vector[0]);
		const Vec4 mov1(vector[1]);
		const Vec4 mul0 = (*this)[0] * mov0;
		const Vec4 mul1 = (*this)[1] * mov1;
		const Vec4 add0 = mul0 + mul1;
		const Vec4 mov2(vector[2]);
		const Vec4 mov3(vector[3]);
		const Vec4 mul2 = (*this)[2] * mov2;
		const Vec4 mul3 = (*this)[3] * mov3;
		const Vec4 add1 = mul2 + mul3;
		const Vec4 add2 = add0 + add1;
		return add2;
	}

	Vector<3, float> Mat4x4::operator*(const Vector<3, float>& vector) const
	{
		Vec4 result = (*this) * Vec4(vector.x, vector.y, vector.z, 1.0f);
		return Vector<3, float>(result.x, result.y, result.z);
	}

	void Mat4x4::operator+=(const Mat4x4& matrix)
	{
		this->m_data[0] += matrix[0];
		this->m_data[1] += matrix[1];
		this->m_data[2] += matrix[2];
		this->m_data[3] += matrix[3];
	}

	void Mat4x4::operator+=(const float& scalar)
	{
		this->m_data[0] += scalar;
		this->m_data[1] += scalar;
		this->m_data[2] += scalar;
		this->m_data[3] += scalar;
	}

	void Mat4x4::operator-=(const Mat4x4& matrix)
	{
		this->m_data[0] -= matrix[0];
		this->m_data[1] -= matrix[1];
		this->m_data[2] -= matrix[2];
		this->m_data[3] -= matrix[3];
	}

	void Mat4x4::operator-=(const float& scalar)
	{
		this->m_data[0] -= scalar;
		this->m_data[1] -= scalar;
		this->m_data[2] -= scalar;
		this->m_data[3] -= scalar;
	}

	void Mat4x4::operator*=(const Mat4x4& matrix)
	{
		*this = *this * matrix;
	}


	void Mat4x4::operator*=(const float& scalar)
	{
		this->m_data[0] *= scalar;
		this->m_data[1] *= scalar;
		this->m_data[2] *= scalar;
		this->m_data[3] *= scalar;
	}

	Mat4x4::Mat4x4(const Vec4& vector1, const Vec4& vector2, const Vec4& vector3, const Vec4& vector4)
	{
		this->m_data[0] = vector1;
		this->m_data[1] = vector2;
		this->m_data[2] = vector3;
		this->m_data[3] = vector4;
	}

	Mat4x4::Mat4x4(const std::array<float, 16> initList)
	{
		this->m_data[0] = Vec4(initList[0], initList[1], initList[2], initList[3]);
		this->m_data[1] = Vec4(initList[4], initList[5], initList[6], initList[7]);
		this->m_data[2] = Vec4(initList[8], initList[9], initList[10], initList[11]);
		this->m_data[3] = Vec4(initList[12], initList[13], initList[14], initList[15]);
	}

	Mat4x4::Mat4x4(const Mat4x4& matrix)
	{
		this->m_data = matrix.m_data;
	}

	Mat4x4::Mat4x4(const float& scalar)
	{
		this->m_data[0] = Vec4(scalar, 0, 0, 0);
		this->m_data[1] = Vec4(0, scalar, 0, 0);
		this->m_data[2] = Vec4(0, 0, scalar, 0);
		this->m_data[3] = Vec4(0, 0, 0, scalar);
	}

	Mat4x4::Mat4x4()
	{
		this->m_data[0] = Vec4(1, 0, 0, 0);
		this->m_data[1] = Vec4(0, 1, 0, 0);
		this->m_data[2] = Vec4(0, 0, 1, 0);
		this->m_data[3] = Vec4(0, 0, 0, 1);
	}

	VOLUND_USERTYPE_REGISTER(Mat4x4,
    [](LuaState* state){
        state->NewUsertype<Mat4x4>("Mat4x4", 
            sol::constructors<
                Mat4x4(), 
                Mat4x4(float), 
                Mat4x4(const Vec4&, const Vec4&, const Vec4&, const Vec4&),
                Mat4x4(const std::array<float, 16>&)
            >(),
            "operator+", sol::overload(
                [](const Mat4x4& a, const Mat4x4& b) { return a + b; },
                [](const Mat4x4& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Mat4x4& a, const Mat4x4& b) { return a - b; },
                [](const Mat4x4& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Mat4x4& a, const Mat4x4& b) { return a * b; },
                [](const Mat4x4& a, float b) { return a * b; },
                [](const Mat4x4& a, const Vec4& v) { return a * v; },
                [](const Mat4x4& a, const Vec3& v) { return a * v; }
            ),
            "operator[]", [](Mat4x4& m, uint8_t index) { return m[index]; }
        );
    });
}
