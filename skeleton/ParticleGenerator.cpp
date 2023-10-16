#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(const PxVec3& pos) : timeOfLife(3)
{
	mPos = pos;
	mTrans = new PxTransform(mPos);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(0.1)), mTrans, Vector4(255, 0, 0, 1));
}

ParticleGenerator::~ParticleGenerator()
{
	auto it = genParticleList.begin();
	while (!genParticleList.empty() && it != genParticleList.end()) {
		auto aux = it;
		++aux;
		delete* it;
		genParticleList.remove(*it);
		it = aux;
	}
	DeregisterRenderItem(renderItem);
	delete mTrans;
}

void ParticleGenerator::integrate(double t) { 
	Particle* p = new Particle(mPos, PxVec3(float(1 + rand() % 100) / 100.0f, float(1 + rand() % 100) / 100.0f, float(1 + rand() % 100) / 100.0f) * 10, PxVec3(0, -9.8, 0), 5, 0.5);
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