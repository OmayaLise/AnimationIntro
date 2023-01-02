#include "AnimationFrame.hpp"

#include "Engine.h"

AnimationFrame::AnimationFrame(const unsigned int p_keyFrame, const char* p_animationName, const unsigned int p_bonesCount)
	: animationBone (std::vector<Transform>())
	, keyFrameIndex (p_keyFrame)
	, animationName (p_animationName)
{
	Math::Vector3 pos;
	Math::Quaternion quat;

	for (unsigned int i = 0; i < p_bonesCount; i++)
	{
		MyGetAnimLocalBoneTransform(animationName, i, keyFrameIndex, pos, quat);
		animationBone.push_back(Transform(pos, quat.Normalize(), Math::Vector3(1.f, 1.f, 1.f)));
	}
}