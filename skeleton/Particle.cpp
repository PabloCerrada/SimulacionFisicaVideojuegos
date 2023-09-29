#include "Particle.h"
#include <ctype.h>
#include "foundation/PxMat33.h"

using namespace physx;

Particle::Particle(const PxVec3& pos, const PxVec3& dir, const PxVec3&	acel, float masa_)
{
	mPos = pos;
	mDir = dir;
	mAcel = acel;
	masa = masa_;
	mTrans = new PxTransform(mPos);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(2)), mTrans, Vector4(255, 0, 0, 1));
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
	mTrans->p += mDir * t;
	mDir += mAcel * t;
	mDir *= pow(DAMPING, t);
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
