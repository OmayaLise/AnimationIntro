#include "Transform.hpp"

Transform::Transform()
	: position(Math::Vector3())
	, rotation(Math::Quaternion())
	, scale(Math::Vector3(1.f, 1.f, 1.f))
	, modelMatrix(Math::Mat4x4::Identity())
	, parentTransform(nullptr)
{
}

Transform::Transform(const Math::Vector3& p_postion, const Math::Quaternion& p_rotation, const Math::Vector3& p_scale)
	: parentTransform(nullptr)
{
	position = p_postion;
	rotation = p_rotation;
	scale = p_scale;
	GetLocalMatrix();
}

Math::Mat4x4& Transform::GetLocalMatrix()
{
	modelMatrix = Math::Mat4x4::CreateTranslationMatrix(position) * Math::Quaternion::QuatToMatrix(rotation) * Math::Mat4x4::CreateScaleMatrix(scale);
	return modelMatrix;
}

 Math::Mat4x4 Transform::GetWorldMatrix()
{
	Math::Mat4x4 world = modelMatrix;

	if (parentTransform)
		world = parentTransform->GetWorldMatrix() * world;

	return world;
}

Math::Vector3 Transform::GetPosition(const Math::Mat4x4& p_mat)
{
	return Math::Vector3(p_mat.data[0][3], p_mat.data[1][3], p_mat.data[2][3]);
}