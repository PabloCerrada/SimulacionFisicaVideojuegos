#include "RB.h"
RB::RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidDynamic* dynamico) {
	gPhysicsRB = gPhysics_;
	gSceneRB = gScene_;
	rItem = rItem_;
	dynamicRB = dynamico;
}

RB::RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidStatic* statico) {
	gPhysicsRB = gPhysics_;
	gSceneRB = gScene_;
	rItem = rItem_;
	staticRB = statico;
}

void RB::integrate(double t) {
	time += t;
	if (timeOfLife < time) death = true;
}

void RB::addForce(Vector3 f) {
	if (dynamicRB != nullptr) {
		dynamicRB->addForce(f);
	}
}

void RB::clearForce() {
	if (dynamicRB != nullptr) {
		dynamicRB->clearForce();
	}
}
float RB::getInvMss() {
	if (dynamicRB != nullptr) {
		return dynamicRB->getInvMass();
	}
}

Vector3 RB::getDir() {
	if (dynamicRB != nullptr) {
		return dynamicRB->getLinearVelocity();
	}
}