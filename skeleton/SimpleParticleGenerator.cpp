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
	Vector4 v((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1);
	Particle* p = new Particle(particleSys, mPos, PxVec3(_randomDir(genDir), _randomDir(genDir), _randomDir(genDir)) * _randomVel(genVel), PxVec3(0, -9.8, 0), 5, 0.5, v);
	particleSys->addParticle(p);

	if (timeOfLife < time) {
		death = true;
	}
}