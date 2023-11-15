#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class ExplosionGenerator : public ForceGenerator
{
protected:
	bool aExplotar = false, explotado = false;
	float k, time = 0, timeToExplote;
	RenderItem* renderItem;
	PxTransform* mTrans;
	PxSphereGeometry width;
public:
	ExplosionGenerator(const float k_);
	virtual ~ExplosionGenerator();
	virtual void updateForce(Particle* particle, double t);
};

