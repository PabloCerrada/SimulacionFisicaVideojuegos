#include "ParticleForceRegistry.h"
void ParticleForceRegistry::updateForces(double duration) {
	for (auto it = begin(); it != end(); ++it) {
		it->first->updateForce(it->second, duration);
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {
	insert({fg, p});
}

void ParticleForceRegistry::deleteRegistry(ForceGenerator* fg, Particle* p) {
    bool eliminado = false;
    auto it = begin();
    while (!eliminado && it != end()) {
        if ((*it).second == p) {
            erase(it);
            eliminado = true;
        }
    }
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
    auto it = begin();
    while (it != end()) {
        if (it->second == p) {
            delete(it->first);
            it = erase(it); // Elimina el elemento y devuelve el siguiente iterador válido
        }
        else {
            ++it;
        }
    }
}