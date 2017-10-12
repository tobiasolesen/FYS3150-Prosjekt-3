#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "solarsystem.h"
#include "euler.h"
#include "velocityverlet.h"
#include "vec3.h"
using namespace std;

//G = 4pi^2
//Hentet data fra NASA; dato 4 okt

int main(int numArguments, char **arguments)
{    
    int numTimesteps = 30000; //100
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);

    SolarSystem solarSystem; //Lager et objekt av klassen SolarSystem som heter SolarSystem. Refererer naa til klassen SolarSystem ved a bruke solarSystem.funksjon
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    //Rekkefolge planeter: Sun, Earth, Jupiter, Mars, Venus, Saturn

    solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 ); // Sun. Kaller pa funksjonen createCelestialBody som defineres i klassen SolarSystem

    // We don't need to store the reference, but just call the function without a left hand side
    solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6); // Earth. Init v = 2pi. Esc vel: sqrt(2G*M_sun/r)
    solarSystem.createCelestialBody( vec3(5.2, 0, 0), vec3(0, 2*M_PI/sqrt(5.2), 0), 9.5e-4 ); //New planet (Jupiter), init v = 2pi/sqrt(r)
    solarSystem.createCelestialBody( vec3(1.52, 0, 0), vec3(0, 2*M_PI/sqrt(1.52), 0), 3.3e-7); // Mars
    solarSystem.createCelestialBody( vec3(0.72, 0, 0), vec3(0, 2*M_PI/sqrt(0.72), 0), 2.45e-6); //Venus
    solarSystem.createCelestialBody( vec3(9.54, 0, 0), vec3(0, 2*M_PI/sqrt(9.54), 0), 2.75e-4); //Saturn

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> & bodies = solarSystem.bodies(); //.bodies contains all bodies in the system

    for(int i = 0; i < bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    //cout << solarSystem.bodies()[0].position << solarSystem.bodies()[0].velocity <<  endl;
    solarSystem.correctInitialConditions(); //Funksjonen correctInitialConditions regner ut bevegelsesmengde for hver body. Oppdaterer hastigheten til sola, og "setter" massesenteret i origo.
    //cout << solarSystem.bodies()[0].position << solarSystem.bodies()[0].velocity << endl;
    double dt = 0.001;
    //Euler integrator(dt);  //integrator blir et objekt av klassen Euler?
    VelocityVerlet integrator (dt);
    //VelocityVerlet integrator(dt);
    solarSystem.calculateForcesAndEnergy();
    for(int timestep=0; timestep<numTimesteps; timestep++) {  //For loop over timesteps
        //integrator.integrateOneStep(solarSystem);  //Calls func integrateOneStep from Euler class wich does Euler method
        integrator.integrateOneStep(solarSystem);    //Calls func integrateOneStep from velocityVerlet class, wich does Velocityverlet method
        solarSystem.writeToFile("positions.txt");
        //cout << "Total energy: " << solarSystem.totalEnergy() << endl; //Skriver ut totalenergien for hvert tidssteg for a se at den er konstant
        //cout << "Angular momentum" << solarSystem.angularmomentum() << endl; //Skriver ut angularmomentum for hvert tidssteg for a se at den er konst
    }

    cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    return 0;
}
