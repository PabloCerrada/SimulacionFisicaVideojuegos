#include "GaussianParticleGenerator.h"
GaussianParticleGenerator::GaussianParticleGenerator(ParticleSystem* pS, const PxVec3& pos, int id_) {
	particleSys = pS;
	mPos = pos;
	mTrans = new PxTransform(mPos);
	timeOfLife = 1;
	mt19937 genVel(dVel());
	mt19937 genDir(dDir());
	id = id_;
}

GaussianParticleGenerator::~GaussianParticleGenerator() {

}

void GaussianParticleGenerator::integrate(double t) {
	ParticleGenerator::integrate(t);
	Vector4 v;
	if (id == 2) {
		v = { 1, (rand() % 100) / 100.0f, 1, 1 };
		Particle* p = new Particle(particleSys, mPos, PxVec3(_randomDir(genDir), _randomDir(genDir), _randomDir(genDir)) * _randomVel(genVel), PxVec3(0, -9.8, 0), 5, 0.5, v);
		particleSys->addParticle(p);
	}
	else if (id == 3) {
		v = { (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1 };
		Particle* p = new Particle(particleSys, mPos, PxVec3(_randomDir(genDir), -1, _randomDir(genDir)) * _randomVel(genVel), PxVec3(0, -9.8, 0), 5, 0.5, v);
		particleSys->addParticle(p);
	}
	else {
		v = { (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1 };
		Particle* p = new Particle(particleSys, mPos, PxVec3(_randomDir(genDir), _randomDir(genDir), _randomDir(genDir)) * _randomVel(genVel), PxVec3(0, -9.8, 0), 5, 0.5, v);
		particleSys->addParticle(p);
	}
	
	

	if (timeOfLife < time) {
		death = true;
	}
}