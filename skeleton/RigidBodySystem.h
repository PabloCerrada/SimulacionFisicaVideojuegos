#include "RenderUtils.hpp"
#include "RB.h"
#include <list>
#include "RBForceRegistry.h"
using namespace physx;
using namespace std;

class RigidBodySystem {
private:
	RBForceRegistry* registering;
	std::list<RB*> rbList;
	PxPhysics* gPhysics = nullptr;
	PxScene* gScene = nullptr;

	void createStaticScenario();
	void createDynamicScenario();
public:
	RigidBodySystem(RBForceRegistry* registering_, PxPhysics* gPhysics_, PxScene* gScene_);
	~RigidBodySystem();
	void addRB(RB* r);
	void update(double t);
	void createScenario();
	void createStaticObject(Vector3 pos, int wx, int wy, int wz, Vector4 color);
	void createDynamicObject();
	int getNPeluches();
};