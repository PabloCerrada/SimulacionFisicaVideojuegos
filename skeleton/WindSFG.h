#pragma once
#include "SolidForceGenerator.h"
#include "core.hpp"
class WindSFG : public SolidForceGenerator
{
protected:
	float k1, k2;
	RenderItem* renderItem;
	PxTransform* mTrans;
	PxBoxGeometry width;
	Vector3 d;
public:
	WindSFG() {};
	WindSFG(const float k1_, const float k2_, Vector3 d_);
	virtual ~WindSFG();
	virtual void updateForce(RB* rb, double t);
	inline void setDrag(float k1_, float k2_) { k1 = k1_; k2 = k2_; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
	inline void setD(Vector3 d_) { d = d_; }
};

