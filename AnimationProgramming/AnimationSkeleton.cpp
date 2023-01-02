#include "AnimationSkeleton.hpp"

#include "Engine.h"

AnimationSkeleton::AnimationSkeleton(const char* p_animationName, Skeleton* p_skeleton)
	: currentKeyFrame(nullptr)
	, nextKeyFrame(nullptr)
	, maxKeyFrame(GetAnimKeyCount(p_animationName))
	, animationName(p_animationName)
	, skeleton(p_skeleton)
	, animationFrames(std::vector<AnimationFrame>())
{
	InitAnimationFrame();
}

void AnimationSkeleton::Update(const float p_frameTime, const std::vector<Transform>& p_nextAnimation)
{
	GiveAnimatationToShader(GetAnimationMeshMatrix(p_frameTime, p_nextAnimation));
	SetAnimationSkeletonMatrix();
}

const std::vector<Transform>& AnimationSkeleton::GetAnimationTransform(const unsigned int p_keyFrame)
{
	return animationFrames[p_keyFrame].animationBone;
}

void AnimationSkeleton::InitAnimationFrame()
{
	for (unsigned int i = 0; i < maxKeyFrame; i++)
	{
		animationFrames.push_back(AnimationFrame(i, animationName, 64));
	}
}

std::vector<Math::Mat4x4> AnimationSkeleton::GetAnimationMeshMatrix(const float p_lerpFactor, const std::vector<Transform>& p_nextAnimation)
{
	std::vector<Math::Mat4x4> res;
	std::vector<Math::Mat4x4> localTransform;
	localTransform.resize(64);
	std::vector<Math::Mat4x4> modelTransform;
	modelTransform.resize(64);

	for (unsigned int i = 0; i < 64; i++)
	{
		// Test Lerp
		Transform lerpTrs;
		lerpTrs.position.x = Math::lerp(animationFrames[*currentKeyFrame].animationBone[i].position.x
			, p_nextAnimation[i].position.x, p_lerpFactor);
		lerpTrs.position.y = Math::lerp(animationFrames[*currentKeyFrame].animationBone[i].position.y
			, p_nextAnimation[i].position.y, p_lerpFactor);
		lerpTrs.position.z = Math::lerp(animationFrames[*currentKeyFrame].animationBone[i].position.z
			, p_nextAnimation[i].position.z, p_lerpFactor);

		lerpTrs.rotation = Math::Quaternion::Slerp(animationFrames[*currentKeyFrame].animationBone[i].rotation
			, p_nextAnimation[i].rotation, p_lerpFactor);

		localTransform[i] = skeleton->bonesApose[i]->transform.GetLocalMatrix() *
			lerpTrs.GetLocalMatrix();

		if (i == 0)
		{
			modelTransform[0] = localTransform[0];
		}
		else
		{
			int parent = skeleton->bones[i]->indexBoneParent;
			modelTransform[i] = modelTransform[parent] * localTransform[i];
		}

		res.push_back(modelTransform[i] * skeleton->bonesApose[i]->transform.GetWorldMatrix().GetInverse().Transpose());
	}
	return res;
}

void AnimationSkeleton::GiveAnimatationToShader(const std::vector<Math::Mat4x4>& p_matrix) const
{
	std::vector<float> temp;
	for (unsigned int i = 0; i < 64; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			for (unsigned int k = 0; k < 4; k++)
			{
				temp.push_back(p_matrix[i].data[k][j]);
			}
		}
	}
	SetSkinningPose(&temp[0], 64);
}

void AnimationSkeleton::SetAnimationSkeletonMatrix()
{
	for (unsigned int i = 0; i < 64; i++)
	{
		skeleton->bones[i]->transform.modelMatrix =
			skeleton->bonesApose[i]->transform.GetLocalMatrix() *
			animationFrames[*currentKeyFrame].animationBone[i].GetLocalMatrix();
	}
}