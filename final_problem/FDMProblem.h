/* 
 * File:   FDMProblem.h
 * Author: hadhahad
 *
 * Created on May 24, 2017, 4:00 PM
 */

#ifndef FDMPROBLEM_H
#define FDMPROBLEM_H

#include<iostream>
#include<fstream>
#include "TridiagonalMatrix.h"
#include "Vector.h"
#include <cmath>
#include <assert.h>

class FDMProblem
{
   public:
      
      double evaluateP( const double& x );
      
      double evaluateQ( const double& x );
      
      double evaluateRightHandSide( const double& x );

      void solve( const double& initialTime, const double& finalTime, 
                             const double& initialCondition_ini, const double& initialCondition_fin, 
                             const int& m, Vector& mesh, Vector& x, const int& verbose );

      bool writeSolution( const char*  fileName, Vector& mesh, Vector& x );
};


#endif /* FDMPROBLEM_H */

