#pragma once
#ifndef PHYSX_SNIPPET_PARTICLE_H
#define PHYSX_SNIPPET_PARTICLE_H

#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(const physx::PxVec3& pos, const physx::PxVec3& dir, float vel_);
	~Particle();

	physx::PxVec3	getPos()	const;
	physx::PxVec3	getDir()	const;

	void setPos(physx::PxVec3 newPos);
	void setVel(float newVel);
	void moveConstVel(double t);
private:
	float vel;
	physx::PxVec3	mPos;
	physx::PxVec3	mDir;
	RenderItem* renderItem;
	physx::PxTransform* mTrans;
};

#endif 

