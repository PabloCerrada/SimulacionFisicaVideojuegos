#include "RB.h"
RB::RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidDynamic* dynamico, PxShape* shape_) {
	gPhysicsRB = gPhysics_;
	gSceneRB = gScene_;
	rItem = rItem_;
	dynamicRB = dynamico;
	shape = shape_;
	dynamic = true;
}

RB::RB(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidStatic* statico, PxShape* shape_) {
	gPhysicsRB = gPhysics_;
	gSceneRB = gScene_;
	rItem = rItem_;
	staticRB = statico;
	shape = shape_;
	dynamic = false;
}

RB::~RB()
{
	if (!dynamic) {
		gSceneRB->removeActor(*staticRB);
		(staticRB)->detachShape(*shape);
		(rItem)->release();
		(staticRB)->release();
	}
	else if (dynamic) {
		gSceneRB->removeActor(*dynamicRB);
		(dynamicRB)->detachShape(*shape);
		(rItem)->release();
		(dynamicRB)->release();
	}
}

void RB::integrate(double t) {
	//if (dynamicRB != nullptr) std::cout << dynamicRB->getGlobalPose().p.x << " " << dynamicRB->getGlobalPose().p.y << " " << dynamicRB->getGlobalPose().p.z << std::endl;
	time += t;
	if (timeOfLife < time) death = true;
}

void RB::addForce(Vector3 f) {
	if (dynamic) {
		dynamicRB->addForce(f);
	}
}

void RB::clearForce() {
	if (dynamic) {
		dynamicRB->clearForce();
	}
}
float RB::getInvMss() {
	if (dynamic) {
		return dynamicRB->getInvMass();
	}
	else return 0;
}

Vector3 RB::getDir() {
	if (dynamic) {
		return dynamicRB->getLinearVelocity();
	}
}

Vector3 RB::getPos() {
	if (dynamic) {
		return dynamicRB->getGlobalPose().p;
	}
}

bool RB::getDynamic() {
	return dynamic;
}