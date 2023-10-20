#pragma once
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include <iostream>
using namespace physx;

const float DAMPING = 0.998;

class Particle
{
public:
	Particle(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_);
	~Particle();

	physx::PxVec3	getPos()	const;
	physx::PxVec3	getDir()	const;

	void setPos(physx::PxVec3 newPos);

	virtual void integrate(double t);

	float getTime();

	bool getDeath();
	/*void moveConstVel(double t);
	void moveAcelVel(double t);
	void verticalShoot(double t);*/
protected:
	bool death = false;
	float tam, time;
	float masa;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;
	RenderItem* renderItem;
	physx::PxTransform* mTrans;
	ParticleSystem* particleSys;
};

