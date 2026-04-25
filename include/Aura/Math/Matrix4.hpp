#pragma once

#include "Aura/Math/Vector3.hpp"
#include <cstring>

namespace aura::math {

    struct AURA_ALIGN_16 Matrix4 {
        float m[4][4];

        Matrix4() {
            SetIdentity();
        }

        void SetIdentity() {
            std::memset(m, 0, sizeof(m));
            m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
        }

        static Matrix4 Identity() {
            Matrix4 res;
            res.SetIdentity();
            return res;
        }

        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 res;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    res.m[i][j] = m[i][0] * other.m[0][j] +
                                  m[i][1] * other.m[1][j] +
                                  m[i][2] * other.m[2][j] +
                                  m[i][3] * other.m[3][j];
                }
            }
            return res;
        }

        static Matrix4 Perspective(float fov, float aspect, float nearP, float farP) {
            Matrix4 res;
            std::memset(res.m, 0, sizeof(res.m));
            float tanHalfFov = std::tan(fov / 2.0f);
            res.m[0][0] = 1.0f / (aspect * tanHalfFov);
            res.m[1][1] = 1.0f / (tanHalfFov);
            res.m[2][2] = -(farP + nearP) / (farP - nearP);
            res.m[2][3] = -1.0f;
            res.m[3][2] = -(2.0f * farP * nearP) / (farP - nearP);
            return res;
        }

        static Matrix4 Translate(const Vector3& v) {
            Matrix4 res;
            res.m[3][0] = v.x;
            res.m[3][1] = v.y;
            res.m[3][2] = v.z;
            return res;
        }
    };

} // namespace aura::math
