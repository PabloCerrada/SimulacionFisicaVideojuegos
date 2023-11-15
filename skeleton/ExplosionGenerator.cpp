#include "ExplosionGenerator.h"
ExplosionGenerator::ExplosionGenerator(const float k_) {
	k = k_;
	timeToExplote = 1.1;
	mTrans = new PxTransform(PxVec3(20, 10, 0));
	width = PxSphereGeometry(20);
	renderItem = new RenderItem(CreateShape(width), mTrans, Vector4(1, 0, 0, 1));
}

ExplosionGenerator::~ExplosionGenerator() {
	DeregisterRenderItem(renderItem);
}
void ExplosionGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) < 1e-10) return;
	time += t;
	if (timeToExplote < time && !explotado) {
		aExplotar = true;
	}
	if (aExplotar) {
		cout << " Ex" << endl;
		bool inside = particle->getPos().x > mTrans->p.x - width.radius &&
			particle->getPos().x < mTrans->p.x + width.radius &&
			particle->getPos().y > mTrans->p.y - width.radius &&
			particle->getPos().y < mTrans->p.y + width.radius &&
			particle->getPos().z > mTrans->p.z - width.radius &&
			particle->getPos().z < mTrans->p.z + width.radius;
		if (inside) {
			cout << "in" << endl;
			Vector3 dir = particle->getDir();
			float drag_coef = dir.normalize();
			float r = sqrt(pow(particle->getPos().x - mTrans->p.x, 2) + pow(particle->getPos().y - mTrans->p.y, 2) + pow(particle->getPos().z - mTrans->p.z, 2));
			Vector3 dragF;
			dragF = -dir + ((k / pow(r, 2)) * Vector3(particle->getPos().x - mTrans->p.x, particle->getPos().y - mTrans->p.y, particle->getPos().z - mTrans->p.z) * exp(-t / 1));
			particle->addForce(dragF);
		}
		explotado = true;
		aExplotar = false;
	}
}