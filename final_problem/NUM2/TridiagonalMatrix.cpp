#include <string>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "TridiagonalMatrix.h"
#include <cmath>

TridiagonalMatrix::TridiagonalMatrix()
{
}

TridiagonalMatrix::TridiagonalMatrix( const int rows, const int columns )
{
   this->elements.resize( 3 * std::min( rows, columns ) );
}

int TridiagonalMatrix::getRows() const
{
   return this->rows;
}
      
int TridiagonalMatrix::getColumns() const
{
   return this->columns;
}
      
bool TridiagonalMatrix::setDimensions( const int rows, const int columns )
{
   this->rows = rows;
   this->columns = columns;
   this->elements.resize( 3 * std::min( rows, columns ) );
   return true;
}
   
bool TridiagonalMatrix::setElement( const int row, const int column, const double& value )
{
   if( std::abs( column - row ) > 1 )
   {
      std::cerr << "Accesing wrong element ( " << row << " column " << column << " ) in tridiagonal matrix. " << std::endl;
      return false;
   }
   this->elements[ 2 * row + column ] = value;
   return true;
}
      
double TridiagonalMatrix::getElement( const int row, const int column ) const
{
   if( std::abs( column - row ) > 1 )
      return 0.0;
   return this->elements[ 2 * row + column ];   
}

double& TridiagonalMatrix::operator()( const int row, const int column )
{
   if( std::abs( column - row ) > 1 )
   {
      std::cerr << "Accesing wrong element ( " << row << " column " << column << " ) in tridiagonal matrix. " << std::endl;
      throw( 0 );
   }
   return this->elements[ 2 * row + column ];   
}
      
const double& TridiagonalMatrix::operator()( const int row, const int column ) const
{
   if( std::abs( column - row ) > 1 )
   {
      std::cerr << "Accesing wrong element ( " << row << " column " << column << " ) in tridiagonal matrix. " << std::endl;
      throw( 0 );
   }   
   return this->elements[ 2 * row + column ];   
}

TridiagonalMatrix& TridiagonalMatrix::operator=( const TridiagonalMatrix& m )
{
   this->setDimensions( m.getRows(), m.getColumns() );
   this->elements = m.elements;
}