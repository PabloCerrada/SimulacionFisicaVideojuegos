#include "Firework.h"
Firework::Firework(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_, Vector4 color, int id_) : Particle(pS, pos, dir, acel, masa_, tam_, color) {
	timeToExplode = 1;
	id = id_;
}

void Firework::integrate(double t) {
	Particle::integrate(t);
	if (timeToExplode < time) {
		ParticleGenerator* gen;
		if (id == 0) gen = new SimpleParticleGenerator(particleSys, getPos());
		else if (id == 1 || id == 2 || id == 3) gen = new GaussianParticleGenerator(particleSys, getPos(), id);
		particleSys->addGenerator(gen);
		death = true;
	}
}

void Firework::explode() {

}