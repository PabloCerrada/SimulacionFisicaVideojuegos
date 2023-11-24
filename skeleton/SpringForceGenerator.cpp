#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator(double k_, double resting_length_, Particle* other_) {
	k = k_;
	restingLength = resting_length_;
	other = other_;
}

void SpringForceGenerator::updateForce(Particle* particle, double t) {
	// Particle is the particle to apply the force
	Vector3 relativePosVector = other->getPos() - particle->getPos();

	// normalizee: Normalize de relativePosVector and returns its length
	const float length = relativePosVector.normalize();
	const float delta_x = length - restingLength;

	Vector3 force = relativePosVector * delta_x * k;
	particle->addForce(force);
}