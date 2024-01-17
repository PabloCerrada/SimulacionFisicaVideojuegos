#pragma once
#include "RenderUtils.hpp"
#include "RB.h"
#include <list>
#include "RBForceRegistry.h"
#include "WindSFG.h"
using namespace physx;
using namespace std;

class RigidBodySystem {
private:
	bool victoria = false, pegado = false;
	RBForceRegistry* registering;
	std::list<RB*> rbList;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;
	RB* gancho;
	RB* anclaje;
	RB* rbPegado = nullptr;
	WindSFG* wind;

	void createStaticScenario();
	void createDynamicScenario();
	inline void setPegado(bool b) { pegado = b; }
public:
	RigidBodySystem(RBForceRegistry* registering_, PxPhysics* gPhysics_, PxScene* gScene_);
	~RigidBodySystem();
	void addRB(RB* r);
	void update(double t);
	void createScenario();
	void createStaticObject(Vector3 pos, int wx, int wy, int wz, Vector4 color, bool transparente);
	RB* createDynamicObject(Vector3 pos, int wx, int wy, int wz, Vector4 color, int id);
	int getNPeluches();
	float nRandom(int n1, int n2);

	inline void setVictoria(bool newVic) { victoria = newVic; }
	inline bool getVictoria() { return victoria; }

	inline void setGancho(RB* rb) { gancho = rb; }
	inline void setAnclaje(RB* rb) { anclaje = rb; }

	void setWind(float k1, float k2, Vector3 d);
	void despegar();
};