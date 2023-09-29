#include "Particle.h"
#include <ctype.h>
#include "foundation/PxMat33.h"

using namespace physx;

Particle::Particle(const PxVec3& pos, const PxVec3& dir, float vel_)
{
	vel = vel_;
	mPos = pos;
	mDir = dir;
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
	return mPos;
}

PxVec3 Particle::getDir() const
{
	return mDir;
}
void Particle::setPos(PxVec3 newPos) {
	mTrans->p = newPos;
}
void Particle::setVel(float newVel) {
	vel = newVel;
}
void Particle::moveConstVel(double t) {
	mTrans->p = mTrans->p + mDir * vel * t;
}
