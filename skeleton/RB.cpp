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
	//if (dynamicRB != nullptr) std::cout << dynamicRB->getGlobalPose().p.x << " " << dynamicRB->getGlobalPose().p.y << " " << dynamicRB->getGlobalPose().p.z << std::endl;
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
	else return 0;
}

Vector3 RB::getDir() {
	if (dynamicRB != nullptr) {
		return dynamicRB->getLinearVelocity();
	}
}