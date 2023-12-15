#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;
const float DAMPINGRB = 0.998;
class RB
{
private:
	float masa, invMasa; 
	float timeOfLife = 3, time;
	bool death = false;
	// Accumulated force
	Vector3 force;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;

	PxPhysics* gPhysicsRB = nullptr;
	PxScene* gSceneRB = nullptr;
	PxRigidStatic* staticRB = nullptr;
	PxRigidDynamic* dynamicRB = nullptr;
	RenderItem* rItem = nullptr;
public:
	RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidStatic* statico);
	RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidDynamic* dynamico);
	~RB() {};

	void integrate(double t);

	// Add force to apply in next integration only
	void addForce(Vector3 f);
	// Clears accumulated force
	void clearForce();

	float getInvMss();

	Vector3 getDir();
};

