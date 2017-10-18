#include "solarsystem.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0),
    m_totMass(0)
{
}

void SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );  //Fyller opp vektoren m_bodies med bodies
    m_totMass += mass;
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_beta = 3; //Gi r_vec/r^3 i F_G. Svarer til 1/r^2
    m_centerofmass.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberOfBodies(); i++) { //Gar gjennom hver av bodiene i numberOfBodies. For hver av disse, gaa gjennom alle andre planeter og regner ut kreftene som virker pa den forste planeten fra de andre.
        CelestialBody &body1 = m_bodies[i];  //Body1 blir sola forst, saa jorda
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];  //Body2 blir jorda forst

            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            // Calculate the force and potential energy here:

            //vec3 F = deltaRVector / (dr*dr*dr) *4 * M_PI*M_PI * body1.mass * body2.mass;
            vec3 F = deltaRVector / pow(dr, m_beta) *4 * M_PI*M_PI * body1.mass * body2.mass; //Oppg d
            //vec 3 F_EJ_x = deltaRVector_EJ[0] * 4*M_PI*M_PI * body1.mass*body3.mass / (dr_EJ*dr_EJ*dr_EJ)
            body1.force -= F;
            body2.force += F;
            m_potentialEnergy -= 4*M_PI*M_PI*body1.mass*body2.mass/dr;
        }

        m_centerofmass += body1.mass*body1.position;
        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();  //Kinetisk energi til jorda
        m_angularmomentum += body1.position.length()*body1.mass*body1.velocity.length(); //angular momentum of earth
    }
    m_centerofmass /= m_totMass;
    //cout << m_centerofmass << endl;
}

int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy; //Type double
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

double SolarSystem::angularmomentum() const
{
    return m_angularmomentum;
}

double SolarSystem::giveBeta() const
{
    return m_beta;
}

double SolarSystem::totMass() const
{
    return m_totMass;
}

vec3 SolarSystem::centerofmass()
{
    return m_centerofmass;
}

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    //m_file << numberOfBodies() << endl;
    //m_file << "Comment line that needs to be here." << endl;
    for(CelestialBody &body : m_bodies) {  //gaar gjennom alle bodies i m_bodies og skriver ut x-pos, y-pos, z-pos for hver. Dvs ny body i hver linje
        m_file <<  setprecision(10) << body.position.x() << " " << setprecision(10) << body.position.y() << " " << setprecision(10) << body.position.z() << "\n";
    }
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}

void SolarSystem::correctInitialConditions() //Oppg f.
{
    vec3 momentum;
    momentum.zeros();
    m_centerofmass.zeros();
    for(int i=0; i<numberOfBodies(); i++) { //Gar gjennom hver av bodiene i numberOfBodies.
        CelestialBody &body = m_bodies[i];
         m_centerofmass += body.mass*body.position;
         momentum += body.velocity*body.mass;  //Regner ut bevegelsesmengde for hver body
    }
    m_centerofmass /= m_totMass;
    for(int i=0; i<numberOfBodies(); i++) { //Gar gjennom hver av bodiene i numberOfBodies.
        CelestialBody &body = m_bodies[i];
        body.position-=m_centerofmass; //Forskyver koord.syst slik at center of mass blir origo
    }
    m_bodies[0].velocity-=momentum/m_bodies[0].mass; //Oppdaterer solas hastighet
    //cout << "Hastighet sol: " << m_bodies[0].velocity <<  endl;
    //cout << "Totalt momentum" << momentum << endl;
}
