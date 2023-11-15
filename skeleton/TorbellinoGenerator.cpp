#include "TorbellinoGenerator.h"
TorbellinoGenerator::TorbellinoGenerator(const float k_) {
	k = k_;
	mTrans = new PxTransform(PxVec3(20, -10, 0));
	width = PxBoxGeometry(20, 20, 20);
	renderItem = new RenderItem(CreateShape(width), mTrans, Vector4(1, 0, 0, 1));
}
void TorbellinoGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) < 1e-10) return;

	bool inside = particle->getPos().x > mTrans->p.x - width.halfExtents.x &&
		particle->getPos().x < mTrans->p.x + width.halfExtents.x &&
		particle->getPos().y > mTrans->p.y - width.halfExtents.y &&
		particle->getPos().y < mTrans->p.y + 100 &&
		particle->getPos().z > mTrans->p.z - width.halfExtents.z &&
		particle->getPos().z < mTrans->p.z + width.halfExtents.z;
	if (inside) {
		cout << "in" << endl;
		Vector3 dir = particle->getDir();
		float drag_coef = dir.normalize();
		Vector3 dragF;
		dragF = dir + Vector3(0, 1, 0) + k * Vector3(particle->getPos().x - mTrans->p.x, 50 - (particle->getPos().y - mTrans->p.y), -(particle->getPos().z - mTrans->p.z));
		particle->addForce(dragF);
	}
}