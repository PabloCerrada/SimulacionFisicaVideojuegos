#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"
class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double k_, double resting_length_, const Vector3& anchorPos_);
	~AnchoredSpringFG();
};

