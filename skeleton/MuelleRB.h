#pragma once
#include "SolidForceGenerator.h"
#include "core.hpp"
class MuelleRB : public SolidForceGenerator
{
protected:
	double k, restingLength;
	RB* other;
public:
	MuelleRB(double k_, double resting_length_, RB* rb);
	virtual void updateForce(RB* rb, double t);
	inline void setK(double k_) { k = k_; }
	inline double getK() { return k; }
	inline RB* getOther() { return other; }
	virtual ~MuelleRB() {}
};
