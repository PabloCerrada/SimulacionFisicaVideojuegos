#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"
class GomaElastica : public SpringForceGenerator
{
private:
	float elasticidad;
public:
	GomaElastica(double k_, double resting_length_, Particle* other_, float elasticidad_);
	~GomaElastica() {}

	virtual void updateForce(Particle* particle, double t);

};

