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

ParticleSystem* particleSys = nullptr;

ParticleForceRegistry* registering = nullptr;


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
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'B': { // Disparo normal
		Particle* p = new Particle(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1));
		particleSys->addParticle(p);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, p);
		ParticleDragGenerator* pdg = new ParticleDragGenerator(20, 0);
		registering->addRegistry(pdg, p);
		break;
	}
	case 'N': { // Disparo con viento hacia arriba masa 5
		Particle* p = new Particle(particleSys, Vector3(-50, 20, 0), Vector3(1, 0, 0) * 50, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1));
		particleSys->addParticle(p);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, p);
		ParticleDragGenerator* pdg = new ParticleDragGenerator(10, 0);
		registering->addRegistry(pdg, p);
		break;
	}
	case 'M': { // Disparo con viento hacia arriba masa 15
		Particle* p = new Particle(particleSys, Vector3(-50, 20, 0), Vector3(1, 0, 0) * 50, PxVec3(0, -9.8, 0), 15, 3, Vector4(1, 0, 0, 1));
		particleSys->addParticle(p);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, p);
		ParticleDragGenerator* pdg = new ParticleDragGenerator(10, 0);
		registering->addRegistry(pdg, p);
		break;
	}
	case 'G': { // Fuego artificial uniforme
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1), 0, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'H': { // Fuego artificial gaussiano
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(0, 1, 0, 1), 1, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'J': { // Fuego artificial gaussiano con paleta rosada
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(0, 0, 1, 1), 2, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'K': { // Hacia la derecha con viento hacia arriba
		Firework* f = new Firework(particleSys, GetCamera()->getEye(), GetCamera()->getDir() * 100, PxVec3(0, -9.8, 0), 5, 1.5, Vector4(0, 0, 1, 1), 3, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);
		break;
	}
	case 'I': { // Torbellino
		ParticulasAleatorias* pA = new ParticulasAleatorias(particleSys, registering);
		pA->crearTorbellino();
		break;
	}
	case 'O': { // Explosion
		ParticulasAleatorias* pA = new ParticulasAleatorias(particleSys, registering);
		pA->crearExplosion();
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