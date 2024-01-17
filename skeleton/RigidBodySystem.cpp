#include "RigidBodySystem.h"
RigidBodySystem::RigidBodySystem(RBForceRegistry* registering_, PxPhysics* gPhysics_, PxScene* gScene_) {
	registering = registering_;
	gPhysics = gPhysics_;
	gScene = gScene_;
	wind = new WindSFG(0, 0, Vector3(1, 0, 0));
}

RigidBodySystem::~RigidBodySystem() {
	auto it = rbList.begin();
	while (!rbList.empty() && it != rbList.end()) {
		auto aux = it;
		++aux;


		registering->deleteRBRegistry(*it);
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

		if ((*it) != gancho && (*it)->getDynamic() && !pegado) {
			if (gancho->getRB()->getWorldBounds().intersects((*it)->getRB()->getWorldBounds())) {
				pegado = true;
				rbPegado = (*it);
			}
		}

		if ((*it)->getDynamic() && (*it)->getPos().y < -50 && (*it)->getPos().x < -50 && (*it)->getPos().z > -355) {
			victoria = true;
			registering->deleteRBRegistry(*it);
			delete* it;
			rbList.erase(it);
		}

		if (pegado) {
			rbPegado->setPos(gancho->getPos() + Vector3(0, -30, 0));
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

RB* RigidBodySystem::createDynamicObject(Vector3 pos, int wx, int wy, int wz, Vector4 color, int id) { // id: 0 capsula, 1 gancho, 2 esfera, 3 Box
	PxRigidDynamic* newSolid = gPhysics->createRigidDynamic(PxTransform(pos));  
	newSolid->setLinearVelocity(PxVec3(0, 0, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });
	
	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	PxMaterial* gMaterial = gPhysics->createMaterial(10, 0, 0);
	PxShape* newShape;
	switch (id)
	{
	case 0:
		newShape = CreateShape(PxCapsuleGeometry(wx, wy), gMaterial);
		newSolid->setMass(10);
		newSolid->attachShape(*newShape);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 0.001);
		break;
	case 1:
		newShape = CreateShape(PxBoxGeometry(wx, wy, wz), gMaterial);
		newSolid->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true); // Gravedad deshabilitada
		newSolid->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true); // Al chocar no reacciona a las colisiones
		newSolid->attachShape(*newShape);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 0.001);
		
		break;
	case 2:
		newShape = CreateShape(PxSphereGeometry(wx), gMaterial);
		newSolid->attachShape(*newShape);
		newSolid->setMass(3);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 0.001);
		break;
	case 3:
		newShape = CreateShape(PxBoxGeometry(wx, wy, wz), gMaterial);
		newSolid->setMass(15);
		newSolid->attachShape(*newShape);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 0.001);
		break;
	default:
		break;
	}
	
	gScene->addActor(*newSolid);
	RenderItem* newItem = new RenderItem(newShape, newSolid, color);
	RB* rb = new RB(gPhysics, gScene, newItem, newSolid, newShape);
	addRB(rb);
	registering->addRegistry(wind, rb);
	return rb;
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
	createDynamicObject(Vector3(0, 0, -500), 20, 20, 20, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 3);
	createDynamicObject(Vector3(-100, 0, -600), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 0);
	createDynamicObject(Vector3(-100, 0, -500), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 0);
	createDynamicObject(Vector3(-50, 0, -550), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 2);
	createDynamicObject(Vector3(0, 0, -600), 20, 10, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 0);
	createDynamicObject(Vector3(0, 0, -400), 20, 15, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 0);
	createDynamicObject(Vector3(100, 0, -600), 20, 15, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 0);
	createDynamicObject(Vector3(100, 0, -500), 20, 20, 20, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 3);
	createDynamicObject(Vector3(100, 0, -400), 20, 20, 20, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 3);
	createDynamicObject(Vector3(50, 0, -450), 20, 0, 0, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 }, 2);
}

float RigidBodySystem::nRandom(int n1, int n2) {
	// Calcular el rango de números posibles
	int rango = n2 - n1 + 1;

	// Generar un número aleatorio dentro del rango
	return std::rand() % rango + n1;
}

void RigidBodySystem::despegar() {
	if (pegado) {
		setPegado(false);
		rbPegado->setDir(Vector3(0, -1, 0));
		rbPegado->setAngular(Vector3(0));
		rbPegado = nullptr;
	}
}

void RigidBodySystem::setWind(float k1, float k2, Vector3 d) {
	wind->setDrag(k1, k2);
	wind->setD(d);

	auto it = rbList.begin();
	while (!rbList.empty() && it != rbList.end()) {
		auto aux = it;
		++aux;

		if ((*it) != gancho && (*it) != anclaje && (*it) != rbPegado && (*it)->getDynamic() && k1 != 0) {
			(*it)->setPos((*it)->getPos() + Vector3(0, 10, 0));
		}


		it = aux;
	}
}