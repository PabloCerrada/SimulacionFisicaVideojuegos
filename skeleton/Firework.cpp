#include "Firework.h"
Firework::Firework(ParticleSystem* pS, const physx::PxVec3& pos, const physx::PxVec3& dir, const physx::PxVec3& acel, float masa_, float tam_) : Particle(pS, pos, dir, acel, masa_, tam_) {
	timeToExplode = 1;
}

void Firework::integrate(double t) {
	Particle::integrate(t);
	//cout << mPos.x << " " << mPos.y << " " << mPos.z << endl;
	if (timeToExplode < time) {
		SimpleParticleGenerator* gen = new SimpleParticleGenerator(particleSys, getPos());
		particleSys->addGenerator(gen);
		death = true;
	}
}

void Firework::explode() {

}