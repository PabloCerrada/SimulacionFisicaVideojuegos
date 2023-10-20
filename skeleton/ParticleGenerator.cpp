#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator()
{
	
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
	delete mTrans;
}

void ParticleGenerator::integrate(double t) { 

}