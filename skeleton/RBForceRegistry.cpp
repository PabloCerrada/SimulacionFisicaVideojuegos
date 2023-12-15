#include "RBForceRegistry.h"
void RBForceRegistry::updateForces(double duration) {
    for (auto it = begin(); it != end(); ++it) {
        it->first->updateForce(it->second, duration);
    }
}

void RBForceRegistry::addRegistry(SolidForceGenerator* fg, RB* rb) {
    insert({ fg, rb });
}

void RBForceRegistry::deleteRegistry(SolidForceGenerator* fg, RB* rb) {
    
}

void RBForceRegistry::deleteParticleRegistry(RB* rb) {
    
}