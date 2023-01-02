#pragma once

#include "AnimationFrame.hpp"
#include "Skeleton.hpp"

class AnimationSkeleton
{
	// Attribute
public:
	unsigned int* currentKeyFrame;
	unsigned int* nextKeyFrame;
	unsigned int maxKeyFrame;

private:
	const char* animationName;
	Skeleton* skeleton;

	std::vector<AnimationFrame> animationFrames;

	// Method
public:
	AnimationSkeleton(const char* p_animationName, Skeleton* p_skeleton);

	void Update(const float p_frameTime, const std::vector<Transform>& p_nextAnimation);

	const char* GetAnimationName() const { return animationName; };
	const unsigned int GetMaxKeyFrame() const { return maxKeyFrame; };
	const std::vector<Transform>& GetAnimationTransform(const unsigned int p_keyFrame);

private:
	void InitAnimationFrame();

	std::vector<Math::Mat4x4> GetAnimationMeshMatrix(const float p_lerpFactor,
		const std::vector<Transform>& p_nextAnimation);
	void GiveAnimatationToShader(const std::vector<Math::Mat4x4>& p_matrix) const;
	void SetAnimationSkeletonMatrix();
};