#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator : public ParticleGenerator
{
private:
	random_device dVel;
	random_device dDir;
	mt19937 genVel;
	mt19937 genDir;
	uniform_real_distribution<double> _randomVel{ 0, 100 };
	uniform_real_distribution<double> _randomDir{ -1, 1 };
public:
	GaussianParticleGenerator(ParticleSystem* pS, const PxVec3& pos);
	virtual ~GaussianParticleGenerator();
	virtual void integrate(double t);
};

