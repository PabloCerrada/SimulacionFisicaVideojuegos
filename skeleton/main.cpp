#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "SimpleParticleGenerator.h"
#include "ParticleSystem.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "TorbellinoGenerator.h"
#include "ExplosionGenerator.h"
#include "ParticulasAleatorias.h"
#include "AnchoredSpringFG.h"
#include "GomaElastica.h"
#include "BuoyancyForceGenerator.h"
#include "RigidBodySystem.h"
#include "RBForceRegistry.h"
#include "WindSFG.h"
#include <list>	

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

ParticleForceRegistry* registering = nullptr;
ParticleSystem* particleSys = nullptr;
RigidBodySystem* rigidBodySys = nullptr;
RBForceRegistry* RBregistering = nullptr;
AnchoredSpringFG* as = nullptr;
Particle* pMuelle = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // To detect trash

	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	registering = new ParticleForceRegistry();
	particleSys = new ParticleSystem(registering);
	RBregistering = new RBForceRegistry();
	rigidBodySys = new RigidBodySystem(RBregistering);

	// RigidBody estatico
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);

	RenderItem* item = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });

	RB* r = new RB(gPhysics, gScene, item, suelo);
	rigidBodySys->addRB(r);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	particleSys->update(t);
	rigidBodySys->update(t);
	registering->updateForces(t);
	RBregistering->updateForces(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'Q': { // Disparo normal
		Particle* p = new Particle(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1));
		particleSys->addParticle(p);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, p);
		ParticleDragGenerator* pdg = new ParticleDragGenerator(20, 0);
		registering->addRegistry(pdg, p);
		break;
	}
	case 'E': { // Disparo con viento hacia arriba masa 5
		Particle* p = new Particle(particleSys, Vector3(-50, 20, 0), Vector3(1, 0, 0) * 50, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1));
		particleSys->addParticle(p);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, p);
		ParticleDragGenerator* pdg = new ParticleDragGenerator(10, 0);
		registering->addRegistry(pdg, p);
		break;
	}
	case 'R': { // Disparo con viento hacia arriba masa 15
		Particle* p = new Particle(particleSys, Vector3(-50, 20, 0), Vector3(1, 0, 0) * 50, PxVec3(0, -9.8, 0), 15, 3, Vector4(1, 0, 0, 1));
		particleSys->addParticle(p);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, p);
		ParticleDragGenerator* pdg = new ParticleDragGenerator(10, 0);
		registering->addRegistry(pdg, p);
		break;
	}
	case 'T': { // Fuego artificial uniforme
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1), 0, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'Y': { // Fuego artificial gaussiano
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(0, 1, 0, 1), 1, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'U': { // Fuego artificial gaussiano con paleta rosada
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(0, 0, 1, 1), 2, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'I': { // Hacia la derecha con viento hacia arriba
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(0, 0, 1, 1), 3, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'O': { // Torbellino
		ParticulasAleatorias* pA = new ParticulasAleatorias(particleSys, registering);
		pA->crearTorbellino();
		break;
	}
	case 'P': { // Explosion
		ParticulasAleatorias* pA = new ParticulasAleatorias(particleSys, registering);
		pA->crearExplosion();
		break;
	}
	case 'F': { // DemoMuelles
		particleSys->generateSpringDemo();
		break;
	}
	case 'G': { // DemoMuelles
		particleSys->generateSpringAnchoredDemo();
		break;
	}
	case 'H': { // Muelle Estático
		pMuelle = new Particle(particleSys, Vector3(0, 70, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 3, Vector4(1, 0, 0, 1), 40);
		particleSys->addParticle(pMuelle);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, pMuelle);
		as = new AnchoredSpringFG(50, 20, Vector3(30, 70, 0), particleSys);
		registering->addRegistry(as, pMuelle);
		break;
	}
	case 'J': { // Particulas unidas con muelle (GomaElastica)
		// First one standard spring uniting 2 particles
		Particle* p1 = new Particle(particleSys, { -20, 40, 0 }, { 0,0,0 }, { 0,0,0 }, 1, 3, Vector4(1, 0, 0, 1), 20);
		particleSys->addParticle(p1);
		Particle* p2 = new Particle(particleSys, { 20, 40, 0 }, { 0,0,0 }, { 0,0,0 }, 1, 3, Vector4(1, 1, 0, 1), 20);
		particleSys->addParticle(p2);
		GomaElastica* f1 = new GomaElastica(5, 0, p2, 5);
		registering->addRegistry(f1, p1);
		GravityForceGenerator* gfg1 = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(gfg1, p1);
		GomaElastica* f2 = new GomaElastica(5, 0, p1, 5);
		registering->addRegistry(f2, p2);
		GravityForceGenerator* gfg2 = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(gfg2, p2);
		ParticleDragGenerator* pdg1 = new ParticleDragGenerator(10, 0);
		registering->addRegistry(pdg1, p1);
		break;
	}
	case 'K': { // Flotacion
		Particle* p = new Particle(particleSys, { 0, 10, 0 }, { 0,0,0 }, { 0,0,0 }, 5, 3, Vector4(1, 0, 0, 1), 20, BOX, {3, 5, 3});
		particleSys->addParticle(p);
		GravityForceGenerator* gfg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(gfg, p);
		BuoyancyForceGenerator* bfg = new BuoyancyForceGenerator(0, 20, 1, particleSys);
		registering->addRegistry(bfg, p);
		break;
	}
	case 'L': {
		// Rigidbody dinamico
		PxRigidDynamic* newSolid = gPhysics->createRigidDynamic(PxTransform({ -70,200,-70 }));
		newSolid->setLinearVelocity({ 0,5,0 });
		newSolid->setAngularVelocity({ 0,0,0 });
		PxShape* newShape = CreateShape(PxBoxGeometry(5, 5, 5));
		newSolid->attachShape(*newShape);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 0.15);
		gScene->addActor(*newSolid);

		RenderItem* newItem = new RenderItem(newShape, newSolid, { 0, 0, 0, 1 });

		RB* r2 = new RB(gPhysics, gScene, newItem, newSolid);
		rigidBodySys->addRB(r2);
		break;
	}
	case 'Z': { // Disparo RB normal con viento
		// Rigidbody dinamico
		PxRigidDynamic* newSolid = gPhysics->createRigidDynamic(PxTransform({ GetCamera()->getEye() }));
		newSolid->setLinearVelocity(GetCamera()->getDir() * 70);
		newSolid->setAngularVelocity({ 0,0,0 });
		PxShape* newShape = CreateShape(PxCapsuleGeometry(2, 1));
		newSolid->attachShape(*newShape);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 0.15);
		gScene->addActor(*newSolid);

		RenderItem* newItem = new RenderItem(newShape, newSolid, { 0, 0, 0, 1 });

		RB* r2 = new RB(gPhysics, gScene, newItem, newSolid);
		rigidBodySys->addRB(r2);
		WindSFG* wind = new WindSFG(10, 0);
		RBregistering->addRegistry(wind, r2);
		break;
	}
	case 'X': { // Disparo RB con Angular velocity, material y mas masa, y viento
		// Rigidbody dinamico
		PxRigidDynamic* newSolid = gPhysics->createRigidDynamic(PxTransform({ GetCamera()->getEye() }));
		newSolid->setLinearVelocity(GetCamera()->getDir() * 70);
		newSolid->setAngularVelocity({ 0,10,0 });

		//PxMaterial* gMaterial = gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
		PxMaterial* gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

		PxShape* newShape = CreateShape(PxCapsuleGeometry(2, 1), gMaterial);
		newSolid->attachShape(*newShape);
		PxRigidBodyExt::updateMassAndInertia(*newSolid, 1);
		gScene->addActor(*newSolid);

		
		RenderItem* newItem = new RenderItem(newShape, newSolid, { 0, 0, 0, 1 });

		RB* r2 = new RB(gPhysics, gScene, newItem, newSolid);
		rigidBodySys->addRB(r2);
		WindSFG* wind = new WindSFG(10, 0);
		RBregistering->addRegistry(wind, r2);
		break;
	}
	case 'B': { // Viento afecta a la particula del muelle estático
		if (pMuelle != nullptr) {
			ParticleDragGenerator* pdg = new ParticleDragGenerator(10, 0);
			registering->addRegistry(pdg, pMuelle);
		}
		break;
	}
	case 'N': { // Resta variable K del muelle estático
		if (as != nullptr) as->setK(as->getK() - 1);
		break;
	}
	case 'M': { // Suma variable K del muelle estático
		if (as != nullptr) as->setK(as->getK() + 1);
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}