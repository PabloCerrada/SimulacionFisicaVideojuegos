#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Particle.h"
ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {
	auto it = particleList.begin();
	while (!particleList.empty() && it != particleList.end()) {
		auto aux = it;
		++aux;
		delete* it;
		particleList.erase(it);
		it = aux;
	}
}

void ParticleSystem::addParticle(Particle* p) {
	particleList.push_back(p);
}

void ParticleSystem::addGenerator(ParticleGenerator* gen) {
	generatorList.push_back(gen);
}

void ParticleSystem::update(double t) {
	auto it = particleList.begin();
	while (!particleList.empty() && it != particleList.end()) {
		auto aux = it;
		++aux;

		(*it)->integrate(t);

		if ((*it)->getPos().y < -100 || (*it)->getDeath()) {
			delete* it;
			particleList.erase(it);
		}
		it = aux;
	}

	auto it2 = generatorList.begin();
	while (!generatorList.empty() && it2 != generatorList.end()) {
		auto aux = it2;
		++aux;
		(*it2)->integrate(t);
		if ((*it2)->getDeath()) generatorList.erase(it2);
		it2 = aux;
	}
}