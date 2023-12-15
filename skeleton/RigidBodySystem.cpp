#include "RigidBodySystem.h"
RigidBodySystem::RigidBodySystem(RBForceRegistry* registering_) {
	registering = registering_;
}

RigidBodySystem::~RigidBodySystem() {
	
}

void RigidBodySystem::addRB(RB* r) {
	rbList.push_back(r);
}

void RigidBodySystem::update(double t) {
	auto it = rbList.begin();
	while (!rbList.empty() && it != rbList.end()) {
		auto aux = it;
		++aux;

		(*it)->integrate(t);

		it = aux;
	}
}