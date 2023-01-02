#pragma once

#include <iostream>
#include <string>

#include "Quaternion.hpp"
#include "Utils.hpp"

namespace Math
{
    inline Quaternion::Quaternion(const float p_x, const float p_y, const float p_z, const float p_w)
        : x(p_x), y(p_y), z(p_z), w(p_w)
    {}

  
    inline Quaternion Quaternion::operator+(const Quaternion& q) const
    {
        return {
                x + q.x,
                y + q.y,
                z + q.z,
                w + q.w
        };
    }

    inline Quaternion Quaternion::operator-(const Quaternion& q) const
    {
        return {
                x - q.x,
                y - q.y,
                z - q.z,
                w - q.w
        };
    }

    inline Quaternion Quaternion::operator*(const Quaternion& q) const
    {
        return {
                x * q.w + y * q.z - z * q.y + w * q.x,
                -x * q.z + y * q.w + z * q.x + w * q.y,
                x * q.y - y * q.x + z * q.w + w * q.z,
                -x * q.x - y * q.y - z * q.z + w * q.w
        };
    }

    inline Quaternion Quaternion::operator/(const Quaternion& q) const
    {
        return {
                x / q.x,
                y / q.y,
                z / q.z,
                w / q.w
        };
    }

    inline Quaternion Quaternion::operator*=(const Quaternion& q)
    {
        return *this = *this * q;
    }

    inline bool Quaternion::operator==(const Quaternion& q) const
    {
        return (
            Math::Abs(x - q.x) <= Math::weakEpsilon &&
            Math::Abs(y - q.y) <= Math::weakEpsilon &&
            Math::Abs(z - q.z) <= Math::weakEpsilon &&
            Math::Abs(w - q.w) <= Math::weakEpsilon
            );
    }

    inline std::ostream& operator<<(std::ostream& o, const Quaternion& q)
    {
        return o << "x = " << q.x << ", y = " << q.y << ", z = " << q.z << ", w = " << q.w;
    }

    //Functions
    inline Quaternion Quaternion::Identity()
    {
        return { 0.f, 0.f, 0.f, 1.f };
    }

    inline Quaternion Quaternion::Normalize() const
    {
        float length = this->Length();

        if (length < Math::weakEpsilon)
            length = 1.0f;

        float ilength = 1.0f / length;

        return {
                x * ilength,
                y * ilength,
                z * ilength,
                w * ilength
        };
    }

    inline float Quaternion::Length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    inline Quaternion Quaternion::Invert() const
    {
        Quaternion result = *this;
        float length = this->Length();
        float lengthSq = length * length;

        if (lengthSq != 0.0)
        {
            float i = 1.0f / lengthSq;

            result.x *= -i;
            result.y *= -i;
            result.z *= -i;
            result.w *= i;
        }

        return result;
    }

    inline Quaternion Quaternion::QuatFromMatrix(const Mat4x4& i_mat)
    {
#if 0 // GLM
        Matrix4 m = i_mat;
        float m00 = m.line[0].data[0];
        float m11 = m.line[1].data[1];
        float m22 = m.line[2].data[2];
        float m21 = m.line[2].data[1];
        float m12 = m.line[1].data[2];
        float m02 = m.line[0].data[2];
        float m20 = m.line[2].data[0];
        float m10 = m.line[1].data[0];
        float m01 = m.line[0].data[1];

        Quaternion q = { 0.f, 0.f, 0.f, 0.f };
        q.w = Math::Sqrt(1.f + m00 + m11 + m22) * 0.5f;
        if (q.w == 0.f)
            return { 0.f, 0.f, 0.f, 1.f };

        q.x = (m21 - m12) / (4.f * q.w);
        q.y = (m20 - m02) / (4.f * q.w);
        q.z = (m10 - m01) / (4.f * q.w);

        return q;
#elif 0 // RAYMATH
        Quaternion result;

        if ((i_mat.data[0] > i_mat.data[5]) && (i_mat.data[0] > i_mat.data[10]))
        {
            float s = sqrtf(1.0f + i_mat.data[0] - i_mat.data[5] - i_mat.data[10]) * 2.f;

            if (s == 0.f)
                return { 0.f, 0.f, 0.f, 1.f };

            result.x = 0.25f * s;
            result.y = (i_mat.data[4] + i_mat.data[1]) / s;
            result.z = (i_mat.data[2] + i_mat.data[8]) / s;
            result.w = (i_mat.data[9] - i_mat.data[6]) / s;
        }
        else if (i_mat.data[5] > i_mat.data[10])
        {
            float s = sqrtf(1.0f + i_mat.data[5] - i_mat.data[0] - i_mat.data[10]) * 2;

            if (s == 0.f)
                return { 0.f, 0.f, 0.f, 1.f };

            result.x = (i_mat.data[4] + i_mat.data[1]) / s;
            result.y = 0.25f * s;
            result.z = (i_mat.data[9] + i_mat.data[6]) / s;
            result.w = (i_mat.data[2] - i_mat.data[8]) / s;
        }
        else
        {
            float s = sqrtf(1.0f + i_mat.data[10] - i_mat.data[0] - i_mat.data[5]) * 2;

            if (s == 0.f)
                return { 0.f, 0.f, 0.f, 1.f };

            result.x = (i_mat.data[2] + i_mat.data[8]) / s;
            result.y = (i_mat.data[9] + i_mat.data[6]) / s;
            result.z = 0.25f * s;
            result.w = (i_mat.data[4] - i_mat.data[1]) / s;
        }

        return result;
#elif 1 // JOLT
        //previous form
        //float diagonal = i_mat.data[0] + i_mat.data[5] + i_mat.data[10];

        float diagonal = i_mat.data[0][0] + i_mat.data[1][0] + i_mat.data[2][0];

        if (diagonal >= 0.0f)
        {
            float s = sqrt(diagonal + 1.0f);
            float sInverse = 0.5f / s;
            return {
                    (i_mat.data[2][1] - i_mat.data[1][2]) * sInverse,
                    (i_mat.data[0][2] - i_mat.data[2][0]) * sInverse,
                    (i_mat.data[1][0] - i_mat.data[0][1]) * sInverse,
                    0.5f * s
            };
        }
        else
        {
            int situationIndex = 0;

            if (i_mat.data[1][1] > i_mat.data[0][0])
                situationIndex = 1;
            if (i_mat.data[2][2] > i_mat.data[situationIndex][situationIndex])
                situationIndex = 2;

            if (situationIndex == 0)
            {
                float s = sqrt(i_mat.data[0][0] - (i_mat.data[1][1] + i_mat.data[2][2]) + 1);
                float sInverse = 0.5f / s;
                return {
                        0.5f * s,
                        (i_mat.data[0][1] + i_mat.data[1][0]) * sInverse,
                        (i_mat.data[2][0] + i_mat.data[0][2]) * sInverse,
                        (i_mat.data[2][1] - i_mat.data[1][2]) * sInverse
                };
            }
            else if (situationIndex == 1)
            {
                float s = sqrt(i_mat.data[1][1] - (i_mat.data[2][2] + i_mat.data[0][0]) + 1);
                float sInverse = 0.5f / s;
                return {
                        (i_mat.data[0][1] + i_mat.data[1][0]) * sInverse,
                        0.5f * s,
                        (i_mat.data[1][2] + i_mat.data[2][1]) * sInverse,
                        (i_mat.data[0][2] - i_mat.data[2][0]) * sInverse
                };
            }
            else
            {
                float s = sqrt(i_mat.data[2][2] - (i_mat.data[0][0] + i_mat.data[1][1]) + 1);
                float sInverse = 0.5f / s;
                return {
                        (i_mat.data[0][2] + i_mat.data[2][0]) * sInverse,
                        (i_mat.data[2][1] + i_mat.data[1][2]) * sInverse,
                        0.5f * s,
                        (i_mat.data[0][1] - i_mat.data[1][0]) * sInverse
                };
            }
        }
#endif
    }

    inline Mat4x4 Quaternion::QuatToMatrix(const Quaternion& p_q)
    {
        p_q.Normalize();

        float dX = 2.f * p_q.x;
        float dY = 2.f * p_q.y;
        float dZ = 2.f * p_q.z;

        float sqX = dX * p_q.x;
        float sqY = dY * p_q.y;
        float sqZ = dZ * p_q.z;

        float qXY = dX * p_q.y;
        float qXZ = dX * p_q.z;
        float qYZ = dY * p_q.z;
        float qXW = dX * p_q.w;
        float qYW = dY * p_q.w;
        float qZW = dZ * p_q.w;

        return {
                1.f - sqY - sqZ,    qXY - qZW,          qXZ + qYW,          0.f,
                qXY + qZW,          1.f - sqX - sqZ,    qYZ - qXW,          0.f,
                qXZ - qYW,          qYZ + qXW,          1.f - sqX - sqY,    0.f,
                0.f,                0.f,                0.f,                1.f
        };

    }
    

    inline Quaternion Quaternion::QuatFromEuler(const float& i_yaw, const float& i_pitch, const float& i_roll)
    {
        float cosYaw = cos(i_yaw * 0.5f);
        float sinYaw = sin(i_yaw * 0.5f);
        float cosPitch = cos(i_pitch * 0.5f);
        float sinPitch = sin(i_pitch * 0.5f);
        float cosRoll = cos(i_roll * 0.5f);
        float sinRoll = sin(i_roll * 0.5f);

        return {
                sinYaw * cosPitch * cosRoll - cosYaw * sinPitch * sinRoll,
                sinYaw * cosPitch * sinRoll + cosYaw * sinPitch * cosRoll,
                cosYaw * cosPitch * sinRoll - sinYaw * sinPitch * cosRoll,
                cosYaw * cosPitch * cosRoll + sinYaw * sinPitch * sinRoll
        };
    }

    inline Quaternion Quaternion::QuatFromEuler(const Vector3& i_eulerRadAngles)
    {
        return QuatFromEuler(i_eulerRadAngles.x, i_eulerRadAngles.y, i_eulerRadAngles.z);
    }

    inline Vector3 Quaternion::QuatToEuler() const
    {
        // Vector3 zero ? 
        Vector3 result;

        // Yaw (x-axis rotation)
        float x0 = 2.0f * (w * x + y * z);
        float x1 = 1.0f - 2.0f * (x * x + y * y);
        result.x = atan2(x0, x1);

        // Pitch (y-axis rotation)
        float y0 = 2.0f * (w * y - z * x);
        y0 = y0 > 1.0f ? 1.0f : y0;
        y0 = y0 < -1.0f ? -1.0f : y0;
        result.y = asin(y0);

        // Roll (z-axis rotation)
        float z0 = 2.0f * (w * z + x * y);
        float z1 = 1.0f - 2.0f * (y * y + z * z);
        result.z = atan2(z0, z1);

        return result;
    }

    inline Quaternion Quaternion::QuatFromAxisAngle(const Vector3& i_axis, float i_radAngle)
    {
        Quaternion result = Identity();

        if (Math::Vector3::Magnitude(i_axis) != 0.0f)
            i_radAngle *= 0.5f;

        Vector3 newAxis = Math::Vector3::Normalize(i_axis);

        float cosres = cos(i_radAngle);
        float sinres = sin(i_radAngle);

        result.x = newAxis.x * sinres;
        result.y = newAxis.y * sinres;
        result.z = newAxis.z * sinres;
        result.w = cosres;

        return result.Normalize();
    }

    inline void Quaternion::QuatToAxisAngle(Vector3& o_outAxis, float& o_outAngle)
    {
        if (Math::Abs(w) > 1.0f)
            *this = this->Normalize();

        Vector3 resAxis = { 0.0f, 0.0f, 0.0f };
        float resAngle = 2.0f * acos(w);
        float den = sqrt(1.0f - w * w);

        if (den > 0.0001f)
        {
            resAxis.x = x / den;
            resAxis.y = y / den;
            resAxis.z = z / den;
        }
        else
        {
            resAxis.x = x;
            resAxis.y = y;
            resAxis.z = z;
        }

        o_outAxis = resAxis;
        o_outAngle = resAngle;
    }

    inline Quaternion Quaternion::VectorToVector(const Vector3& i_from, const Vector3& i_to)
    {
        Quaternion result = { 0.f, 0.f, 0.f, 0.f };

        float dot = Vector3::DotProduct(i_from, i_to);
        Vector3 cross = Vector3::CrossProduct(i_from, i_to);

        result.x = cross.x;
        result.y = cross.y;
        result.z = cross.z;
        result.w = 1.0f + dot;

        return result.Normalize();
    }

    inline Quaternion Quaternion::Lerp(const Quaternion& i_q1, const Quaternion& i_q2, float i_factor)
    {
        i_factor = Math::Clamp(i_factor, 0.f, 1.f);
        return {
                i_q1.x + i_factor * (i_q2.x - i_q1.x),
                i_q1.y + i_factor * (i_q2.y - i_q1.y),
                i_q1.z + i_factor * (i_q2.z - i_q1.z),
                i_q1.w + i_factor * (i_q2.w - i_q1.w)
        };
    }

    inline Quaternion Quaternion::Nlerp(const Quaternion& i_q1, const Quaternion& i_q2, float i_factor)
    {
        i_factor = Math::Clamp(i_factor, 0.f, 1.f);

        Quaternion result = Lerp(i_q1, i_q2, i_factor);

        return result.Normalize();
    }

    inline Quaternion Quaternion::Slerp(const Quaternion& i_q1, const Quaternion& i_q2, float i_factor)
    {
#if false
        i_factor = Math::Clamp(i_factor, 0.f, 1.f);

        Quaternion result = Identity();

        float cosHalfTheta = i_q1.x * i_q2.x + i_q1.y * i_q2.y + i_q1.z * i_q2.z + i_q1.w * i_q2.w;

        if (Math::Abs(cosHalfTheta) >= 1.0f)
            result = i_q1;
        else if (cosHalfTheta > 0.95f)
            result = Nlerp(i_q1, i_q2, i_factor);
        else
        {
            float halfTheta = acos(cosHalfTheta);
            float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

            if (Math::Abs(sinHalfTheta) < 0.001f)
            {
                result.x = (i_q1.x * 0.5f + i_q2.x * 0.5f);
                result.y = (i_q1.y * 0.5f + i_q2.y * 0.5f);
                result.z = (i_q1.z * 0.5f + i_q2.z * 0.5f);
                result.w = (i_q1.w * 0.5f + i_q2.w * 0.5f);
            }
            else
            {
                float ratioA = sin((1 - i_factor) * halfTheta) / sinHalfTheta;
                float ratioB = sin(i_factor * halfTheta) / sinHalfTheta;

                result.x = (i_q1.x * ratioA + i_q2.x * ratioB);
                result.y = (i_q1.y * ratioA + i_q2.y * ratioB);
                result.z = (i_q1.z * ratioA + i_q2.z * ratioB);
                result.w = (i_q1.w * ratioA + i_q2.w * ratioB);
            }
        }

        return result;
#else
        float cosHalfOmega = i_q1.x * i_q2.x + i_q1.y * i_q2.y + i_q1.z * i_q2.z + i_q1.w * i_q2.w;

        Quaternion tto = i_q2;
        if (cosHalfOmega < 0.f)
        {
            tto = { -tto.x, -tto.y, -tto.z, -tto.w };
            cosHalfOmega = -cosHalfOmega;
        }

        if (Math::Abs(cosHalfOmega) >= 1.0f)
        {
            return i_q1;
        }
        else
        {
            float halfOmega = acos(cosHalfOmega);
            float sinHalfOmega = sqrt(1.f - cosHalfOmega * cosHalfOmega);

            float ratioA = (sin((1.f - i_factor) * halfOmega) / sinHalfOmega);
            float ratioB = (sin(i_factor * halfOmega) / sinHalfOmega);
            return { (i_q1.x * ratioA + tto.x * ratioB),
                (i_q1.y * ratioA + tto.y * ratioB),
                (i_q1.z * ratioA + tto.z * ratioB),
                (i_q1.w * ratioA + tto.w * ratioB) };
        }
#endif

    }

}