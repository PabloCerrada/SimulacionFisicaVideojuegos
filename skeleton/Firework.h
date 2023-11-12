#pragma once
#include "Particle.h"
#include "SimpleParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "ParticleForceRegistry.h"
class Firework : public Particle
{
private:
	float timeToExplode;
	int id;
	ParticleForceRegistry* registering;
public:
	Firework(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_, Vector4 color, int id_, ParticleForceRegistry* registering_);
	virtual ~Firework() {};
	virtual void integrate(double t);
	void explode();
};

