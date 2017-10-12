#ifndef VELOCITYVERLET_H
#define VELOCITYVERLET_H
#include "solarsystem.h"

class VelocityVerlet
{
public:
    VelocityVerlet(double dt);
    void integrateOneStep(SolarSystem &system);

private:
    double m_dt;
};

#endif // VELOCITYVERLET_H
