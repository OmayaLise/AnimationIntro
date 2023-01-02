#pragma once

#include <cmath>
#include <string>
#include <iostream>

#include "Vector3.hpp"

namespace Math
{
	class Vector4
	{
		// Attribute
	public:
		union
		{
			float data[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};
		};

		// Method
	public:
		Vector4(const float p_x = 0.f, const float p_y = 0.f, const float p_z = 0.f, const float p_w = 0.f);
		Vector4(const Vector3& p_vector3, const float p_w = 0.f);
		Vector4(const Vector4& p_copy);

		static const float DotProduct(const Vector4& p_a, const Vector4& p_b);
		static const float Magnitude(const Vector4& p_vector4);
		static const float CrossProduct(const Vector4& p_a, const Vector4& p_b);
		static const Vector4 Normalize(const Vector4& p_vector4);
		static const Vector4 Homogenize(const Vector4& p_vector4);

		const Vector3 ToVector3() const;

		void Display() const;
		std::string ToString() const;

		friend Vector4 operator+(const Vector4& p_left, const Vector4& p_right);
		friend Vector4 operator-(const Vector4& p_left, const Vector4& p_right);
		friend Vector4 operator*(const Vector4& p_left, const float multiplier);
		friend Vector4 operator/(const Vector4& p_left, const float divider);

		friend Vector4& operator+=(Vector4& p_left, const Vector4& p_right);
		friend Vector4& operator-=(Vector4& p_left, const Vector4& p_right);
		friend Vector4& operator*=(Vector4& p_left, const float multipler);
		friend Vector4& operator/=(Vector4& p_left, const float divider);

		friend bool operator==(const Vector4& p_left, const Vector4& p_right);
		friend bool operator!=(const Vector4& p_left, const Vector4& p_right);
		friend bool operator<(const Vector4& p_left, const Vector4& p_right);
		friend bool operator<=(const Vector4& p_left, const Vector4& p_right);
		friend bool operator>(const Vector4& p_left, const Vector4& p_right);
		friend bool operator>=(const Vector4& p_left, const Vector4& p_right);
	};
}

#include "Vector4.inl"