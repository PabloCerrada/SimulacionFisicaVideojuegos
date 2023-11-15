#include "Particle.h"
#include <ctype.h>
#include "foundation/PxMat33.h"

Particle::Particle(ParticleSystem* pS, const PxVec3& pos, const PxVec3& dir, const PxVec3&	acel, float masa_, float tam_, Vector4 color) : time(0)
{
	particleSys = pS;
	mDir = dir;
	mAcel = acel;
	masa = masa_;
	if (masa != 0) {
		invMasa = 1.0 / masa;
	}
	tam = tam_;
	force = { 0, 0, 0 };
	mTrans = new PxTransform(pos);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(tam)), mTrans, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete mTrans;
}

PxVec3 Particle::getPos() const
{
	return mTrans->p;
}

PxVec3 Particle::getDir() const
{
	return mDir;
}
void Particle::setPos(PxVec3 newPos) {
	mTrans->p = newPos;
}

void Particle::integrate(double t) { // MRU 
	update(t);
	time += t;
	if (timeOfLife < time) death = true;
	/*mTrans->p += mDir * t;
	mDir += mAcel * t;
	mDir *= pow(DAMPING, t);*/
}

float Particle::getTime() {
	return time;
}

bool Particle::getDeath() {
	return death;
}

void Particle::addForce(Vector3 f) {
	force += f;
}

void Particle::clearForce() {
	force *= 0;
}

bool Particle::update(double delta_t) {
	// Semi-implicit Euler algorithm
	// Get the accel considering the force accum
	Vector3 resulting_accel = force * invMasa;
	mDir += resulting_accel * delta_t; // Ex. 1.3 --> add acceleration
	mDir *= powf(DAMPING, delta_t); // Exercise 1.3 --> adddamping
	mTrans->p += mDir * delta_t;
	_remaining_time -= delta_t;
	// Clear accum
	clearForce();

	return _remaining_time > 0.0;
}

