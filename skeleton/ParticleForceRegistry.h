#pragma once

#include <map>
#include "ForceGenerator.h"

typedef pair<ForceGenerator*, Particle*> FNPair;

class ParticleForceRegistry : public multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fg, Particle* p);

	void deleteRegistry(ForceGenerator* fg, Particle* p);

	void deleteParticleRegistry(Particle* p);
};

