#include "SimpleParticleGenerator.h"
SimpleParticleGenerator::SimpleParticleGenerator(const PxVec3& pos) {
	mPos = pos;
	mTrans = new PxTransform(mPos);
	timeOfLife = 3;
	mt19937 genVel(dVel());
	mt19937 genDir(dDir());
}

SimpleParticleGenerator::~SimpleParticleGenerator() {

}

void SimpleParticleGenerator::integrate(double t) {
	
	//Particle* p = new Particle(mPos, PxVec3(float(1 + rand() % 100) / 100.0f, float(1 + rand() % 100) / 100.0f, float(1 + rand() % 100) / 100.0f) * 10, PxVec3(0, -9.8, 0), 5, 0.5);
	Particle* p = new Particle(mPos, PxVec3(_randomDir(genDir), _randomDir(genDir), _randomDir(genDir)) * _randomVel(genVel), PxVec3(0, -9.8, 0), 5, 0.5);
	genParticleList.push_back(p);

	auto it = genParticleList.begin();
	while (!genParticleList.empty() && it != genParticleList.end()) {
		auto aux = it;
		++aux;

		(*it)->integrate(t);

		if ((*it)->getPos().y < -30 || (*it)->getTime() > timeOfLife) {
			delete* it;
			genParticleList.remove(*it);
		}
		it = aux;
	}
}