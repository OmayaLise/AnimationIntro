#include "AnimationBlend.hpp"

AnimationBlend::AnimationBlend()
	: currentAnimationSkeleton(nullptr)
	, nextAnimationSkeleton(nullptr)
	, currentKeyFrame(0)
	, nextKeyFrame(1)
	, currentFrameTime(0.f)
	, changeAnimTime(4)
	, animTimer(1.f)
{
}

void AnimationBlend::Update(const float p_frameTime)
{
	//float animationSpeed = 0.5f;
	float animationSpeed = 0.03333f;


	currentFrameTime += p_frameTime;

	if (currentKeyFrame == 0)
		animTimer++;
	if (animTimer == 144)
	{
		if (currentFrameTime > animationSpeed)
		{
			NextKeyFrame(currentKeyFrame, currentAnimationSkeleton->GetMaxKeyFrame());
			NextKeyFrame(nextKeyFrame, nextAnimationSkeleton->GetMaxKeyFrame());
			currentFrameTime = 0.f;
		}
	
		currentAnimationSkeleton->Update(
			currentFrameTime / animationSpeed,
			nextAnimationSkeleton->GetAnimationTransform(nextKeyFrame)
		);
	
		ChangeAnimation();
		animTimer = 0;
	}
	else
	{
		if (currentFrameTime > animationSpeed)
		{
			NextKeyFrame(currentKeyFrame, currentAnimationSkeleton->GetMaxKeyFrame());
			NextKeyFrame(nextKeyFrame, currentAnimationSkeleton->GetMaxKeyFrame());
			currentFrameTime = 0.f;
		}

		currentAnimationSkeleton->Update(
			currentFrameTime / animationSpeed,
			currentAnimationSkeleton->GetAnimationTransform(nextKeyFrame)
		);
	}
}

void AnimationBlend::SetCurrentAnimationSkeleton(AnimationSkeleton* p_currentAnimationSkeleton)
{ 
	currentAnimationSkeleton = p_currentAnimationSkeleton;
	p_currentAnimationSkeleton->currentKeyFrame = &currentKeyFrame;
	p_currentAnimationSkeleton->nextKeyFrame = &nextKeyFrame;
}

void AnimationBlend::SetNextAnimationSkeleton(AnimationSkeleton* p_nextAnimationSkeleton)
{
	nextAnimationSkeleton = p_nextAnimationSkeleton;
	p_nextAnimationSkeleton->currentKeyFrame = &currentKeyFrame;
	p_nextAnimationSkeleton->nextKeyFrame = &nextKeyFrame;
}

void AnimationBlend::ChangeAnimation()
{
	AnimationSkeleton* temp = currentAnimationSkeleton;
	SetCurrentAnimationSkeleton(nextAnimationSkeleton);
	SetNextAnimationSkeleton(temp);
}

void AnimationBlend::NextKeyFrame(unsigned int& p_keyFrame, const unsigned int p_keyFrameMax)
{
	++p_keyFrame;
	if (p_keyFrame >= p_keyFrameMax)
		p_keyFrame = 0;
}