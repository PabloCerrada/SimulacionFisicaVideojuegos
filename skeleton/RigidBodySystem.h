#include "RenderUtils.hpp"
#include "RB.h"
#include <list>
#include "RBForceRegistry.h"
using namespace physx;
using namespace std;

class RigidBodySystem {
private:
	bool victoria = false;
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
	void createStaticObject(Vector3 pos, int wx, int wy, int wz, Vector4 color, bool transparente);
	void createDynamicObject(Vector3 pos, int wx, int wy, int wz, Vector4 color);
	int getNPeluches();
	float nRandom(int n1, int n2);

	inline void setVictoria(bool newVic) { victoria = newVic; }
	inline bool getVictoria() { return victoria; }
};