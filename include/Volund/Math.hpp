#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4x4.hpp"
#include "Quaternion.hpp"

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

    template<typename T>
    bool Approximate(T x, T y)
    {
        return std::abs(x - y) < std::numeric_limits<T>::epsilon() * T(2);
    }

    template<VectorSize Size, typename T>
    Vector<Size, T> Normalize(const Vector<Size, T>& vector)
    {
        return vector / vector.Length();
    }

    template<VectorSize Size, typename T>
    T Dot(const Vector<Size, T>& a, const Vector<Size, T>& b)
    {
        T product = T(0);
        for (int i = 0; i < Size; i++)
        {
            product += a[i] * b[i];
        }
        return product;
    }

    Vec3 VOLUND_API Cross(const Vec3& a, const Vec3& b);

    Mat4x4 VOLUND_API Translate(Mat4x4 const& matrix, Vec3 const& vector);

    Mat4x4 VOLUND_API Scale(Mat4x4 const& matrix, Vec3 const& vector);

    Quat VOLUND_API LookAt(const Vec3& front, const Vec3& up);

    Mat4x4 VOLUND_API ViewMatrix(Vec3 const& from, Vec3 const& to, Vec3 const& up);

    Mat4x4 VOLUND_API ProjectionMatrix(float fovRadians, float aspectRatio, float near, float far);

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
