#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator : public ForceGenerator
{
private:
	float height, volume, liquidDensity, gravity = 9.8;
	Particle* liquidParticle;
	ParticleSystem* particleSys;
public:
	BuoyancyForceGenerator(float h, float V, float d, ParticleSystem* pS);
	virtual ~BuoyancyForceGenerator() {}

	virtual void updateForce(Particle* particle, double t);
};

