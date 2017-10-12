#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>

class SolarSystem
{
public:
    SolarSystem();
    void createCelestialBody(vec3 position, vec3 velocity, double mass);
    void calculateForcesAndEnergy();
    int numberOfBodies() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    double angularmomentum() const;
    double giveBeta() const;
    double totMass() const;  //Funksjoner deklarasjon
    vec3 centerofmass();
    void writeToFile(std::string filename);
    std::vector<CelestialBody> &bodies();
    void correctInitialConditions();

private:
    std::vector<CelestialBody> m_bodies;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double m_angularmomentum;
    double m_beta;
    double m_totMass;  //Variabel deklarasjon
    vec3 m_centerofmass;
};

#endif // SOLARSYSTEM_H
