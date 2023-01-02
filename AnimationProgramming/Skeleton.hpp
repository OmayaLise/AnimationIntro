#pragma once

#include <vector>

#include "Bone.hpp"

class Skeleton
{
	// Attribute
public:
	std::vector<Bone*> bones;
	std::vector<Bone*> bonesInvert;
	std::vector<Bone*> bonesApose;

	// Method
public:
	Skeleton(const unsigned int p_boneCount);
	~Skeleton();

	void Draw() const;

private:
	void InitBones(const unsigned int p_boneCount);

	void InitInvertBones();

	void InitAPoseBones();

	void SetParentBone(const unsigned int p_indexBone, const unsigned int p_indexBoneParent);
};