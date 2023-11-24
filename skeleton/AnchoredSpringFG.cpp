#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k_, double resting_length_, const Vector3& anchorPos_) : SpringForceGenerator(k_, resting_length_, nullptr) {
	other = new Particle(particleSys, anchorPos_, { 0,0,0 }, { 0,0,0 }, 5, 2, { 1,0,0,1 });
}

AnchoredSpringFG::~AnchoredSpringFG() {
	delete other;
}