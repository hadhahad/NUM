/* 
 * File:   main.cpp
 * Author: hadhahad
 *
 * Created on May 24, 2017, 3:51 PM
 */

#include <cstdlib>
#include "FDMProblem.h"
#include "Vector.h"
#include <assert.h>

using namespace std;

typedef FDMProblem Problem;
const double initialTime( M_PI / 2 );
const double finalTime( M_PI );
//const double initialTime( 0 );
//const double finalTime( 15 );
const double initialCondition_ini( 0 );
const double initialCondition_fin( 1 );
const int m( 100000 );



int main(int argc, char** argv) 
{
    int verbose ( 0 );
    if ( ( argc == 2 ) && ( argv[1][0] == '-' ) && ( argv[1][1] == 'v' ) )
    {
        verbose = 1;
    }
    else
    {
        cerr << "Type the argument '-v' for verbose output. No other arguments are possible." << endl;
    }
    /*
    std::cout << "We have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; i++) 
    {
        std::cout << argv[i] << std::endl;
    }
    */
    Problem problem;  
    Vector mesh;
    Vector x;
    mesh.setSize( m + 1 );
    x.setSize( m + 1 );
    
    problem.solve( initialTime, finalTime, initialCondition_ini, initialCondition_fin, m, mesh, x, verbose );
    problem.writeSolution("solution.txt", mesh, x);
    
    return 0;
}

