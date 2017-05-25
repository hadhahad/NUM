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
#include "Solver.h"
#include <cmath>

class FDMProblem
{
   public:
      
      double evaluateP(const double& x)
      {
          return exp(-sin(x));
      }
      
      double evaluateQ(const double& x)
      {
          return -sin(x)*exp(-sin(x));
      }
      
      double evaluateF(const double& x)
      {
          return 0;
      }
      
      void solve( const double& initialTime, const double& finalTime, 
                             const double& initialCondition_ini, const double& initialCondition_fin, 
                             const int& m, Vector& mesh, Vector& x)
      { 
          const double step = (finalTime - initialTime) / m;
          double* p;
          double *q;
          Vector rightHandSide;
          TridiagonalMatrix A;
          
          A.setDimensions( m + 1, m + 1 );
          p = new double[ m + 1 ];
          q = new double[ m + 1 ];
          rightHandSide.setSize( m + 1 );
          
          mesh[ 0 ] = initialTime;
          p[ 0 ] = evaluateP( initialTime );
          q[ 0 ] = evaluateQ( initialTime );
          rightHandSide[ 0 ] = initialCondition_ini;
          mesh[ m ] = finalTime;
          p[ m ] = evaluateP( finalTime );
          q[ m ] = evaluateQ( finalTime );
          rightHandSide[ m ] = initialCondition_fin;
          
          for(int i = 1; i < m; i++)
          {
              mesh[ i ] = initialTime + i * step;
              p[ i ] = evaluateP( mesh[ i ] );
              q[ i ] = evaluateQ( mesh[ i ] );
              rightHandSide[ i ] = evaluateF( mesh[ i ] );
          }
          
          A( 0, 0 ) = 1;
          A( m, m ) = 1;
          for(int i = 1; i < m; i++)
          {
              A( i, i - 1 ) = -p[ i ] / ( step * step );
              A( i, i ) = q[ i ] + ( p[ i ] + p[ i + 1 ] ) / ( step * step );
              A( i, i + 1 ) = -p[ i + 1 ] / ( step * step );
          }
          
          delete[] p;
          delete[] q; 
          
          ThomasAlgorithm solver( A, rightHandSide );
          solver.solve( x );         
      }

      bool writeSolution( const char*  fileName, Vector& mesh, Vector& x)
      {
         std::fstream file;
         file.open( fileName, std::ios::out );
         for(int i = 0; i < x.getSize(); i++)
         {
            file << mesh[i] << " " << x[i] << std::endl;
         }
      }
};


#endif /* FDMPROBLEM_H */

