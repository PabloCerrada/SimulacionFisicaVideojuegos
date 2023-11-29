#include "GomaElastica.h"
GomaElastica::GomaElastica(double k_, double resting_length_, Particle* other_, float elasticidad_) : SpringForceGenerator(k_, resting_length_, other_) {
	elasticidad = elasticidad_;
}

void GomaElastica::updateForce(Particle* particle, double t) {
	// Particle is the particle to apply the force
	Vector3 relativePosVector = other->getPos() - particle->getPos();

	// normalizee: Normalize de relativePosVector and returns its length
	const float length = relativePosVector.normalize();
	if (length > elasticidad) {
		const float delta_x = length - restingLength;

		Vector3 force = relativePosVector * delta_x * k;
		particle->addForce(force);
	}
}