#pragma once
#ifndef PHYSX_SNIPPET_PARTICLE_H
#define PHYSX_SNIPPET_PARTICLE_H

#include "RenderUtils.hpp"

const float DAMPING = 0.998;

class Particle
{
public:
	Particle(const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_);
	~Particle();

	physx::PxVec3	getPos()	const;
	physx::PxVec3	getDir()	const;

	void setPos(physx::PxVec3 newPos);

	void integrate(double t);

	/*void moveConstVel(double t);
	void moveAcelVel(double t);
	void verticalShoot(double t);*/
private:
	float masa;
	physx::PxVec3	mPos;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;
	RenderItem* renderItem;
	physx::PxTransform* mTrans;
};

#endif 

