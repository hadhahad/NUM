/* 
 * File:   Solver.h
 * Author: hadhahad
 *
 * Created on May 24, 2017, 11:03 PM
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "TridiagonalMatrix.h"

class ThomasAlgorithm
{
   public:
      ThomasAlgorithm( TridiagonalMatrix& A, Vector& b );
      
      bool solve( Vector& x );      
      
   protected:
      
      TridiagonalMatrix A;
      
      Vector b;
   
};



#endif /* SOLVER_H */

