#pragma once
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;

const float DAMPING = 0.998;

class Particle
{
public:
	Particle(const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_);
	~Particle();

	physx::PxVec3	getPos()	const;
	physx::PxVec3	getDir()	const;

	void setPos(physx::PxVec3 newPos);

	void integrate(double t);

	float getTime();
	/*void moveConstVel(double t);
	void moveAcelVel(double t);
	void verticalShoot(double t);*/
private:
	float tam, time;
	float masa;
	physx::PxVec3	mPos;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;
	RenderItem* renderItem;
	physx::PxTransform* mTrans;
};

