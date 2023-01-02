// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

#include "Skeleton.hpp"
#include "AnimationSkeleton.hpp"
#include "AnimationBlend.hpp"

void DrawGizmo()
{
	Math::Vector3 offset(-200.f, 0.f, 0.f);
	// X axis
	MyDrawLine(Math::Vector3(0, 0, 0) + offset, Math::Vector3(100, 0, 0) + offset, Math::Vector3(1, 0, 0));
	// Y axis
	MyDrawLine(Math::Vector3(0, 0, 0) + offset, Math::Vector3(0, 100, 0) + offset, Math::Vector3(0, 1, 0));
	// Z axis
	MyDrawLine(Math::Vector3(0, 0, 0) + offset, Math::Vector3(0, 0, 100) + offset, Math::Vector3(0, 0, 1));
}

class CSimulation : public ISimulation
{
	Skeleton* skeleton;
	AnimationSkeleton* animationSkeletonWalk;
	AnimationSkeleton* animationSkeletonRun;
	AnimationBlend* animationBlend;

	virtual void Init() override
	{
		skeleton = new Skeleton(GetSkeletonBoneCount());
		animationSkeletonWalk = new AnimationSkeleton("ThirdPersonWalk.anim", skeleton);
		animationSkeletonRun = new AnimationSkeleton("ThirdPersonRun.anim", skeleton);
		animationBlend = new AnimationBlend();

		animationBlend->SetCurrentAnimationSkeleton(animationSkeletonRun);
		animationBlend->SetNextAnimationSkeleton(animationSkeletonWalk);
	}

	virtual void Update(float frameTime) override
	{
		DrawGizmo();
		
		animationBlend->Update(frameTime);

		skeleton->Draw();
	}

};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

