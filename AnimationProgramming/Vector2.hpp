#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace Math
{
    class Vector2
    {
        // Attribute
    public:
        union
        {
            float data[2];
            struct
            {
                float x;
                float y;
            };
        };

        // Method
    public:
        Vector2(const float p_x = 0.f, const float p_y = 0.f);
        Vector2(const Vector2& p_copy);

        static const float DotProduct(const Vector2& p_a, const Vector2& p_b);
        static const float Magnitude(const Vector2& p_vector);
        static const Vector2& Normalize(const Vector2& p_vector);

        void Display() const;
        const std::string ToString() const;

        friend const Vector2 operator+(const Vector2& p_left, const Vector2& p_right);
        friend const Vector2 operator-(const Vector2& p_left, const Vector2& p_right);
        friend const Vector2 operator*(const Vector2& p_left, const float p_multiplier);
        friend const Vector2 operator/(const Vector2& p_left, const float p_divider);
        
        friend Vector2& operator+=(Vector2& p_left, const Vector2& p_right);
        friend Vector2& operator-=(Vector2& p_left, const Vector2& p_right);
        friend Vector2& operator*=(Vector2& p_left, const float p_multiplier);
        friend Vector2& operator/=(Vector2& p_left, const float p_divider);
        
        friend bool operator==(const Vector2& p_left, const Vector2& p_right);
        friend bool operator!=(const Vector2& p_left, const Vector2& p_right);
        
        friend bool operator<(const Vector2& p_left, const Vector2& p_right);
        friend bool operator<=(const Vector2& p_left, const Vector2& p_right);
        friend bool operator>(const Vector2& p_left, const Vector2& p_right);
        friend bool operator>=(const Vector2& p_left, const Vector2& p_right);
    };
}
#include "Vector2.inl"