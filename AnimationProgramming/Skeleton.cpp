#include "Skeleton.hpp"

#include "Engine.h"

Skeleton::Skeleton(const unsigned int p_boneCount)
	: bones(std::vector<Bone*>())
{
	InitBones(p_boneCount);
	InitInvertBones();
	InitAPoseBones();
}

Skeleton::~Skeleton()
{
	for (unsigned int i = 0; i < bones.size(); i++)
		delete bones[i];
	bones.clear();
}

void Skeleton::Draw() const
{
	for (unsigned int i = 2; i < bones.size() - 6; i++)
	{
		if (bones[i]->indexBoneParent == -1)
			continue;

		Math::Vector3 bonePosition = Transform::GetPosition(bones[i]->transform.GetWorldMatrix());
		Math::Vector3 boneParentPosition = Transform::GetPosition(bones[bones[i]->indexBoneParent]->transform.GetWorldMatrix());
		Math::Vector3 offset(200.f, 0.f, 0.f);
		Math::Vector3 Blue(0.f, 0.f, 1.f);
		MyDrawLine(bonePosition + offset, boneParentPosition + offset, Blue);
	}
}

void Skeleton::InitBones(const unsigned int p_boneCount)
{

	for (unsigned int i = 0; i < p_boneCount; i++)
	{
		bones.push_back(new Bone(i));
	}

	Math::Vector3 pos;
	Math::Quaternion quat;
	for (unsigned int i = 0; i < bones.size(); i++)
	{
		MyGetSkeletonBoneLocalBindTransform(i, pos, quat);
		Bone* bone = bones[i];
		bone->transform.position = pos;
		bone->transform.rotation = quat.Normalize();
		bone->transform.scale = Math::Vector3(1.f, 1.f, 1.f);
		bone->transform.GetLocalMatrix();
		bone->index = i;
		bone->name = GetSkeletonBoneName(i);

		if (GetSkeletonBoneParentIndex(i) != -1)
			SetParentBone(i, GetSkeletonBoneParentIndex(i));
	}

}

void Skeleton::InitInvertBones()
{
	for (unsigned int i = 0; i < bones.size(); i++)
	{
		bonesInvert.push_back(bones[i]);
	}

	for (unsigned int i = 0; i < bonesInvert.size(); i++)
	{
			bonesInvert[i]->transform.modelMatrix = bonesInvert[i]->transform.modelMatrix.GetInverse();
	}
}

void Skeleton::InitAPoseBones()
{
	for (unsigned int i = 0; i < bones.size(); i++)
	{
		bonesApose.push_back(bones[i]);
	}
}

void Skeleton::SetParentBone(const unsigned int p_indexBone, const unsigned int p_indexBoneParent)
{
	bones[p_indexBone]->indexBoneParent = p_indexBoneParent;
	bones[p_indexBoneParent]->indexBonesChild.push_back(p_indexBone);
	bones[p_indexBone]->transform.SetParentTransform(&bones[p_indexBoneParent]->transform);
}
