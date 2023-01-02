#pragma once

#include <cmath>
#include <corecrt_math_defines.h>
#include <string>
#include <iostream>

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Utils.hpp"

namespace Math
{
	class Mat4x4 //line then column
	{
		// Attribute
	public:
		float data[4][4];

		// Method
	public:
		Mat4x4(const float p_value = 0);
		Mat4x4(const Mat4x4& p_other);
		Mat4x4(const float f1, const float f2, const float f3, const float f4,
			const float f5, const float f6, const float f7, const float f8,
			const float f9, const float f10, const float f11, const float f12,
			const float f13, const float f14, const float f15, const float f16);

		static Mat4x4 Identity();

		Mat4x4 Transpose();
		Mat4x4 GetInverse() const;
		float Determinant() const;
		Mat4x4 CofactorMatrix() const;

		static Mat4x4 CreateTranslationMatrix(const Vector3& p_translation);
		static Mat4x4 CreateScaleMatrix(const Vector3& p_scale);
		static Mat4x4 CreateXRotationMatrix(float p_angleDegree);
		static Mat4x4 CreateYRotationMatrix(float p_angleDegree);
		static Mat4x4 CreateZRotationMatrix(float p_angleDegree);

		static Mat4x4 CreateRotationMatrix(const Vector3& p_angleDegree);
		static Mat4x4 CreateTransformationMatrix(const Vector3& p_translation, const Vector3& p_scale, const Vector3& p_rotationDegree);

		static Vector3 GetPositionFromMatrix(const Mat4x4& p_matrix);
		static Vector3 GetScaleFromMatrix(const Mat4x4& p_matrix);

		void Display() const;
		const std::string& ToString() const;

		Mat4x4 operator+(const Mat4x4& p_right);
		Mat4x4 operator-(const Mat4x4& p_right);
		const Mat4x4 operator*(const Mat4x4& other) const;
		Vector4 operator*(const Vector4& p_right);
		Mat4x4 operator*(const float p_left);

		friend bool operator==(const Mat4x4& p_left, const Mat4x4& p_right);
	};
}

#include "Mat4x4.inl"