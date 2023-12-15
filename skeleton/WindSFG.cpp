#include "WindSFG.h"
WindSFG::WindSFG(const float k1_, const float k2_) {
	k1 = k1_;
	k2 = k2_;
	mTrans = new PxTransform(PxVec3(20, 10, 0));
	width = PxBoxGeometry(40, 10, 10);
	//renderItem = new RenderItem(CreateShape(width), mTrans, Vector4(1, 0, 0, 1));
}

WindSFG::~WindSFG() {
	DeregisterRenderItem(renderItem);
}
void WindSFG::updateForce(RB* rb, double t) {
	if (fabs(rb->getInvMss()) < 1e-10) return;

	
	Vector3 dir = rb->getDir();
	float drag_coef = dir.normalize();
	Vector3 dragF;
	drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;
	dragF = dir + Vector3(0, 1, 0) * drag_coef;
	rb->addForce(dragF);
	
	// Si queremos un viento que vaya SIEMPRE en contra de la direccioon de la particula
	//Vector3 dir = particle->getDir();
	//float drag_coef = dir.normalize();
	//Vector3 dragF;
	//drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;
	//dragF = -dir * drag_coef;
	//particle->addForce(dragF);
}