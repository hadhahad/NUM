/* 
 * File:   main.cpp
 * Author: hadhahad
 *
 * Created on May 24, 2017, 3:51 PM
 */

#include <cstdlib>
#include "FDMProblem.h"
#include "Vector.h"

using namespace std;

typedef FDMProblem Problem;
const double initialTime( M_PI / 2 );
const double finalTime( M_PI );
//const double initialTime( 0 );
//const double finalTime( 15 );
const double initialCondition_ini( 0 );
const double initialCondition_fin( 1 );
const int m( 100000 );


/*
 * 
 */
int main(int argc, char** argv) 
{
    Problem problem;  
    Vector mesh;
    Vector x;
    mesh.setSize( m + 1 );
    x.setSize( m + 1 );
    
    problem.solve( initialTime, finalTime, initialCondition_ini, initialCondition_fin, m, mesh, x );
    problem.writeSolution("solution.txt", mesh, x);
    
    return 0;
}

