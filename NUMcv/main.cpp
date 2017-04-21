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
#include "RungeKutta.h"
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef RiccatiProblem Problem;
typedef Merson< Problem > Integrator;
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
    
    if (true)
    {
        double sum(0), sum_sqr;
        double time(initialTime);
        double subtr, subtr_sqr;
        float L1, L2, Lmax(0);
        double ut, u;
        int timeStepCount = std::ceil( std::max( 0.0, finalTime - initialTime ) / timeStep );
        for(int k = 1; k <= timeStepCount ; k++)
        {
            time += timeStep;
            if (time >= finalTime)
                time = finalTime;
            ut = solution.getElement(k, 0);
            u = problem.getExactSolution(time);
            subtr = abs(ut - u);
            subtr_sqr = subtr*subtr;
            if (Lmax < subtr)
            {
                Lmax = subtr;
            }
            sum += subtr;
            sum_sqr += subtr_sqr;
        }
        sum *= timeStep;
        sum_sqr *= timeStep;
        L1 = sum;
        L2 = sqrt(sum_sqr);
        
        std::fstream file;
        file.open( "norms.txt", std::ios::out );
        if( !file )
        {
            std::cerr << "Unable to open a file " << "norms.txt" << "." << std::endl;
            return false;
        }
        file <<  "L1 = " << L1 << "\n" << 
            "L2 = " << L2 << "\n" <<
            "Lmax = " << Lmax << "\n" << std::endl;
    }
    
    return EXIT_SUCCESS;
}


