#pragma once
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include <iostream>
#include <random>
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "ExplosionGenerator.h"
#include "TorbellinoGenerator.h"

#define M_PI 3.14159265358979323846
class ParticulasAleatorias
{
private:
	ParticleForceRegistry* registering;
	ParticleSystem* particleSys;
	int id;
	random_device dPos;
	mt19937 genPos;
	uniform_real_distribution<double> randomPos{ 0, 100 };
public:
	ParticulasAleatorias(ParticleSystem* particleSys_, ParticleForceRegistry* registering_);
	void crearExplosion();
	void crearTorbellino();
};

