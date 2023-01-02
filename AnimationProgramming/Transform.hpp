#pragma once

#include "Quaternion.hpp"
#include "Vector3.hpp"

class Transform
{
	// Attribute
public:
	Math::Quaternion rotation;
	Math::Vector3 position;
	Math::Vector3 scale;

	Math::Mat4x4 modelMatrix;

private:
	Transform* parentTransform;

	// Method
public:
	Transform();
	Transform(const Math::Vector3& p_postion, const Math::Quaternion& p_rotation, const Math::Vector3& p_scale);

	void SetParentTransform(Transform* p_parentTransform) { parentTransform = p_parentTransform; };

	Math::Mat4x4& GetLocalMatrix();
	Math::Mat4x4 GetWorldMatrix();

	static Math::Vector3 GetPosition(const Math::Mat4x4& p_mat);
};

