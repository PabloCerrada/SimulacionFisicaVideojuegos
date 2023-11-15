#include "GravityForceGenerator.h"
GravityForceGenerator::GravityForceGenerator(const Vector3& g) {
	gravity_ = g;
}

GravityForceGenerator::~GravityForceGenerator() {

}
void GravityForceGenerator::updateForce(Particle* particle, double duration) {
	if (fabs(particle->getInvMass()) < 1e-10) return;

	particle->addForce(gravity_ * particle->getMass());
}