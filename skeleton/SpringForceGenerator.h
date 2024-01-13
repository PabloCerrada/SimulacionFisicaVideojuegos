#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class SpringForceGenerator : public ForceGenerator
{
protected:
	double k, restingLength;
	Particle* other;
public:
	SpringForceGenerator(double k_, double resting_length_, Particle* other_);
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k_) { k = k_; }
	inline double getK() { return k; }
	inline Particle* getOther() { return other; }
	virtual ~SpringForceGenerator() {}
};

