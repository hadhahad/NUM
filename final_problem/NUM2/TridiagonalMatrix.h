/* 
 * File:   TridiagonalMatrix.h
 * Author: hadhahad
 *
 * Created on May 24, 2017, 6:52 PM
 */

#ifndef TRIDIAGONALMATRIX_H
#define TRIDIAGONALMATRIX_H


#include <vector>
#include <iostream>
#include "Vector.h"

class TridiagonalMatrix
{
   public:
   
      TridiagonalMatrix();
            
      TridiagonalMatrix( const int rows, const int columns );
      
      int getRows() const;
      
      int getColumns() const;
      
      bool setDimensions( const int rows, const int columns );
      
      bool setElement( const int row, const int column, const double& value );
      
      double getElement( const int row, const int column ) const;

      double& operator()( const int row, const int column );
      
      const double& operator()( const int row, const int column ) const;
      
      TridiagonalMatrix& operator=( const TridiagonalMatrix& m );
      
   private:      
      
      std::vector< double > elements;
      int rows, columns; 

};

#endif /* TRIDIAGONALMATRIX_H */

