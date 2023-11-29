#pragma once
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include <iostream>
using namespace physx;

const float DAMPING = 0.998;

enum FORMA {
	BOX = 0,
	SPHERE = 1
};

class Particle
{
public:
	Particle(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_, Vector4 color, float tim = 3, FORMA f = SPHERE, Vector3 dimF = {2, 2, 2});
	~Particle();

	physx::PxVec3	getPos()	const;
	physx::PxVec3	getDir()	const;

	void setPos(physx::PxVec3 newPos);

	virtual void integrate(double t);

	float getTime();

	bool getDeath();

	// Clears accumulated force
	void clearForce();
	// Add force to apply in next integration only
	void addForce(Vector3 f);

	bool update(double delta_t);

	inline float getInvMass() { return invMasa; }
	inline float getMass() { return masa; }
	inline void setTimeOfLife(float newLife) { timeOfLife = newLife; }
	
protected:
	FORMA forma;
	bool death = false;
	float tam, time;
	float masa, invMasa;
	float timeOfLife = 3;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;
	RenderItem* renderItem;
	physx::PxTransform* mTrans;
	ParticleSystem* particleSys;

	// Accumulated force
	Vector3 force;
	float _remaining_time = 0;
};

