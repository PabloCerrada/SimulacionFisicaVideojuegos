#pragma once
#include "RenderUtils.hpp"

#include <list>
using namespace std;
class Particle;
class ParticleGenerator;
class ParticleSystem
{
private:
	std::list<Particle*> particleList;
	std::list<ParticleGenerator*> generatorList;
public:
	ParticleSystem();
	~ParticleSystem();
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* gen);
	void update(double t);
};

