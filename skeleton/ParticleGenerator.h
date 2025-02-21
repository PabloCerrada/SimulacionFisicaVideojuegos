#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>
#include <random>
#include "ParticleSystem.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
using namespace std;

class ParticleGenerator
{
private:
	
protected:
	ParticleForceRegistry* registering;
	ParticleSystem* particleSys;
	physx::PxVec3	mPos;
	physx::PxTransform* mTrans;
	float timeOfLife, time = 0;
	bool death = false;
public:
	ParticleGenerator();
	~ParticleGenerator();

	bool getDeath();
	virtual void integrate(double t);
};

