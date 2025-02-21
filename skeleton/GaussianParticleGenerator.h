#pragma once
#include "ParticleGenerator.h"
#include "ParticleDragGenerator.h"
#include "TorbellinoGenerator.h"
#include "ExplosionGenerator.h"
class GaussianParticleGenerator : public ParticleGenerator
{
private:
	int id;
	random_device dVel;
	random_device dDir;
	mt19937 genVel;
	mt19937 genDir;
	uniform_real_distribution<double> _randomVel{ 0, 100 };
	normal_distribution<double> _randomDir{ 0, 1 };
public:
	GaussianParticleGenerator(ParticleSystem* pS, const PxVec3& pos, int id_, ParticleForceRegistry* registering_);
	virtual ~GaussianParticleGenerator();
	virtual void integrate(double t);
};

