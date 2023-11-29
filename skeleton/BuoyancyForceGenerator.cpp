#include "BuoyancyForceGenerator.h"
BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, ParticleSystem* pS) {
	height = h;
	volume = V;
	liquidDensity = d;
	particleSys = pS;
	liquidParticle = new Particle(particleSys, { 0, height,0 }, { 0,0,0 }, { 0,0,0 }, 0, 4, { 0,0,1,1 }, 20, BOX, { 10, 1, 10 });
	particleSys->addParticle(liquidParticle);
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	float h = particle->getPos().y;
	float h0 = liquidParticle->getPos().y;

	Vector3 f(0, 0, 0);
	float inmersed = 0;
	if (h - h0 > height * 0.5) {
		inmersed = 0;
	}
	else if (h0 - h > height * 0.5) {
		inmersed = 1;
	}
	else {
		inmersed = (h0 - h) / height + 0.5;
	}
	f.y = liquidDensity * volume * inmersed * gravity;
	particle->addForce(f);
}