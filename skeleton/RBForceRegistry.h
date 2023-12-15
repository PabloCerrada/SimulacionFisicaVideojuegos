#pragma once
#include <map>
#include "RB.h"
#include "SolidForceGenerator.h"

typedef pair<SolidForceGenerator*, RB*> RBFNPair;

class RBForceRegistry : public multimap<SolidForceGenerator*, RB*>
{
public:
	void updateForces(double duration);

	void addRegistry(SolidForceGenerator* fg, RB* rb);

	void deleteRegistry(SolidForceGenerator* fg, RB* rb);

	void deleteParticleRegistry(RB* rb);
};