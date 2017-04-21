/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hadhahad
 *
 * Created on April 21, 2017, 3:52 PM
 */

#include <cstdlib>
#include "RiccatiProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "RungeKutt.h"
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef RiccatiProblem Problem;
typedef RungeKutt< Problem > Integrator;
const double initialTime( 0.12 );
const double finalTime( 0.15 );
const double timeStep( 1.0e-3 );
const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    Problem problem;
    Integrator integrator( problem );
    ODESolution solution;
    integrator.setIntegrationTimeStep( integrationTimeStep );
    ODESolver< Problem, Integrator > solver( problem, integrator );
    double initialCondition[ 1 ];
    initialCondition[ 0 ] = problem.getExactSolution( initialTime );
    solver.setInitialCondition( initialCondition );
    solver.solve( solution, initialTime, finalTime, timeStep );
    solution.write( "riccati.txt", initialTime, timeStep );
    problem.writeExactSolution( "exact-riccati.txt", initialTime, finalTime, timeStep, 1.0 );
    
    
    return EXIT_SUCCESS;
}


