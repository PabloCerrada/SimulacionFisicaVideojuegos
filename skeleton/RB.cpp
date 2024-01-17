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
	// Consegui eliminar correctamente los rigidbody pero no se que toque y llego un momento que no funcionaba
	// No he conseguido eliminar correctamente los rigidbodys de escena y he hecho este apaño para que se juegue bien
	if (dynamic) {
		dynamicRB->setGlobalPose(PxTransform(0, -2000, 0));
	}
	//if (!dynamic) {
	//	/*gSceneRB->removeActor(*staticRB);
	//	(staticRB)->detachShape(*shape);
	//	(rItem)->release();
	//	(staticRB)->release();*/
	//	//rItem = nullptr;
	//	//DeregisterRenderItem(rItem);
	//	//shape->release();
	//	//(staticRB)->release();
	//}
	//else if (dynamic) {
	//	/*gSceneRB->removeActor(*dynamicRB);
	//	(dynamicRB)->detachShape(*shape);
	//	(rItem)->release();
	//	(dynamicRB)->release();*/
	//	//rItem = nullptr;
	//	//DeregisterRenderItem(rItem);
	//	//shape->release();
	//	//(dynamicRB)->release();
	//}
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

void RB::setPos(Vector3 newPos)
{
	if (dynamic) {
		dynamicRB->setGlobalPose(PxTransform(newPos));
	}
}

void RB::setDir(Vector3 newDir) {
	if (dynamic) {
		dynamicRB->setLinearVelocity(newDir);
	}
}

void RB::setAngular(Vector3 newAng) {
	if (dynamic) {
		dynamicRB->setAngularVelocity(newAng);
	}
}