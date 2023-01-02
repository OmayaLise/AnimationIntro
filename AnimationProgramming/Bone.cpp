#include "Bone.hpp"

#include "Engine.h"

Bone::Bone(int p_index, Math::Vector3& p_position, Math::Quaternion& p_rotation, Math::Vector3& p_scale)
	: transform(Transform())
	, index(p_index)
	, indexBonesChild(std::vector<int>())
	, indexBoneParent(-1)
	, name("DefaultName")
{
	transform.position = p_position;
	transform.rotation = p_rotation;
	transform.scale = p_scale;
	transform.GetLocalMatrix();
}