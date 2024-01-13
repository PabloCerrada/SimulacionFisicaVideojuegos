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

		(*it)->integrate(t);

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

void RigidBodySystem::createScenario() {
	createStaticScenario();
	createDynamicScenario();
}

void RigidBodySystem::createStaticObject(Vector3 pos, int wx, int wy, int wz, Vector4 color) {
	// Rigido de abajo
	PxRigidStatic* objeto = gPhysics->createRigidStatic(PxTransform(pos));
	PxShape* shape = CreateShape(PxBoxGeometry(wx, wy, wz));
	objeto->attachShape(*shape);
	gScene->addActor(*objeto);
	RenderItem* item = new RenderItem(shape, objeto, color);
	addRB(new RB(gPhysics, gScene, item, objeto));
}

void RigidBodySystem::createStaticScenario() {

	// Rigido de abajo
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, -150, -500 }));
	PxShape* shape1 = CreateShape(PxBoxGeometry(150, 50, 150));
	suelo->attachShape(*shape1);
	gScene->addActor(*suelo);
	RenderItem* item1 = new RenderItem(shape1, suelo, { 1, 0, 0, 1 });
	RB* r1 = new RB(gPhysics, gScene, item1, suelo);
	rigidBodySys->addRB(r1);

	// Palos
	PxRigidStatic* paloIzq = gPhysics->createRigidStatic(PxTransform({ -145, 0, -355 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(5, 200, 5));
	paloIzq->attachShape(*shape2);
	gScene->addActor(*paloIzq);
	RenderItem* item2 = new RenderItem(shape2, paloIzq, { 1, 0, 0, 1 });
	RB* r2 = new RB(gPhysics, gScene, item2, paloIzq);
	rigidBodySys->addRB(r2);

	PxRigidStatic* paloDch = gPhysics->createRigidStatic(PxTransform({ 145, 0, -355 }));
	PxShape* shape3 = CreateShape(PxBoxGeometry(5, 200, 5));
	paloDch->attachShape(*shape3);
	gScene->addActor(*paloDch);
	RenderItem* item3 = new RenderItem(shape3, paloDch, { 1, 0, 0, 1 });
	RB* r3 = new RB(gPhysics, gScene, item3, paloDch);
	rigidBodySys->addRB(r3);

	PxRigidStatic* paloIzqFondo = gPhysics->createRigidStatic(PxTransform({ -145, 0, -645 }));
	PxShape* shape4 = CreateShape(PxBoxGeometry(5, 200, 5));
	paloIzqFondo->attachShape(*shape4);
	gScene->addActor(*paloIzqFondo);
	RenderItem* item4 = new RenderItem(shape4, paloIzqFondo, { 1, 0, 0, 1 });
	RB* r4 = new RB(gPhysics, gScene, item4, paloIzqFondo);
	rigidBodySys->addRB(r4);

	PxRigidStatic* paloDchFondo = gPhysics->createRigidStatic(PxTransform({ 145, 0, -645 }));
	PxShape* shape5 = CreateShape(PxBoxGeometry(5, 200, 5));
	paloDchFondo->attachShape(*shape5);
	gScene->addActor(*paloDchFondo);
	RenderItem* item5 = new RenderItem(shape5, paloDchFondo, { 1, 0, 0, 1 });
	RB* r5 = new RB(gPhysics, gScene, item5, paloDchFondo);
	rigidBodySys->addRB(r5);

	PxRigidStatic* paloArribaFrente = gPhysics->createRigidStatic(PxTransform({ 0, 200, -355 }));
	PxShape* shape6 = CreateShape(PxBoxGeometry(150, 5, 5));
	paloArribaFrente->attachShape(*shape6);
	gScene->addActor(*paloArribaFrente);
	RenderItem* item6 = new RenderItem(shape6, paloArribaFrente, { 1, 0, 0, 1 });
	RB* r6 = new RB(gPhysics, gScene, item6, paloArribaFrente);
	rigidBodySys->addRB(r6);

	PxRigidStatic* paloArribaIzq = gPhysics->createRigidStatic(PxTransform({ -145, 200, -500 }));
	PxShape* shape7 = CreateShape(PxBoxGeometry(5, 5, 150));
	paloArribaIzq->attachShape(*shape7);
	gScene->addActor(*paloArribaIzq);
	RenderItem* item7 = new RenderItem(shape7, paloArribaIzq, { 1, 0, 0, 1 });
	RB* r7 = new RB(gPhysics, gScene, item7, paloArribaIzq);
	rigidBodySys->addRB(r7);

	PxRigidStatic* paloArribaDch = gPhysics->createRigidStatic(PxTransform({ 145, 200, -500 }));
	PxShape* shape8 = CreateShape(PxBoxGeometry(5, 5, 150));
	paloArribaDch->attachShape(*shape8);
	gScene->addActor(*paloArribaDch);
	RenderItem* item8 = new RenderItem(shape8, paloArribaDch, { 1, 0, 0, 1 });
	RB* r8 = new RB(gPhysics, gScene, item8, paloArribaDch);
	rigidBodySys->addRB(r8);

	PxRigidStatic* paloArribaFondo = gPhysics->createRigidStatic(PxTransform({ 0, 200, -645 }));
	PxShape* shape9 = CreateShape(PxBoxGeometry(150, 5, 5));
	paloArribaFondo->attachShape(*shape9);
	gScene->addActor(*paloArribaFondo);
	RenderItem* item9 = new RenderItem(shape9, paloArribaFondo, { 1, 0, 0, 1 });
	RB* r9 = new RB(gPhysics, gScene, item9, paloArribaFondo);
	rigidBodySys->addRB(r9);

	PxRigidStatic* tapaFondo = gPhysics->createRigidStatic(PxTransform({ 0, 50, -645 }));
	PxShape* shape10 = CreateShape(PxBoxGeometry(150, 150, 3));
	tapaFondo->attachShape(*shape10);
	gScene->addActor(*tapaFondo);
	if (DEBUG) RenderItem* item10 = new RenderItem(shape10, tapaFondo, { 0, 0, 0, 0 });
	RB* r10 = new RB(gPhysics, gScene, nullptr, tapaFondo);
	rigidBodySys->addRB(r10);

	PxRigidStatic* tapaIzq = gPhysics->createRigidStatic(PxTransform({ -145, 50, -500 }));
	PxShape* shape11 = CreateShape(PxBoxGeometry(3, 150, 150));
	tapaIzq->attachShape(*shape11);
	gScene->addActor(*tapaIzq);
	if (DEBUG) RenderItem* item11 = new RenderItem(shape11, tapaIzq, { 0, 0, 0, 0 });
	RB* r11 = new RB(gPhysics, gScene, nullptr, tapaIzq);
	rigidBodySys->addRB(r11);

	PxRigidStatic* tapaDch = gPhysics->createRigidStatic(PxTransform({ 145, 50, -500 }));
	PxShape* shape12 = CreateShape(PxBoxGeometry(3, 150, 150));
	tapaDch->attachShape(*shape12);
	gScene->addActor(*tapaDch);
	if (DEBUG) RenderItem* item11 = new RenderItem(shape12, tapaDch, { 0, 0, 0, 0 });
	RB* r12 = new RB(gPhysics, gScene, nullptr, tapaDch);
	rigidBodySys->addRB(r12);

	PxRigidStatic* troneraArribaFrente = gPhysics->createRigidStatic(PxTransform({ -95, 0, -355 }));
	PxShape* shape13 = CreateShape(PxBoxGeometry(50, 5, 5));
	troneraArribaFrente->attachShape(*shape13);
	gScene->addActor(*troneraArribaFrente);
	RenderItem* item13 = new RenderItem(shape13, troneraArribaFrente, { 1, 0, 0, 1 });
	RB* r13 = new RB(gPhysics, gScene, item13, troneraArribaFrente);
	rigidBodySys->addRB(r13);

	PxRigidStatic* troneraDchFrente = gPhysics->createRigidStatic(PxTransform({ -50, -50, -355 }));
	PxShape* shape14 = CreateShape(PxBoxGeometry(5, 50, 5));
	troneraDchFrente->attachShape(*shape14);
	gScene->addActor(*troneraDchFrente);
	RenderItem* item14 = new RenderItem(shape14, troneraDchFrente, { 1, 0, 0, 1 });
	RB* r14 = new RB(gPhysics, gScene, item14, troneraDchFrente);
	rigidBodySys->addRB(r14);

	PxRigidStatic* troneraArribaDch = gPhysics->createRigidStatic(PxTransform({ -50, 0, -405 }));
	PxShape* shape15 = CreateShape(PxBoxGeometry(5, 5, 50));
	troneraArribaDch->attachShape(*shape15);
	gScene->addActor(*troneraArribaDch);
	RenderItem* item15 = new RenderItem(shape15, troneraArribaDch, { 1, 0, 0, 1 });
	RB* r15 = new RB(gPhysics, gScene, item15, troneraArribaDch);
	rigidBodySys->addRB(r15);

	PxRigidStatic* troneraDchFondo = gPhysics->createRigidStatic(PxTransform({ -50, -50, -450 }));
	PxShape* shape16 = CreateShape(PxBoxGeometry(5, 50, 5));
	troneraDchFondo->attachShape(*shape16);
	gScene->addActor(*troneraDchFondo);
	RenderItem* item16 = new RenderItem(shape16, troneraDchFondo, { 1, 0, 0, 1 });
	RB* r16 = new RB(gPhysics, gScene, item16, troneraDchFondo);
	rigidBodySys->addRB(r16);

	PxRigidStatic* troneraArribaFondo = gPhysics->createRigidStatic(PxTransform({ -95, 0, -450 }));
	PxShape* shape17 = CreateShape(PxBoxGeometry(50, 5, 5));
	troneraArribaFondo->attachShape(*shape17);
	gScene->addActor(*troneraArribaFondo);
	RenderItem* item17 = new RenderItem(shape17, troneraArribaFondo, { 1, 0, 0, 1 });
	RB* r17 = new RB(gPhysics, gScene, item17, troneraArribaFondo);
	rigidBodySys->addRB(r17);

	PxRigidStatic* rampa = gPhysics->createRigidStatic(PxTransform({ -95, -80, -403 }));
	PxTransform p8(-95, -80, -403);
	p8.q = PxQuat(PxPi / 7, PxVec3(1, 0, 0));
	rampa->setGlobalPose(p8);
	PxShape* shape18 = CreateShape(PxBoxGeometry(45, 1, 50));
	rampa->attachShape(*shape18);
	gScene->addActor(*rampa);
	RenderItem* item18 = new RenderItem(shape18, rampa, { 1, 0, 0, 1 });
	RB* r18 = new RB(gPhysics, gScene, item18, rampa);
	rigidBodySys->addRB(r18);

	PxRigidStatic* tapaTroneraDch = gPhysics->createRigidStatic(PxTransform({ -50, -50, -400 }));
	PxShape* shape19 = CreateShape(PxBoxGeometry(3, 50, 50));
	tapaTroneraDch->attachShape(*shape19);
	gScene->addActor(*tapaTroneraDch);
	RenderItem* item19 = new RenderItem(shape19, tapaTroneraDch, { 1, 0, 0, 1 });
	RB* r19 = new RB(gPhysics, gScene, item19, tapaTroneraDch);
	rigidBodySys->addRB(r19);

	PxRigidStatic* tapaTroneraFondo = gPhysics->createRigidStatic(PxTransform({ -95, -50, -450 }));
	PxShape* shape20 = CreateShape(PxBoxGeometry(50, 50, 3));
	tapaTroneraFondo->attachShape(*shape20);
	gScene->addActor(*tapaTroneraFondo);
	RenderItem* item20 = new RenderItem(shape20, tapaTroneraFondo, { 1, 0, 0, 1 });
	RB* r20 = new RB(gPhysics, gScene, item20, tapaTroneraFondo);
	rigidBodySys->addRB(r20);

	PxRigidStatic* tapaFrenteDch = gPhysics->createRigidStatic(PxTransform({ 50, 50, -355 }));
	PxShape* shape21 = CreateShape(PxBoxGeometry(100, 150, 3));
	tapaFrenteDch->attachShape(*shape21);
	gScene->addActor(*tapaFrenteDch);
	if (DEBUG) RenderItem* item21 = new RenderItem(shape21, tapaFrenteDch, { 0, 0, 0, 0 });
	RB* r21 = new RB(gPhysics, gScene, nullptr, tapaFrenteDch);
	rigidBodySys->addRB(r21);

	PxRigidStatic* tapaFrenteIzq = gPhysics->createRigidStatic(PxTransform({ -95, 100, -355 }));
	PxShape* shape22 = CreateShape(PxBoxGeometry(50, 100, 3));
	tapaFrenteIzq->attachShape(*shape22);
	gScene->addActor(*tapaFrenteIzq);
	if (DEBUG) RenderItem* item22 = new RenderItem(shape22, tapaFrenteIzq, { 0, 0, 0, 0 });
	RB* r22 = new RB(gPhysics, gScene, nullptr, tapaFrenteIzq);
	rigidBodySys->addRB(r22);
}

void RigidBodySystem::createDynamicScenario() {
	PxRigidDynamic* newSolid = gPhysics->createRigidDynamic(PxTransform({ 0, 0, -500 }));
	newSolid->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid->attachShape(*newShape);
	PxRigidBodyExt::updateMassAndInertia(*newSolid, 10);
	gScene->addActor(*newSolid);
	RenderItem* newItem = new RenderItem(newShape, newSolid, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r1 = new RB(gPhysics, gScene, newItem, newSolid);
	rigidBodySys->addRB(r1);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid2 = gPhysics->createRigidDynamic(PxTransform({ -100, 0, -600 }));
	newSolid->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape2 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid2->attachShape(*newShape2);
	PxRigidBodyExt::updateMassAndInertia(*newSolid2, 10);
	gScene->addActor(*newSolid2);
	RenderItem* newItem2 = new RenderItem(newShape2, newSolid2, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r2 = new RB(gPhysics, gScene, newItem2, newSolid2);
	rigidBodySys->addRB(r2);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid3 = gPhysics->createRigidDynamic(PxTransform({ -100, 0, -500 }));
	newSolid3->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape3 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid3->attachShape(*newShape3);
	PxRigidBodyExt::updateMassAndInertia(*newSolid3, 10);
	gScene->addActor(*newSolid3);
	RenderItem* newItem3 = new RenderItem(newShape3, newSolid3, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r3 = new RB(gPhysics, gScene, newItem3, newSolid3);
	rigidBodySys->addRB(r3);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid4 = gPhysics->createRigidDynamic(PxTransform({ -50, 0, -550 }));
	newSolid4->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape4 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid4->attachShape(*newShape4);
	PxRigidBodyExt::updateMassAndInertia(*newSolid4, 10);
	gScene->addActor(*newSolid4);
	RenderItem* newItem4 = new RenderItem(newShape4, newSolid4, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r4 = new RB(gPhysics, gScene, newItem4, newSolid4);
	rigidBodySys->addRB(r4);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid5 = gPhysics->createRigidDynamic(PxTransform({ 0, 0, -600 }));
	newSolid5->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape5 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid5->attachShape(*newShape5);
	PxRigidBodyExt::updateMassAndInertia(*newSolid5, 10);
	gScene->addActor(*newSolid5);
	RenderItem* newItem5 = new RenderItem(newShape5, newSolid5, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r5 = new RB(gPhysics, gScene, newItem5, newSolid5);
	rigidBodySys->addRB(r5);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid6 = gPhysics->createRigidDynamic(PxTransform({ 0, 0, -400 }));
	newSolid6->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape6 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid6->attachShape(*newShape6);
	PxRigidBodyExt::updateMassAndInertia(*newSolid6, 10);
	gScene->addActor(*newSolid6);
	RenderItem* newItem6 = new RenderItem(newShape6, newSolid6, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r6 = new RB(gPhysics, gScene, newItem6, newSolid6);
	rigidBodySys->addRB(r6);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid7 = gPhysics->createRigidDynamic(PxTransform({ 100, 0, -600 }));
	newSolid7->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape7 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid7->attachShape(*newShape7);
	PxRigidBodyExt::updateMassAndInertia(*newSolid7, 10);
	gScene->addActor(*newSolid7);
	RenderItem* newItem7 = new RenderItem(newShape7, newSolid7, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r7 = new RB(gPhysics, gScene, newItem7, newSolid7);
	rigidBodySys->addRB(r7);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid8 = gPhysics->createRigidDynamic(PxTransform({ 100, 0, -500 }));
	newSolid8->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape8 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid8->attachShape(*newShape8);
	PxRigidBodyExt::updateMassAndInertia(*newSolid8, 10);
	gScene->addActor(*newSolid8);
	RenderItem* newItem8 = new RenderItem(newShape8, newSolid8, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r8 = new RB(gPhysics, gScene, newItem8, newSolid8);
	rigidBodySys->addRB(r8);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid9 = gPhysics->createRigidDynamic(PxTransform({ 100, 0, -400 }));
	newSolid9->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape9 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid9->attachShape(*newShape9);
	PxRigidBodyExt::updateMassAndInertia(*newSolid9, 10);
	gScene->addActor(*newSolid9);
	RenderItem* newItem9 = new RenderItem(newShape9, newSolid9, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r9 = new RB(gPhysics, gScene, newItem9, newSolid9);
	rigidBodySys->addRB(r9);

	// Rigidbody dinamico
	PxRigidDynamic* newSolid10 = gPhysics->createRigidDynamic(PxTransform({ 50, 0, -450 }));
	newSolid10->setLinearVelocity(PxVec3(0, -30, 0));
	//newSolid->setAngularVelocity({ 0,10,0 });

	//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
	//PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* newShape10 = CreateShape(PxCapsuleGeometry(20, 10));
	newSolid10->attachShape(*newShape10);
	PxRigidBodyExt::updateMassAndInertia(*newSolid10, 10);
	gScene->addActor(*newSolid10);
	RenderItem* newItem10 = new RenderItem(newShape10, newSolid10, { nRandom(0, 100) / 100, nRandom(0, 100) / 100, nRandom(0, 100) / 100, 1 });

	RB* r10 = new RB(gPhysics, gScene, newItem10, newSolid10);
	rigidBodySys->addRB(r10);
}