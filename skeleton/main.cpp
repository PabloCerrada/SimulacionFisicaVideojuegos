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

std::string display_text = "La maquina regalajuguetes";

std::string juguetes = "Juguetes restantes: 10";

std::string felicitacion = "";


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

Particle* pMuelle;
AnchoredSpringFG* as;

void congratulations() {
	int a = 10 - rigidBodySys->getNPeluches();
	if (a != 1) felicitacion = "Has ganado " + to_string(a) + " juguetes";
	else felicitacion = "Has ganado " + to_string(a) + " juguete";
	
}
void updateText() {
	int a = rigidBodySys->getNPeluches();
    juguetes = "Juguetes restantes: " + to_string(a);
}

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

	// Inicializar la semilla para obtener números realmente aleatorios
	std::srand(std::time(0));

	RBregistering = new RBForceRegistry();
	rigidBodySys = new RigidBodySystem(RBregistering, gPhysics, gScene);
	registering = new ParticleForceRegistry();
	particleSys = new ParticleSystem(registering);

	rigidBodySys->createScenario();
	// Iman
	pMuelle = new Particle(particleSys, Vector3(0, 200, -500), Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 3, Vector4(1, 0, 0, 1), -1, BOX, Vector3(20, 2, 20));
	particleSys->addParticle(pMuelle);
	as = new AnchoredSpringFG(0, 0, Vector3(0, 200, -500), particleSys);
	registering->addRegistry(as, pMuelle);
	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	rigidBodySys->update(t);
	if (rigidBodySys->getVictoria()) {
		congratulations();
		updateText();
		rigidBodySys->setVictoria(false);
	}
	RBregistering->updateForces(t);
	particleSys->update(t);
	registering->updateForces(t);
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

	delete rigidBodySys;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'T':
		as->setGanchoPos(as->getGanchoPos() + Vector3(0, 0, -1));
		pMuelle->setPos(pMuelle->getPos() + Vector3(0, 0, -1));
		break;
	case 'G':
		as->setGanchoPos(as->getGanchoPos() + Vector3(0, 0, 1));
		pMuelle->setPos(pMuelle->getPos() + Vector3(0, 0, 1));
		break;
	case 'F':
		as->setGanchoPos(as->getGanchoPos() + Vector3(-1, 0, 0));
		pMuelle->setPos(pMuelle->getPos() + Vector3(-1, 0, 0));
		break;
	case 'H':
		as->setGanchoPos(as->getGanchoPos() + Vector3(1, 0, 0));
		pMuelle->setPos(pMuelle->getPos() + Vector3(1, 0, 0));
		break;
	case 'Q':
		pMuelle->setPos(pMuelle->getPos() + Vector3(0, 1, 0));
		break;
	case 'E':
		pMuelle->setPos(pMuelle->getPos() + Vector3(0, -1, 0));
		break;
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