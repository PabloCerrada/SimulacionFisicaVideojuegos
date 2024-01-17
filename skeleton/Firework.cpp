#include "Firework.h"
Firework::Firework(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_, Vector4 color, int id_, ParticleForceRegistry* registering_) : Particle(pS, pos, dir, acel, masa_, tam_, color) {
	timeToExplode = 0.01;
	id = id_;
	registering = registering_;
}

void Firework::integrate(double t) {
	Particle::integrate(t);
	if (timeToExplode < time) {
		ParticleGenerator* gen;
		if (id == 0) gen = new SimpleParticleGenerator(particleSys, getPos(), registering);
		else if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5) gen = new GaussianParticleGenerator(particleSys, getPos(), id, registering);
		particleSys->addGenerator(gen);
		death = true;
	}
}

void Firework::explode() {

}