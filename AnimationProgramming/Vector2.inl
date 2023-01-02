#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace Math
{
    inline Vector2::Vector2(const float p_x, const float p_y)
        : x(p_x)
        , y(p_y)
    {}

    inline Vector2::Vector2(const Vector2& p_copy)
        : x(p_copy.x)
        , y(p_copy.y)
    {}

    inline const float Vector2::DotProduct(const Vector2& p_a, const Vector2& p_b)
    {
        return p_a.x * p_b.x + p_a.y * p_b.y;
    }

    inline const float Vector2::Magnitude(const Vector2& p_vector)
    {
        return sqrt(p_vector.x * p_vector.x + p_vector.y * p_vector.y);
    }

    inline const Vector2& Vector2::Normalize(const Vector2& p_vector)
    {
        float magnitude = Magnitude(p_vector);
        Vector2 vectorNormalize = p_vector;
        vectorNormalize.x *= (1 / magnitude);
        vectorNormalize.y *= (1 / magnitude);
        return vectorNormalize;
    }

    inline void Vector2::Display() const
    {
        std::cout << "[ " << x << ", " << y << " ]" << std::endl;
    }

    inline const std::string Vector2::ToString() const
    {
        return "[ " + std::to_string(x) + ", " + std::to_string(y) + " ]";
    }

    inline const Vector2 operator+(const Vector2& p_left, const Vector2& p_right)
    {
        return { p_left.x + p_right.x, p_left.y + p_right.y };
    }

    inline const Vector2 operator-(const Vector2& p_left, const Vector2& p_right)
    {
        return { p_left.x - p_right.x, p_left.y - p_right.y };
    }

    inline const Vector2 operator*(const Vector2& p_left, const float p_multiplier)
    {
        return { p_left.x * p_multiplier, p_left.y * p_multiplier };
    }

    inline const Vector2 operator/(const Vector2& p_left, const float p_divider)
    {
        return { p_left.x / p_divider, p_left.y / p_divider };
    }

    inline Vector2& operator+=(Vector2& p_left, const Vector2& p_right)
    {
        p_left = p_left + p_right;
        return p_left;
    }

    inline Vector2& operator-=(Vector2& p_left, const Vector2& p_right)
    {
        p_left = p_left - p_right;
        return p_left;
    }

    inline Vector2& operator*=(Vector2& p_left, const float p_multiplier)
    {
        p_left = p_left * p_multiplier;
        return p_left;
    }

    inline Vector2& operator/=(Vector2& p_left, const float p_divider)
    {
        p_left = p_left / p_divider;
        return p_left;
    }

    inline bool operator==(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x <= p_right.x + 0.001 && p_left.x >= p_right.x - 0.001 &&
            p_left.y <= p_right.y + 0.001 && p_left.y >= p_right.y - 0.001)
            return true;
        else
            return false;
    }

    inline bool operator!=(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x <= p_right.x + 0.001f && p_left.x >= p_right.x - 0.001f &&
            p_left.y <= p_right.y + 0.001f && p_left.y >= p_right.y - 0.001f)
            return false;
        else
            return true;
    }

    inline bool operator<(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x < p_right.x && p_left.y < p_right.y)
            return true;
        else
            return false;
    }

    inline bool operator<=(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x <= p_right.x && p_left.y <= p_right.y)
            return true;
        else
            return false;
    }

    inline bool operator>(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x > p_right.x && p_left.y > p_right.y)
            return true;
        else
            return false;
    }

    inline bool operator>=(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x >= p_right.x && p_left.y >= p_right.y)
            return true;
        else
            return false;
    }
}