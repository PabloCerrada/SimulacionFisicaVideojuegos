#include "MuelleAncladoRB.h"
MuelleAncladoRB::MuelleAncladoRB(double k_, double resting_length_, const Vector3& anchorPos_, RigidBodySystem* rbS) : MuelleRB(k_, resting_length_,
	rbS->createDynamicObject(Vector3(0, 200, -500), 20, 2, 20, { 1, 0, 0, 1 }, 1)) {
}

MuelleAncladoRB::~MuelleAncladoRB() {

}