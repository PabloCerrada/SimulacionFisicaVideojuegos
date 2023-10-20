#pragma once
#include "Particle.h"
#include "SimpleParticleGenerator.h"
class Firework : public Particle
{
private:
	float timeToExplode;
public:
	Firework(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_);
	virtual ~Firework() {};
	virtual void integrate(double t);
	void explode();
};

