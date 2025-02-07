#pragma once

#include "Vector.hpp"
#include "Logger.hpp"
#include "Core.hpp"

#include <cstdint>
#include <cmath>

namespace Volund
{
    template<typename T>
    class Vector<3, T>
    {
    public:

        union { T x, r, s; };
        union { T y, g, t; };
        union { T z, b, p; };

        static VectorSize GetSize();

        T Length() const;
        T Length2() const;

        T& operator[](uint8_t index);
        const T& operator[](uint8_t index) const;

        Vector<3, T> operator+(const Vector<3, T>& other) const;
        Vector<3, T> operator+(const T& other) const;

        Vector<3, T> operator-(const Vector<3, T>& other) const;
        Vector<3, T> operator-(const T& other) const;

        Vector<3, T> operator*(const Vector<3, T>& other) const;
        Vector<3, T> operator*(const T& other) const;

        Vector<3, T> operator/(const Vector<3, T>& other) const;
        Vector<3, T> operator/(const T& other) const;

        void operator+=(const Vector<3, T>& other);
        void operator+=(const T& other);

        void operator-=(const Vector<3, T>& other);
        void operator-=(const T& other);

        void operator*=(const Vector<3, T>& other);
        void operator*=(const T& other);

        void operator/=(const Vector<3, T>& other);
        void operator/=(const T& other);

        void operator=(const Vector<3, T>& other);
        void operator=(const T& other);

        template<typename U>
        explicit operator Vector<3, U>() const;

        Vector() = default;

        Vector(const Vector<3, T>& vector);
        Vector(T x, T y, T z);
        Vector(T scalar);
    };

    template<typename T>
    inline T Vector<3, T>::Length() const
    {
        return sqrt(this->Length2());
    }

    template<typename T>
    inline T Vector<3, T>::Length2() const
    {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    template<typename T>
    inline VectorSize Vector<3, T>::GetSize()
    {
        return 3;
    }

    template<typename T>
    inline T& Vector<3, T>::operator[](uint8_t index)
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
        default:
        {
            VOLUND_ERROR("Inavlid Vector Index");
            return x;
        }
        break;
        }
    }

    template<typename T>
    inline const T& Vector<3, T>::operator[](uint8_t index) const
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
        default:
        {
            VOLUND_ERROR("Inavlid Vector Index");
            return x;
        }
        break;
        }
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator+(const Vector<3, T>& other) const
    {
        return Vector<3, T>(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator+(const T& other) const
    {
        return Vector<3, T>(this->x + other, this->y + other, this->z + other);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator-(const Vector<3, T>& other) const
    {
        return Vector<3, T>(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator-(const T& other) const
    {
        return Vector<3, T>(this->x - other, this->y - other, this->z - other);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator*(const Vector<3, T>& other) const
    {
        return Vector<3, T>(this->x * other.x, this->y * other.y, this->z * other.z);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator*(const T& other) const
    {
        return Vector<3, T>(this->x * other, this->y * other, this->z * other);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator/(const Vector<3, T>& other) const
    {
        return Vector<3, T>(this->x / other.x, this->y / other.y, this->z / other.z);
    }

    template<typename T>
    inline Vector<3, T> Vector<3, T>::operator/(const T& other) const
    {
        return Vector<3, T>(this->x / other, this->y / other, this->z / other);
    }

    template<typename T>
    inline void Vector<3, T>::operator+=(const Vector<3, T>& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }

    template<typename T>
    inline void Vector<3, T>::operator+=(const T& other)
    {
        this->x += other;
        this->y += other;
        this->z += other;
    }

    template<typename T>
    inline void Vector<3, T>::operator-=(const Vector<3, T>& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
    }

    template<typename T>
    inline void Vector<3, T>::operator-=(const T& other)
    {
        this->x -= other;
        this->y -= other;
        this->z -= other;
    }

    template<typename T>
    inline void Vector<3, T>::operator*=(const Vector<3, T>& other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
    }

    template<typename T>
    inline void Vector<3, T>::operator*=(const T& other)
    {
        this->x *= other;
        this->y *= other;
        this->z *= other;
    }

    template<typename T>
    inline void Vector<3, T>::operator/=(const Vector<3, T>& other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
    }

    template<typename T>
    inline void Vector<3, T>::operator/=(const T& other)
    {
        this->x /= other;
        this->y /= other;
        this->z /= other;
    }

    template<typename T>
    inline void Vector<3, T>::operator=(const Vector<3, T>& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    template<typename T>
    inline void Vector<3, T>::operator=(const T& other)
    {
        this->x = other;
        this->y = other;
        this->z = other;
    }

    template<typename T>
    template<typename U>
    inline Vector<3, T>::operator Vector<3, U>() const
    {
        return Vector<3, U>((U)this->x, (U)this->y, (U)this->z);
    }

    template<typename T>
    inline Vector<3, T>::Vector(const Vector<3, T>& vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
    }

    template<typename T>
    inline Vector<3, T>::Vector(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template<typename T>
    inline Vector<3, T>::Vector(T scalar)
    {
        this->x = scalar;
        this->y = scalar;
        this->z = scalar;
    }

    #ifdef VOLUND_BUILD
        template class VOLUND_API Vector<3, float>;
        template class VOLUND_API Vector<3, double>;
        template class VOLUND_API Vector<3, int32_t>;
        template class VOLUND_API Vector<3, int64_t>;
    #else
        extern template class VOLUND_API Vector<3, float>;
        extern template class VOLUND_API Vector<3, double>;
        extern template class VOLUND_API Vector<3, int32_t>;
        extern template class VOLUND_API Vector<3, int64_t>;
    #endif

    using Vec3 = Vector<3, float>;
    using DVec3 = Vector<3, double>;
    using IVec3 = Vector<3, int32_t>;
    using I64Vec3 = Vector<3, int64_t>;
    using RGB = Vec3;
}
