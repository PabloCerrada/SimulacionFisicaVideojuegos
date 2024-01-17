#pragma once
#include "MuelleRB.h"
#include "RigidBodySystem.h"
#include "core.hpp"
class MuelleAncladoRB : public MuelleRB
{
private:
	RigidBodySystem* rbSys;
public:
	MuelleAncladoRB(double k_, double resting_length_, const Vector3& anchorPos_, RigidBodySystem* rbS);
	virtual ~MuelleAncladoRB();
	inline void setGanchoPos(Vector3 newPos) { other->setPos(newPos); }
	inline Vector3 getGanchoPos() { return other->getPos(); }
};
