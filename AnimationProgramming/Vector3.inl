#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace Math
{
	inline Vector3::Vector3(const float p_x, const float p_y, const float p_z)
		: x(p_x)
		, y(p_y)
		, z(p_z)
	{}

	inline Vector3::Vector3(const Vector3& p_copy)
		: x(p_copy.x)
		, y(p_copy.y)
		, z(p_copy.z)
	{}

	inline const float Vector3::DotProduct(const Vector3& p_a, const Vector3& p_b)
	{
		return p_a.x * p_b.x + p_a.y * p_b.y + p_a.z * p_b.z;
	}

	inline const float Vector3::Magnitude(const Vector3& p_vector3)
	{
		return sqrt(p_vector3.x * p_vector3.x + p_vector3.y * p_vector3.y + p_vector3.z * p_vector3.z);
	}

	inline const Vector3 Vector3::CrossProduct(const Vector3& p_a, const Vector3& p_b)
	{
		return { (p_a.y * p_b.z) - (p_a.z * p_b.y), (p_a.z * p_b.x) - (p_a.x * p_b.z), (p_a.x * p_b.y) - (p_a.y * p_b.x) };
	}

	inline const Vector3 Vector3::Normalize(const Vector3& p_vector3)
	{
		float magnitude = Magnitude(p_vector3);
		Vector3 vectorNormalize = p_vector3;
		if (magnitude != 0)
		{
			vectorNormalize.x *= (1 / magnitude);
			vectorNormalize.y *= (1 / magnitude);
			vectorNormalize.z *= (1 / magnitude);
		}
		return vectorNormalize;
	}

	inline void Vector3::Display() const
	{
		std::cout << "[ " << x << ", " << y << ", " << z << " ]" << std::endl;
	}

	inline const std::string Vector3::ToString() const
	{
		return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
	}

	inline Vector3 operator+(const Vector3& p_left, const Vector3& p_right)
	{
		return { p_left.x + p_right.x, p_left.y + p_right.y, p_left.z + p_right.z };
	}

	inline Vector3 operator-(const Vector3& p_left, const Vector3& p_right)
	{
		return { p_left.x - p_right.x, p_left.y - p_right.y, p_left.z - p_right.z };
	}

	inline Vector3 operator-(const Vector3 p_right)
	{
		return { -p_right.x, -p_right.y, -p_right.z };
	}

	inline Vector3 operator*(const Vector3& p_left, const float multiplier)
	{
		return { p_left.x * multiplier, p_left.y * multiplier, p_left.z * multiplier };
	}

	inline Vector3 operator/(const Vector3& p_left, const float divider)
	{
		return { p_left.x / divider, p_left.y / divider, p_left.z / divider };
	}

	inline Vector3& operator+=(Vector3& p_left, const Vector3& p_right)
	{
		p_left = p_left + p_right;
		return p_left;
	}

	inline Vector3& operator-=(Vector3& p_left, const Vector3& p_right)
	{
		p_left = p_left - p_right;
		return p_left;
	}

	inline Vector3& operator*=(Vector3& p_left, const float multipler)
	{
		p_left = p_left * multipler;
		return p_left;
	}

	inline Vector3& operator/=(Vector3& p_left, const float divider)
	{
		p_left = p_left / divider;
		return p_left;
	}

	inline bool operator==(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x <= p_right.x + 0.001f && p_left.x >= p_right.x - 0.001f &&
			p_left.y <= p_right.y + 0.001f && p_left.y >= p_right.y - 0.001f &&
			p_left.z <= p_right.z + 0.001f && p_left.z >= p_right.z - 0.001f)
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x <= p_right.x + 0.001f && p_left.x >= p_right.x - 0.001f &&
			p_left.y <= p_right.y + 0.001f && p_left.y >= p_right.y - 0.001f &&
			p_left.z <= p_right.z + 0.001f && p_left.z >= p_right.z - 0.001f)
			return false;
		else
			return true;
	}

	inline bool operator<(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x < p_right.x && p_left.y < p_right.y && p_left.z < p_right.z)
			return true;
		else
			return false;
	}

	inline bool operator<=(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x <= p_right.x && p_left.y <= p_right.y && p_left.z <= p_right.z)
			return true;
		else
			return false;
	}

	inline bool operator>(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x > p_right.x && p_left.y > p_right.y && p_left.z > p_right.z)
			return true;
		else
			return false;
	}

	inline bool operator>=(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x >= p_right.x && p_left.y >= p_right.y && p_left.z >= p_right.z)
			return true;
		else
			return false;
	}
}