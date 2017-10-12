#include "euler.h"
#include "solarsystem.h"
#include <iostream>

Euler::Euler(double dt) :
    m_dt(dt)
{
}

void Euler::integrateOneStep(SolarSystem &system)
{
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies()) {
        body.position = body.position + body.velocity*m_dt; //
        body.velocity = body.velocity + body.force / body.mass * m_dt;
    }
    //std::cout << system.bodies()[1].position.length() << std::endl;
}
