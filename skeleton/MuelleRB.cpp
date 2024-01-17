#include "MuelleRB.h"
MuelleRB::MuelleRB(double k_, double resting_length_, RB* rb) {
	k = k_;
	restingLength = resting_length_;
	other = rb;
}

void MuelleRB::updateForce(RB* rb, double t) {
	// Particle is the particle to apply the force
	Vector3 relativePosVector = other->getPos() - rb->getPos();

	// normalizee: Normalize de relativePosVector and returns its length
	const float length = relativePosVector.normalize();
	const float delta_x = length - restingLength;

	Vector3 force = relativePosVector * delta_x * k;
	rb->addForce(force);
}