#pragma once

#include <cmath>
#include <string>
#include <iostream>

namespace Math
{
	class Vector3
	{
		// Attribute
	public:
		union
		{
			float data[3];
			struct
			{
				float x;
				float y;
				float z;
			};
			struct
			{
				float r;
				float g;
				float b;
			};
		};

		// Method
	public:
		Vector3(const float p_x = 0, const float p_y = 0, const float p_z = 0);
		Vector3(const Vector3& p_copy);

		static const float DotProduct(const Vector3& p_a, const Vector3& p_b);
		static const float Magnitude(const Vector3& p_vector3);
		static const Vector3 CrossProduct(const Vector3& p_a, const Vector3& p_b);
		static const Vector3 Normalize(const Vector3& p_vector3);

		void Display() const;
		const std::string ToString() const;

		friend Vector3 operator+(const Vector3& p_left, const Vector3& p_right);
		friend Vector3 operator-(const Vector3& p_left, const Vector3& p_right);
		friend Vector3 operator-(const Vector3 p_right);
		friend Vector3 operator*(const Vector3& p_left, const float multiplier);
		friend Vector3 operator/(const Vector3& p_left, const float divider);

		friend Vector3& operator+=(Vector3& p_left, const Vector3& p_right);
		friend Vector3& operator-=(Vector3& p_left, const Vector3& p_right);
		friend Vector3& operator*=(Vector3& p_left, const float multipler);
		friend Vector3& operator/=(Vector3& p_left, const float divider);

		friend bool operator==(const Vector3& p_left, const Vector3& p_right);
		friend bool operator!=(const Vector3& p_left, const Vector3& p_right);
		friend bool operator<(const Vector3& p_left, const Vector3& p_right);
		friend bool operator<=(const Vector3& p_left, const Vector3& p_right);
		friend bool operator>(const Vector3& p_left, const Vector3& p_right);
		friend bool operator>=(const Vector3& p_left, const Vector3& p_right);
	};
}

#include "Vector3.inl"