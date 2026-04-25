#pragma once

#include "Aura/Core/Base.hpp"
#include <cmath>
#include <iostream>

namespace aura::math {

    struct AURA_ALIGN_16 Vector3 {
        float x, y, z;

        constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        constexpr Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Up;
        static const Vector3 Forward;
        static const Vector3 Right;

        inline Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
        inline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
        inline Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
        inline Vector3 operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

        inline float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
        
        inline Vector3 Cross(const Vector3& v) const {
            return Vector3(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            );
        }

        inline float Length() const { return std::sqrt(x * x + y * y + z * z); }
        inline float LengthSquared() const { return x * x + y * y + z * z; }

        inline Vector3 Normalized() const {
            float len = Length();
            if (len > 0.0f) return *this / len;
            return Vector3::Zero;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
            return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
        }
    };

    inline const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
    inline const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
    inline const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
    inline const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
    inline const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);

} // namespace aura::math
