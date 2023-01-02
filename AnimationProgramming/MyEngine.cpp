#include "Engine.h"

void MyGetSkeletonBoneLocalBindTransform(int boneIndex, Math::Vector3& pos, Math::Quaternion& quat)
{
	GetSkeletonBoneLocalBindTransform(boneIndex, pos.x, pos.y, pos.z, quat.w, quat.x, quat.y, quat.z);
}

void MyGetAnimLocalBoneTransform(const char* animName, int boneIndex, int keyFrameIndex, Math::Vector3& pos, Math::Quaternion& quat)
{
	GetAnimLocalBoneTransform(animName, boneIndex, keyFrameIndex, pos.x, pos.y, pos.z, quat.w, quat.x, quat.y, quat.z);
}

void MyDrawLine(const Math::Vector3& pos0, const Math::Vector3& pos1, const Math::Vector3& rgb)
{
	DrawLine(pos0.x, pos0.y, pos0.z, pos1.x, pos1.y, pos1.z, rgb.r, rgb.g, rgb.b);
}
