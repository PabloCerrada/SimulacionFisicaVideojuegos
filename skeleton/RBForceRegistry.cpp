#include "RBForceRegistry.h"
void RBForceRegistry::updateForces(double duration) {
    for (auto it = begin(); it != end(); ++it) {
        it->first->updateForce(it->second, duration);
    }
}

void RBForceRegistry::addRegistry(SolidForceGenerator* fg, RB* rb) {
    insert({ fg, rb });
}


void RBForceRegistry::deleteRBRegistry(RB* rb) {
	auto it = begin();
	while (it != end()) {
		if (it->second != rb) {
			it++;
		}
		else {
			it = this->erase(it);
		}
	}
}