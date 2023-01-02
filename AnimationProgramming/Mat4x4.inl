#pragma once

#include <cmath>
#include <corecrt_math_defines.h>
#include <string>
#include <iostream>

namespace Math
{
	inline Mat4x4::Mat4x4(const float p_value)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				data[i][j] = p_value;
			}
		}
	}

	inline Mat4x4::Mat4x4(const Mat4x4& p_other)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				data[i][j] = p_other.data[i][j];
			}
		}
	}

	inline Mat4x4::Mat4x4(const float f1, const float f2, const float f3, const float f4,
		const float f5, const float f6, const float f7, const float f8,
		const float f9, const float f10, const float f11, const float f12,
		const float f13, const float f14, const float f15, const float f16)
	{
		data[0][0] = f1;  data[0][1] = f2;  data[0][2] = f3;  data[0][3] = f4;
		data[1][0] = f5;  data[1][1] = f6;  data[1][2] = f7;  data[1][3] = f8;
		data[2][0] = f9;  data[2][1] = f10; data[2][2] = f11; data[2][3] = f12;
		data[3][0] = f13; data[3][1] = f14; data[3][2] = f15; data[3][3] = f16;
	}

	inline Mat4x4 Mat4x4::Identity()
	{
		Mat4x4 identity;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					identity.data[i][j] = 1;
			}
		}
		return identity;
	}

	inline Mat4x4 Mat4x4::Transpose()
	{
		Mat4x4 transpose;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				transpose.data[i][j] = data[j][i];
			}
		}
		return transpose;
	}

	inline Mat4x4 Mat4x4::GetInverse() const
	{
		Mat4x4 inverse;
		float determinant = Determinant();
		if (determinant == 0)
			return Mat4x4::Identity();
		Mat4x4 cofactorMatrix = CofactorMatrix();
		cofactorMatrix.Transpose();
		cofactorMatrix = cofactorMatrix * (1.f / determinant);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inverse.data[i][j] = cofactorMatrix.data[i][j];
			}
		}
		return inverse;
	}

	inline float Mat4x4::Determinant() const
	{
		return data[0][0] * (data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[1][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) + data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]))
			- data[0][1] * (data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[1][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]))
			+ data[0][2] * (data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - data[1][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]))
			- data[0][3] * (data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - data[1][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) + data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
	}

	inline Mat4x4 Mat4x4::CofactorMatrix() const
	{
		Mat4x4 Cof;

		Cof.data[0][0] = data[1][1] * (data[2][2] * data[3][3] - data[3][2] * data[2][3]) - data[1][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) + data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);
		Cof.data[0][1] = -(data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[1][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]));
		Cof.data[0][2] = data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - data[1][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
		Cof.data[0][3] = -(data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - data[1][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) + data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));

		Cof.data[1][0] = -(data[0][1] * (data[2][2] * data[3][3] - data[3][2] * data[2][3]) - data[0][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) + data[0][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]));
		Cof.data[1][1] = data[0][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[0][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[0][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);
		Cof.data[1][2] = -(data[0][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - data[0][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[0][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
		Cof.data[1][3] = data[0][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - data[0][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) + data[0][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
		Cof.data[2][0] = data[0][1] * (data[1][2] * data[3][3] - data[3][2] * data[1][3]) - data[0][2] * (data[1][1] * data[3][3] - data[3][1] * data[1][3]) + data[0][3] * (data[1][1] * data[3][2] - data[1][2] * data[3][1]);
		Cof.data[2][1] = -(data[0][0] * (data[1][2] * data[3][3] - data[1][3] * data[3][2]) - data[0][2] * (data[1][0] * data[3][3] - data[3][0] * data[1][3]) + data[0][3] * (data[1][0] * data[3][2] - data[1][2] * data[3][0]));
		Cof.data[2][2] = data[0][0] * (data[1][1] * data[3][3] - data[1][3] * data[3][1]) - data[0][1] * (data[1][0] * data[3][3] - data[3][0] * data[1][3]) + data[0][3] * (data[1][0] * data[3][1] - data[1][1] * data[3][0]);
		Cof.data[2][3] = -(data[0][0] * (data[1][1] * data[3][2] - data[1][2] * data[3][1]) - data[0][1] * (data[1][0] * data[3][2] - data[3][0] * data[1][2]) + data[0][2] * (data[1][0] * data[3][1] - data[1][1] * data[3][0]));

		Cof.data[3][0] = -(data[0][1] * (data[1][2] * data[2][3] - data[2][2] * data[1][3]) - data[0][2] * (data[1][1] * data[2][3] - data[2][1] * data[1][3]) + data[0][3] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]));
		Cof.data[3][1] = data[0][0] * (data[1][2] * data[2][3] - data[1][3] * data[2][2]) - data[0][2] * (data[1][0] * data[2][3] - data[2][0] * data[1][3]) + data[0][3] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]);
		Cof.data[3][2] = -(data[0][0] * (data[1][1] * data[2][3] - data[1][3] * data[2][1]) - data[0][1] * (data[1][0] * data[2][3] - data[2][0] * data[1][3]) + data[0][3] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]));
		Cof.data[3][3] = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) - data[0][1] * (data[1][0] * data[2][2] - data[2][0] * data[1][2]) + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

		return Cof;
	}

	inline Mat4x4 Mat4x4::CreateTranslationMatrix(const Vector3& p_translation)
	{
		Mat4x4 translationMatrix = Mat4x4::Identity();
		if (p_translation.x != 0.f)
			translationMatrix.data[0][3] = p_translation.x;
		if (p_translation.y != 0.f)
			translationMatrix.data[1][3] = p_translation.y;
		if (p_translation.z != 0.f)
			translationMatrix.data[2][3] = p_translation.z;
		return translationMatrix;
	}

	inline Mat4x4 Mat4x4::CreateScaleMatrix(const Vector3& p_scale)
	{
		Mat4x4 scaleMatrix = Mat4x4::Identity();
		scaleMatrix.data[0][0] = p_scale.x;
		scaleMatrix.data[1][1] = p_scale.y;
		scaleMatrix.data[2][2] = p_scale.z;
		scaleMatrix.data[3][3] = 1.f;
		return scaleMatrix;
	}

	inline Mat4x4 Mat4x4::CreateXRotationMatrix(float p_angleDegree)
	{
		p_angleDegree *= (float)M_PI / 180.f; // To radians
		Mat4x4 xRotationMatrix = Mat4x4::Identity();
		xRotationMatrix.data[1][1] = cosf(p_angleDegree);
		xRotationMatrix.data[1][2] = -sinf(p_angleDegree);
		xRotationMatrix.data[2][1] = sinf(p_angleDegree);
		xRotationMatrix.data[2][2] = cosf(p_angleDegree);
		return xRotationMatrix;
	}

	inline Mat4x4 Mat4x4::CreateYRotationMatrix(float p_angleDegree)
	{
		p_angleDegree *= (float)M_PI / 180.f; // To radians
		Mat4x4 yRotationMatrix = Mat4x4::Identity();
		yRotationMatrix.data[0][0] = cosf(p_angleDegree);
		yRotationMatrix.data[0][2] = sinf(p_angleDegree);
		yRotationMatrix.data[2][0] = -sinf(p_angleDegree);
		yRotationMatrix.data[2][2] = cosf(p_angleDegree);
		return yRotationMatrix;
	}

	inline Mat4x4 Mat4x4::CreateZRotationMatrix(float p_angleDegree)
	{
		p_angleDegree *= (float)M_PI / 180.f; // floato radians
		Mat4x4 zRotationMatrix = Mat4x4::Identity();
		zRotationMatrix.data[0][0] = cosf(p_angleDegree);
		zRotationMatrix.data[0][1] = -sinf(p_angleDegree);
		zRotationMatrix.data[1][0] = sinf(p_angleDegree);
		zRotationMatrix.data[1][1] = cosf(p_angleDegree);
		return zRotationMatrix;
	}

	inline Mat4x4 Mat4x4::CreateRotationMatrix(const Vector3& p_angleDegree)
	{
		return CreateYRotationMatrix(p_angleDegree.y) * CreateXRotationMatrix(p_angleDegree.x) * CreateZRotationMatrix(p_angleDegree.z);
	}

	inline Mat4x4 Mat4x4::CreateTransformationMatrix(const Vector3& p_translation, const Vector3& p_scale, const Vector3& p_rotationDegree)
	{
		return CreateTranslationMatrix(p_translation) * CreateYRotationMatrix(p_rotationDegree.y) * CreateXRotationMatrix(p_rotationDegree.x) * CreateZRotationMatrix(p_rotationDegree.z) * CreateScaleMatrix(p_scale);
	}

	inline Vector3 Mat4x4::GetPositionFromMatrix(const Mat4x4& p_matrix)
	{
		Vector3 position;

		position.x = p_matrix.data[0][3];
		position.y = p_matrix.data[1][3];
		position.z = p_matrix.data[2][3];

		return position;
	}

	inline Vector3 Mat4x4::GetScaleFromMatrix(const Mat4x4& p_matrix)
	{
		Vector3 scale;
		for (unsigned int i = 0; i < 3; i++)
		{
			Vector3 xScale = Vector3(p_matrix.data[0][i], p_matrix.data[1][i], p_matrix.data[2][i]);
			float length = Vector3::Magnitude(xScale);
			scale.x = p_matrix.data[0][i] / length;
			scale.y = p_matrix.data[1][i] / length;
			scale.z = p_matrix.data[2][i] / length;
		}
		return scale;
	}

	inline void Mat4x4::Display() const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			std::cout << "| ";
			for (unsigned int j = 0; j < 4; j++)
			{
				std::cout << data[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << std::endl;
	}

	inline const std::string& Mat4x4::ToString() const
	{
		std::string result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result += "| ";
			for (unsigned int j = 0; j < 4; j++)
			{
				result += std::to_string(data[i][j]) + " ";
			}
			result += "|\n";
		}
		return result;
	}

	inline Mat4x4 Mat4x4::operator+(const Mat4x4& p_right)
	{
		Mat4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = data[i][j] + p_right.data[i][j];
			}
		}
		return result;
	}

	inline Mat4x4 Mat4x4::operator-(const Mat4x4& p_right)
	{
		Mat4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = data[i][j] - p_right.data[i][j];
			}
		}
		return result;
	}

	inline const Mat4x4 Mat4x4::operator*(const Mat4x4& other) const
	{
		Mat4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				for (unsigned int k = 0; k < 4; k++)
				{
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
	}

	inline Vector4 Mat4x4::operator*(const Vector4& p_right)
	{
		Vector4 result;
		result.x = data[0][0] * p_right.x + data[0][1] * p_right.y + data[0][2] * p_right.z + data[0][3] * p_right.w;
		result.y = data[1][0] * p_right.x + data[1][1] * p_right.y + data[1][2] * p_right.z + data[1][3] * p_right.w;
		result.z = data[2][0] * p_right.x + data[2][1] * p_right.y + data[2][2] * p_right.z + data[2][3] * p_right.w;
		result.w = data[3][0] * p_right.x + data[3][1] * p_right.y + data[3][2] * p_right.z + data[3][3] * p_right.w;
		return result;
	}

	inline Mat4x4 Mat4x4::operator*(const float p_left)
	{
		Mat4x4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = data[i][j] * p_left;
			}
		}
		return result;
	}

	inline bool operator==(const Mat4x4& p_left, const Mat4x4& p_right)
	{
		float margin = 0.000001f;
		bool result = true;

		for (unsigned int i = 0; i < 4; ++i)
		{
			for (unsigned int j = 0; j < 4; ++j)
			{
				if (p_left.data[i][j] > p_right.data[i][j] + margin || p_left.data[i][j] < p_right.data[i][j] - margin)
				{
					result = false;
					break;
				}
			}
			if (!result)
				break;
		}
		return result;
	}
}