#include "TridiagonalMatrix.h"


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

bool ThomasAlgorithm( TridiagonalMatrix& A, Vector& b )
{
   /****
    * First phase: Eliminate elements under diagonal
    */
   const int n = A.getColumns();
   A( 0, 1 ) /= A( 0, 0 );
   b[ 0 ] /= A( 0, 0 );
   A( 0, 0 ) = 1.0;
   for( int k = 1; k < n; k++ )
   {
      b[ k ] = ( b[ k ] - A( k, k - 1 ) * b[ k - 1 ] ) / ( A( k, k ) - A( k, k - 1 ) * A( k - 1, k) );
      if( k < n - 1 )
      {
         A( k, k + 1 ) = A( k, k + 1) / ( A( k, k ) - A( k, k - 1 ) * A( k - 1, k ) );
         A( k, k ) = 1.0;
      }
   }
   /****
    * Second phase: Backward substitution
    */
   for( int k = n - 2; k >= 0; k-- )
      b[ k ] = b[ k ] - A( k, k+1 ) * b[ k + 1 ];
}
