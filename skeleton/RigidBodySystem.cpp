#include "RigidBodySystem.h"
RigidBodySystem::RigidBodySystem(RBForceRegistry* registering_, PxPhysics* gPhysics_, PxScene* gScene_) {
	registering = registering_;
	gPhysics = gPhysics_;
	gScene = gScene_;
}

RigidBodySystem::~RigidBodySystem() {
	auto it = rbList.begin();
	while (!rbList.empty() && it != rbList.end()) {
		auto aux = it;
		++aux;

		registering->deleteParticleRegistry(*it);
		delete* it;
		rbList.erase(it);

		it = aux;
	}
}

void RigidBodySystem::addRB(RB* r) {
	rbList.push_back(r);
}

void RigidBodySystem::update(double t) {
	auto it = rbList.begin();
	while (!rbList.empty() && it != rbList.end()) {
		auto aux = it;
		++aux;

		if ((*it)->getDynamic() && (*it)->getPos().y < -50 && (*it)->getPos().x < -50 && (*it)->getPos().z > -355) {
			victoria = true;
			registering->deleteParticleRegistry(*it);
			delete* it;
			rbList.erase(it);
		}

		it = aux;
	}
}

int RigidBodySystem::getNPeluches() {
	int n = 0;
	auto it = rbList.begin();
	while (!rbList.empty() && it != rbList.end()) {
		auto aux = it;
		++aux;

		if ((*it)->getInvMss() != 0) n++;

		it = aux;
	}
	return n;
}

void RigidBodySystem::createScenario() { // Limites caja (-100, + 100) en x (-600, -400) en z (-100 y -400 es la tronera)
	createStaticScenario();
	createDynamicScenario();
}

void RigidBodySystem::createStaticObject(Vector3 pos, int wx, int wy, int wz, Vector4 color, bool transparente) {
	// Rigido de abajo
	PxRigidStatic* objeto = gPhysics->createRigidStatic(PxTransform(pos));
	PxShape* shape = CreateShape(PxBoxGeometry(wx, wy, wz));
	objeto->attachShape(*shape);
	gScene->addActor(*objeto);

	if (transparente) {
		addRB(new RB(gPhysics, gScene, nullptr, objeto, shape));
	}
	else {
		RenderItem* item = new RenderItem(shape, objeto, color);
		addRB(new RB(gPhysics, gScene, item, objeto, shape));
	}
	
}

void RigidBodySystem::createDynamicObject(Vector3 pos, int wx, int wy, int wz, Vector4 color) {
	PxRigidDynamic* newSolid = gPhysics->createRigidDynamic(PxTransform(pos));
	newSolid->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape = CreateShape(PxCapsuleGeometry(wx, wy));
	newSolid->attachShape(*newShape);
	PxRigidBodyExt::updateMassAndInertia(*newSolid, 10);
	gScene->addActor(*newSolid);
	RenderItem* newItem = new RenderItem(newShape, newSolid, color);

	addRB(new RB(gPhysics, gScene, newItem, newSolid, newShape));
}

void RigidBodySystem::createStaticScenario() {

	// Rigido abajo
	createStaticObject(Vector3(0, -150, -500), 150, 50, 150, Vector4(1, 0, 0, 1), false); // Suelo

	// Palos
	createStaticObject(Vector3(-145, 0, -355), 5, 200, 5, Vector4(1, 0, 0, 1), false); // PaloIzq
	createStaticObject(Vector3(145, 0, -355), 5, 200, 5, Vector4(1, 0, 0, 1), false); // PaloDch
	createStaticObject(Vector3(-145, 0, -645), 5, 200, 5, Vector4(1, 0, 0, 1), false); // PaloIzqFondo
	createStaticObject(Vector3(145, 0, -645), 5, 200, 5, Vector4(1, 0, 0, 1), false); // PaloDchFondo

	createStaticObject(Vector3(0, 200, -355), 150, 5, 5, Vector4(1, 0, 0, 1), false); // PaloArribaFrente
	createStaticObject(Vector3(-145, 200, -500), 5, 5, 150, Vector4(1, 0, 0, 1), false); // PaloArribaIzq
	createStaticObject(Vector3(145, 200, -500), 5, 5, 150, Vector4(1, 0, 0, 1), false); // PaloArribaDch
	createStaticObject(Vector3(0, 200, -645), 150, 5, 5, Vector4(1, 0, 0, 1), false); // PaloArribaFondo

	// Tapas y tronera
	createStaticObject(Vector3(0, 50, -645), 150, 150, 3, Vector4(0, 0, 0, 1), true); // tapaFondo
	createStaticObject(Vector3(-145, 50, -500), 3, 150, 150, Vector4(0, 0, 0, 1), true); // tapaIzq
	createStaticObject(Vector3(145, 50, -500), 3, 150, 150, Vector4(0, 0, 0, 1), true); // tapaDch
	createStaticObject(Vector3(-95, 0, -355), 50, 5, 5, Vector4(1, 0, 0, 1), false); // troneraArribaFrente
	createStaticObject(Vector3(-50, -50, -355), 5, 50, 5, Vector4(1, 0, 0, 1), false); // troneraDchFrente

	createStaticObject(Vector3(-50, 0, -405), 5, 5, 50, Vector4(1, 0, 0, 1), false); // troneraArribaDch
	createStaticObject(Vector3(-50, -50, -450), 5, 50, 5, Vector4(1, 0, 0, 1), false); // troneraDchFondo
	createStaticObject(Vector3(-95, 0, -450), 50, 5, 5, Vector4(1, 0, 0, 1), false); // troneraArribaFondo

	createStaticObject(Vector3(-50, -50, -400), 3, 50, 50, Vector4(1, 0, 0, 1), false); // tapaTroneraDch
	createStaticObject(Vector3(-95, -50, -450), 50, 50, 3, Vector4(1, 0, 0, 1), false); // tapaTroneraFondo

	createStaticObject(Vector3(50, 50, -355), 100, 150, 3, Vector4(0, 0, 0, 1), true); // tapaFrenteDch
	createStaticObject(Vector3(-95, 100, -355), 50, 100, 3, Vector4(0, 0, 0, 1), true); // tapaFrenteIzq

	PxRigidStatic* rampa = gPhysics->createRigidStatic(PxTransform({ -95, -80, -403 }));
	PxTransform p8(-95, -80, -403);
	p8.q = PxQuat(PxPi / 7, PxVec3(1, 0, 0));
	rampa->setGlobalPose(p8);
	PxShape* shape = CreateShape(PxBoxGeometry(45, 1, 50));
	rampa->attachShape(*shape);
	gScene->addActor(*rampa);
	RenderItem* item = new RenderItem(shape, rampa, { 1, 0, 0, 1 });
	addRB(new RB(gPhysics, gScene, item, rampa, shape));
}

void RigidBodySystem::createDynamicScenario() {
	createDynamicObject(Vector3(0, 0, -500), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(-100, 0, -600), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(-100, 0, -500), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(-50, 0, -550), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(0, 0, -600), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(0, 0, -400), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(100, 0, -600), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(100, 0, -500), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(100, 0, -400), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
	createDynamicObject(Vector3(-100, 0, -400), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });
}

float RigidBodySystem::nRandom(int n1, int n2) {
	// Calcular el rango de números posibles
	int rango = n2 - n1 + 1;

	// Generar un número aleatorio dentro del rango
	return std::rand() % rango + n1;
}