#include "Particle.h"
#include <ctype.h>
#include "foundation/PxMat33.h"

Particle::Particle(ParticleSystem* pS, const PxVec3& pos, const PxVec3& dir, const PxVec3&	acel, float masa_, float tam_) : time(0)
{
	particleSys = pS;
	mDir = dir;
	mAcel = acel;
	masa = masa_;
	tam = tam_;
	mTrans = new PxTransform(pos);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(tam)), mTrans, Vector4(255, 0, 0, 1));
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
	time += t;
	mTrans->p += mDir * t;
	mDir += mAcel * t;
	mDir *= pow(DAMPING, t);
}

float Particle::getTime() {
	return time;
}

bool Particle::getDeath() {
	return death;
}

//void Particle::moveConstVel(double t) { // MRU 
//	mTrans->p = mTrans->p + mDir * vel * t;
//}
//
//void Particle::moveAcelVel(double t) { // MRUA
//	mTrans->p += mDir * vel * t;
//	mDir += mAcel * t;
//	mDir *= pow(DAMPING, t);
//}
//
//void Particle::verticalShoot(double t) { // MRUA
//	mTrans->p += mDir * t - (1 / 2) * mGrav * pow(t, 2);
//	mDir += mGrav * t;
//	mDir *= pow(DAMPING, t);
//} // Cosas mias
