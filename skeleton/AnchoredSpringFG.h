#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"
class AnchoredSpringFG : public SpringForceGenerator
{
private:
	ParticleSystem* particleSys;
public:
	AnchoredSpringFG(double k_, double resting_length_, const Vector3& anchorPos_, ParticleSystem* pS);
	virtual ~AnchoredSpringFG();
};

