#include "ParticulasAleatorias.h"
ParticulasAleatorias::ParticulasAleatorias(ParticleSystem* particleSys_, ParticleForceRegistry* registering_) {
    particleSys = particleSys_;
    registering = registering_;
    std::mt19937 genPos(dPos());
   
}
void ParticulasAleatorias::crearExplosion() {
    for (int i = 0; i < 100; ++i) {
        int randomValue1 = std::rand() % 2;
        int result1 = (randomValue1 == 0) ? -1 : 1;

        int randomValue2 = std::rand() % 2;
        int result2 = (randomValue2 == 0) ? -1 : 1;

        int randomValue3 = std::rand() % 2;
        int result3 = (randomValue3 == 0) ? -1 : 1;

        Vector3 pos(randomPos(genPos) * result1, randomPos(genPos) * result2, randomPos(genPos) * result3);

        Particle* p = new Particle(particleSys, pos, Vector3(0, 0, 0), PxVec3(0, -9.8, 0), 15, 3, Vector4(1, 0, 0, 1));
        p->setTimeOfLife(15);
        particleSys->addParticle(p);
        GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -1.5, 0));
        registering->addRegistry(fg, p);
        ExplosionGenerator* eg = new ExplosionGenerator(1000000000);
        registering->addRegistry(eg, p);
    }
}

void ParticulasAleatorias::crearTorbellino() {
    const double radio = 15.0;  // Radio del círculo
    const int nParticulas = 30;  // Número de puntos en el círculo
    for (int i = 0; i < nParticulas; ++i) {
        // Calcular el ángulo para cada punto en el círculo
        double angulo = 2 * M_PI * i / nParticulas;

        // Calcular las coordenadas x e y usando las funciones coseno y seno
        double x = radio * cos(angulo);
        double z = radio * sin(angulo);

        Vector3 pos(x, -i + 30, z);

        Particle* p = new Particle(particleSys, pos, Vector3(0, 0, 0), PxVec3(0, -9.8, 0), 15, 2, Vector4(1, 0, 0, 1));
        p->setTimeOfLife(15);
        particleSys->addParticle(p);
        GravityForceGenerator* fg = new GravityForceGenerator(Vector3(0, -9.8, 0));
        registering->addRegistry(fg, p);
        TorbellinoGenerator* tg = new TorbellinoGenerator(3);
        registering->addRegistry(tg, p);
    }
}