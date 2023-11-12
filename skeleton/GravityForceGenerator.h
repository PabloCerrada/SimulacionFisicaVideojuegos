#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
class GravityForceGenerator : public ForceGenerator
{
private:
	Vector3 gravity_;
public:
	GravityForceGenerator(const Vector3& g);

	virtual void updateForce(Particle* particle, double duration);

	inline void setGravity(Vector3 g) { gravity_ = g; }
};

