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
	bool dynamic;
	// Accumulated force
	Vector3 force;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;

	PxPhysics* gPhysicsRB = nullptr;
	PxScene* gSceneRB = nullptr;
	PxRigidStatic* staticRB = nullptr;
	PxRigidDynamic* dynamicRB = nullptr;
	PxShape* shape = nullptr;
	RenderItem* rItem = nullptr;
public:
	RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidStatic* statico, PxShape* shape_);
	RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidDynamic* dynamico, PxShape* shape_);
	~RB();

	void integrate(double t);

	// Add force to apply in next integration only
	void addForce(Vector3 f);
	// Clears accumulated force
	void clearForce();

	float getInvMss();

	Vector3 getDir();
	Vector3 getPos();
	PxRigidDynamic* getRB() { return dynamicRB; }

	void setPos(physx::PxVec3 newPos);
	void setDir(Vector3 newDir);
	void setAngular(Vector3 newAng);

	bool getDynamic();
};

