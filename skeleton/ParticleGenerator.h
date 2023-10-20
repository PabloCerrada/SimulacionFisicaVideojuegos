#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>
#include <random>
using namespace std;

class ParticleGenerator
{
private:
	
protected:
	physx::PxVec3	mPos;
	physx::PxTransform* mTrans;
	float timeOfLife;
	list<Particle*> genParticleList;
public:
	ParticleGenerator();
	~ParticleGenerator();

	virtual void integrate(double t);
};

