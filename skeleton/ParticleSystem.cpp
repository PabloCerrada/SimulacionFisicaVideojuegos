#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "Particle.h"
ParticleSystem::ParticleSystem(ParticleForceRegistry* registering_) {
	registering = registering_;
}

ParticleSystem::~ParticleSystem() {
	auto it = particleList.begin();
	while (!particleList.empty() && it != particleList.end()) {
		auto aux = it;
		++aux;
		registering->deleteParticleRegistry(*it);
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
			registering->deleteParticleRegistry(*it);
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

void ParticleSystem::generateSpringDemo() {
	// First one standard spring uniting 2 particles
	Particle* p1 = new Particle(this, { -10, 10, 0 }, { 0,0,0 }, { 0,0,0 }, 1, 3, Vector4(1, 0, 0, 1));
	addParticle(p1);
	Particle* p2 = new Particle(this, { 10, 10, 0 }, { 0,0,0 }, { 0,0,0 }, 2, 6, Vector4(1, 0, 0, 1));
	addParticle(p2);
	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	registering->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	registering->addRegistry(f2, p2);
}

void ParticleSystem::generateSpringAnchoredDemo() {
	Particle* p3 = new Particle(this, { -10, 20,0 }, { 0,0,0 }, { 0,0,0 }, 3, 9, Vector4(1, 0, 0, 1));
	addParticle(p3);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10, 20, 0 }, this);
	registering->addRegistry(f3, p3);
}