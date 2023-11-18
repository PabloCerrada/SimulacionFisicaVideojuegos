#include "TorbellinoGenerator.h"
TorbellinoGenerator::TorbellinoGenerator(const float k_) {
	k = k_;
	mTrans = new PxTransform(PxVec3(0, -10, 0));
	width = PxBoxGeometry(20, 10, 20);
	renderItem = new RenderItem(CreateShape(width), mTrans, Vector4(1, 0, 0, 0.1));
}
void TorbellinoGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) < 1e-10) return;

	bool inside = particle->getPos().x > mTrans->p.x - width.halfExtents.x &&
		particle->getPos().x < mTrans->p.x + width.halfExtents.x &&
		particle->getPos().y > mTrans->p.y - width.halfExtents.y &&
		particle->getPos().y < mTrans->p.y + 150 &&
		particle->getPos().z > mTrans->p.z - width.halfExtents.z &&
		particle->getPos().z < mTrans->p.z + width.halfExtents.z;
	if (inside) {
		Vector3 particlePosition = particle->getPos();
		if (fabs(1 / particle->getMass()) < 1e-10) return;
		Vector3 velocidadtorbellino = k * Vector3(-(particlePosition.z - mTrans->p.z), 75 - (particlePosition.y - mTrans->p.y), particlePosition.x - mTrans->p.x);
		Vector3 v = particle->getDir() - velocidadtorbellino;
		float drag_coef = v.normalize();
		drag_coef = k * drag_coef + 0 * drag_coef * drag_coef;
		Vector3 dragF = -v * drag_coef;

		particle->addForce(dragF);
	}
}