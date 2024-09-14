#pragma once

#include "Matrix.h"

#include "Math/Vector/Vector4.h"

#include <array>

namespace Volund
{
    struct Mat4x4
    {
    public:

        Vec4& operator[](uint8_t index);
        const Vec4& operator[](uint8_t index) const;

        Mat4x4 operator+(const Mat4x4& matrix) const;
        Mat4x4 operator+(const float& scalar) const;

        Mat4x4 operator-(const Mat4x4& matrix) const;
        Mat4x4 operator-(const float& scalar) const;

        Mat4x4 operator*(const Mat4x4& matrix) const;
        Mat4x4 operator*(const float& scalar) const;

        Vec4 operator*(const Vec4& vector) const;
        Vector<3, float> operator*(const Vector<3, float>& vector) const;

        void operator+=(const Mat4x4& matrix);
        void operator+=(const float& scalar);

        void operator-=(const Mat4x4& matrix);
        void operator-=(const float& scalar);

        void operator*=(const Mat4x4& matrix);
        void operator*=(const float& scalar);

        //void operator/=(const Mat4x4& matrix);
        //void operator/=(const float& scalar);

        Mat4x4(const Vec4& vector1, const Vec4& vector2, const Vec4& vector3, const Vec4& vector4);
        Mat4x4(const std::array<float, 16> initList);
        Mat4x4(const Mat4x4& matrix);
        Mat4x4(const float& scalar);

        Mat4x4();

    private:

        std::array<Vec4, 4> m_Data;
    };
}
