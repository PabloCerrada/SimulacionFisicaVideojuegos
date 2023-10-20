#include "SimpleParticleGenerator.h"
SimpleParticleGenerator::SimpleParticleGenerator(ParticleSystem* pS, const PxVec3& pos) {
	particleSys = pS;
	mPos = pos;
	mTrans = new PxTransform(mPos);
	timeOfLife = 1;
	mt19937 genVel(dVel());
	mt19937 genDir(dDir());
}

SimpleParticleGenerator::~SimpleParticleGenerator() {
	
}

void SimpleParticleGenerator::integrate(double t) {
	ParticleGenerator::integrate(t);
	Particle* p = new Particle(particleSys, mPos, PxVec3(_randomDir(genDir), _randomDir(genDir), _randomDir(genDir)) * 20, PxVec3(0, -9.8, 0), 5, 0.5);
	particleSys->addParticle(p);

	if (timeOfLife < time) {
		death = true;
	}
}