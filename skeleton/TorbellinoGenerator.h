#pragma once
#include "ParticleDragGenerator.h"
class TorbellinoGenerator : public ParticleDragGenerator
{
private:
	float k;
	Vector3 pos;
public:
	TorbellinoGenerator(const float k_);
	virtual void updateForce(Particle* particle, double t);
};

