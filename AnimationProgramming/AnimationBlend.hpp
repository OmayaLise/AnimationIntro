#pragma once

#include "AnimationSkeleton.hpp"

class AnimationBlend
{
	// Attribute
private:
	AnimationSkeleton* currentAnimationSkeleton;
	AnimationSkeleton* nextAnimationSkeleton;

	unsigned int currentKeyFrame;
	unsigned int nextKeyFrame;
	float currentFrameTime;

	unsigned int changeAnimTime;
	float animTimer;

	// Method
public:
	AnimationBlend();

	void Update(const float p_frameTime);

	void SetCurrentAnimationSkeleton(AnimationSkeleton* p_currentAnimationSkeleton);
	void SetNextAnimationSkeleton(AnimationSkeleton* p_nextAnimationSkeleton);

private:
	void ChangeAnimation();

	void NextKeyFrame(unsigned int& p_keyFrame, const unsigned int p_keyFrameMax);
};