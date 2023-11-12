#include "ParticleForceRegistry.h"
void ParticleForceRegistry::updateForces(double duration) {
	for (auto it = begin(); it != end(); ++it) {
		it->first->updateForce(it->second, duration);
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {
	insert({fg, p});
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
    auto it = begin();
    while (it != end()) {
        if (it->second == p) {
            it = erase(it); // Elimina el elemento y devuelve el siguiente iterador válido
        }
        else {
            ++it;
        }
    }
}