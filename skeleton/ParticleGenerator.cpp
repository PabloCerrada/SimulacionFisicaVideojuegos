#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{
	
}

ParticleGenerator::~ParticleGenerator()
{
	delete mTrans;
	delete particleSys;
}

void ParticleGenerator::integrate(double t) { 
	time += t;
}

bool ParticleGenerator::getDeath() {
	return death;
}