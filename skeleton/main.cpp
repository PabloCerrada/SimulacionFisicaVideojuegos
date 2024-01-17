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
#include "MuelleAncladoRB.h"
#include <chrono>
#include <list>	

#include <iostream>

std::string display_text = "La maquina regalajuguetes";

std::string juguetes = "Juguetes restantes: 10";

std::string felicitacion = "Has ganado 0 juguetes";

std::string espacio = "SPACE para soltar objeto";
std::string controles = "TFGH mover gancho";
std::string controles1 = "B soplar viento derecha 2s";
std::string controles2 = "V soplar viento izq 2s";


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

RB* rbMuelle;
MuelleAncladoRB* as;
bool viento;
std::chrono::steady_clock::time_point timeInit;

void congratulations() {
	int a = 12 - rigidBodySys->getNPeluches();
	if (a != 1) felicitacion = "Has ganado " + to_string(a) + " juguetes";
	else felicitacion = "Has ganado " + to_string(a) + " juguete";
	
}
void updateText() {
	int a = rigidBodySys->getNPeluches() - 2;
    juguetes = "Juguetes restantes: " + to_string(a);
}

void creacionMuelle() {
	// Ejemplo Muelle
	Particle* pMuelle = new Particle(particleSys, Vector3(-175, 150, -355), Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 15, Vector4(1, 0, 0, 1), -1);
	particleSys->addParticle(pMuelle);
	GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
	registering->addRegistry(fg, pMuelle);
	AnchoredSpringFG* as1 = new AnchoredSpringFG(50, 20, Vector3(-175, 200, -355), particleSys);
	registering->addRegistry(as1, pMuelle);

	// Ejemplo Muelle
	Particle* pMuelle2 = new Particle(particleSys, Vector3(175, 150, -355), Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 15, Vector4(1, 0, 0, 1), -1);
	particleSys->addParticle(pMuelle2);
	GravityForceGenerator* fg2 = new GravityForceGenerator(Vector3(0, -9.8, 0));
	registering->addRegistry(fg2, pMuelle2);
	AnchoredSpringFG* as2 = new AnchoredSpringFG(50, 20, Vector3(175, 200, -355), particleSys);
	registering->addRegistry(as2, pMuelle2);
}

// Initialize physics engine
void initPhysics(bool interactive)
{

	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

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
	creacionMuelle();
	// Iman
	rbMuelle = rigidBodySys->createDynamicObject(Vector3(0, 175, -500), 20, 2, 20, { 1, 0, 0, 1 }, 1);
	as = new MuelleAncladoRB(0, 0, Vector3(0, 200, -500), rigidBodySys);
	RBregistering->addRegistry(as, rbMuelle);
	rigidBodySys->setGancho(rbMuelle);
	rigidBodySys->setAnclaje(as->getOther());
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	// Bucle hasta que el contador llegue a cero
	if (viento && std::chrono::steady_clock::now() - timeInit > std::chrono::seconds(2)) {
		rigidBodySys->setWind(0, 0, Vector3(0, 0, 0));
		viento = false;
	}
	rigidBodySys->update(t);
	if (rigidBodySys->getVictoria()) {
		Firework* f = new Firework(particleSys, PxVec3(-150, 0, -200), PxVec3(0, 0, 0), PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1), 0, registering);
		particleSys->addParticle(f);
		GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg, f);

		Firework* f2 = new Firework(particleSys, PxVec3(150, 0, -200), PxVec3(0, 0, 0), PxVec3(0, -9.8, 0), 5, 1.5, Vector4(1, 0, 0, 1), 1, registering);
		particleSys->addParticle(f2);
		GravityForceGenerator* fg2 = new GravityForceGenerator(Vector3(0, -9.8, 0));
		registering->addRegistry(fg2, f2);
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
	delete rigidBodySys;
	delete particleSys;
	delete registering;
	delete RBregistering;
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
	case 'T':
		if (as->getGanchoPos().z >= -625) {
			as->setGanchoPos(as->getGanchoPos() + Vector3(0, 0, -1));
			rbMuelle->setPos(rbMuelle->getPos() + Vector3(0, 0, -1));
		}
		break;
	case 'G':
		if (as->getGanchoPos().z <= -380) {
			as->setGanchoPos(as->getGanchoPos() + Vector3(0, 0, 1));
			rbMuelle->setPos(rbMuelle->getPos() + Vector3(0, 0, 1));
		}
		break;
	case 'F':
		if (as->getGanchoPos().x >= -125) {
			as->setGanchoPos(as->getGanchoPos() + Vector3(-1, 0, 0));
			rbMuelle->setPos(rbMuelle->getPos() + Vector3(-1, 0, 0));
		}
		break;
	case 'H':
		if (as->getGanchoPos().x <= 125) {
			as->setGanchoPos(as->getGanchoPos() + Vector3(1, 0, 0));
			rbMuelle->setPos(rbMuelle->getPos() + Vector3(1, 0, 0));
		}
		break;
	case 'Q':
		if (rbMuelle->getPos().y <= 175) rbMuelle->setPos(rbMuelle->getPos() + Vector3(0, 1, 0));
		break;
	case 'E':
		if (rbMuelle->getPos().y >= -80) rbMuelle->setPos(rbMuelle->getPos() + Vector3(0, -1, 0));
		break;
	case ' ':
		rigidBodySys->despegar();
		break;
	case 'B':
		if (!viento) {
			timeInit = std::chrono::steady_clock::now();
			rigidBodySys->setWind(100, 0, Vector3(1, -0.2, 0));
			viento = true;
		}
		break;
	case 'V':
		if (!viento) {
			timeInit = std::chrono::steady_clock::now();
			rigidBodySys->setWind(100, 0, Vector3(-1, -0.2, 0));
			viento = true;
		}
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