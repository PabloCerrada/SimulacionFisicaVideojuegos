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
public:
	RigidBodySystem(RBForceRegistry* registering_);
	~RigidBodySystem();
	void addRB(RB* r);
	void update(double t);
};