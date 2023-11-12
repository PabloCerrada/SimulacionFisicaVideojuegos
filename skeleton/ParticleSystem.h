#pragma once
#include "RenderUtils.hpp"
#include <list>
using namespace std;
class Particle;
class ParticleGenerator;
class ParticleForceRegistry;
class ParticleSystem
{
private:
	ParticleForceRegistry* registering;
	std::list<Particle*> particleList;
	std::list<ParticleGenerator*> generatorList;
public:
	ParticleSystem(ParticleForceRegistry* registering_);
	~ParticleSystem();
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* gen);
	void update(double t);
};

