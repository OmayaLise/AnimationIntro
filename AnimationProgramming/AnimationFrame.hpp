#pragma once

#include <vector>

#include "Transform.hpp"

class AnimationFrame
{
	// Attribute
public:
	std::vector<Transform> animationBone;

private:
	const unsigned int keyFrameIndex;
	const char* animationName;

	// Method
public:
	AnimationFrame(const unsigned int p_keyFrame, const char* p_animationName, const unsigned int p_bonesCount);

	const unsigned int GetKeyFrameIndex() const { return keyFrameIndex; };
	const char* GetAnimationName() const { return animationName; };
};