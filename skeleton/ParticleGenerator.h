#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>
using namespace std;

class ParticleGenerator
{
private:
	physx::PxVec3	mPos;
	RenderItem* renderItem;
	physx::PxTransform* mTrans;
	list<Particle*> genParticleList;
	float timeOfLife;
public:
	ParticleGenerator(const PxVec3& pos);
	~ParticleGenerator();

	void integrate(double t);
};

