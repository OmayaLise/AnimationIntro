#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include "Mat4x4.hpp"
#include "Vector3.hpp"

namespace Math
{
    class Quaternion
    {
        // Attribute
    public:
        union
        {
            struct 
            { 
                float x; 
                float y; 
                float z; 
                float w;
            };

            float data[4];

            struct
            {
                Vector3 vector;
                float scalar;
            };
        };

        // Method
    public:
        Quaternion(const float p_x = 0.f, const float p_y = 0.f, const float p_z = 0.f, const float p_w = 1.f);

        Quaternion(const Quaternion& other) { x = other.x; y = other.y; z = other.z; w = other.w; };
        Quaternion& operator=(const Quaternion& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; };

        // Operators 
        Quaternion operator+(const Quaternion& p_q) const;
        Quaternion operator-(const Quaternion& p_q) const;
        Quaternion operator*(const Quaternion& p_q) const;
        Quaternion operator/(const Quaternion& p_q) const;
        Quaternion operator*=(const Quaternion& p_q);
        bool operator==(const Quaternion& p_q) const;

        // Functions 
        static Quaternion Identity();

        //Normalize quaternion
        Quaternion Normalize() const;

        //Give quaternion lenght 
        float Length() const;

        //Give quaternion 's inverse if it exist
        Quaternion Invert() const;

        //Give quaternion from matrix
        static Quaternion QuatFromMatrix(const Mat4x4& i_mat);

        static Mat4x4 QuatToMatrix(const Quaternion& p_q);

        //Create a quaternion from traditional radian angles
        // yaw Rotation around X axis, in radian
        // pitch Rotation around Y axis, in radian
        // roll Rotation around Z axis, in radian
        static Quaternion QuatFromEuler(const float& i_yaw, const float& i_pitch, const float& i_roll);

        //Create a quaternion from traditional radian angles To recheck
        static Quaternion QuatFromEuler(const Vector3& i_eulerRadAngles);

        //  Give the Euler angles equivalent to quaternion (yaw, pitch, roll)
        Vector3 QuatToEuler() const;

        // Create a quaternion given an angle, in radians, and a rotation axis
        static Quaternion QuatFromAxisAngle(const Vector3& i_axis, float i_radAngle);

        // Give the axis and angle of rotation from a quaternion
        void QuatToAxisAngle(Vector3& o_outAxis, float& o_outAngle);

        //Give rotation quaternion from a vector to another
        static Quaternion VectorToVector(const Vector3& i_from, const Vector3& i_to);

        //Calculate linear interpolation between two quaternions (normalize before)
        static Quaternion Lerp(const Quaternion& i_q1, const Quaternion& i_q2, float i_factor);

        //Calculate slerp-optimized interpolation between two quaternions (normalize before)
        static Quaternion Nlerp(const Quaternion& i_q1, const Quaternion& i_q2, float i_factor);

        //Calculates spherical linear interpolation between two quaternions (normalize before)
        static Quaternion Slerp(const Quaternion& i_q1, const Quaternion& i_q2, float i_factor);
    };

    std::ostream& operator<<(std::ostream& o_o, const Quaternion& i_q);
};

#include "Quaternion.inl"