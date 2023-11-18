#include "ParticleDragGenerator.h"
ParticleDragGenerator::ParticleDragGenerator(const float k1_, const float k2_) {
	k1 = k1_;
	k2 = k2_; 
	mTrans = new PxTransform(PxVec3(20,10,0));
	width = PxBoxGeometry(40, 10, 10);
	renderItem = new RenderItem(CreateShape(width), mTrans, Vector4(1, 0, 0, 1));
}

ParticleDragGenerator::~ParticleDragGenerator() {
	DeregisterRenderItem(renderItem);
}
void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) < 1e-10) return;
	
	bool inside = particle->getPos().x > mTrans->p.x - width.halfExtents.x &&
		particle->getPos().x < mTrans->p.x + width.halfExtents.x &&
		particle->getPos().y > mTrans->p.y - width.halfExtents.y &&
		particle->getPos().y < mTrans->p.y + 35 &&
		particle->getPos().z > mTrans->p.z - width.halfExtents.z &&
		particle->getPos().z < mTrans->p.z + width.halfExtents.z;
	if (inside) {
		Vector3 dir = particle->getDir();
		float drag_coef = dir.normalize();
		Vector3 dragF;
		drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;
		dragF = dir + Vector3(0, 1, 0) * drag_coef;
		particle->addForce(dragF);
	}
	// Si queremos un viento que vaya SIEMPRE en contra de la direccioon de la particula
	//Vector3 dir = particle->getDir();
	//float drag_coef = dir.normalize();
	//Vector3 dragF;
	//drag_coef = k1 * drag_coef + k2 * drag_coef * drag_coef;
	//dragF = -dir * drag_coef;
	//particle->addForce(dragF);
}