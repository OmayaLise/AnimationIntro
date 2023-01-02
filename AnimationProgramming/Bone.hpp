#pragma once

#include <vector>

#include "Transform.hpp"

class Bone
{
	// Attribute
public:
	Transform transform;
	
	int index;
	std::vector<int> indexBonesChild;
	int indexBoneParent;

	const char* name;

	// Method
public:
	Bone(int p_index, Math::Vector3& p_position = Math::Vector3(), Math::Quaternion& p_rotation = Math::Quaternion(), Math::Vector3& p_scale = Math::Vector3(1.f, 1.f, 1.f));
};