#include "Vector.h"

void Vector::setSize( const int size )
{
   this->data.resize( size );
   this->size = size;
}

int Vector::getSize() const
{
   return this->size;
}

double& Vector::operator[]( const int index )
{
   return this->data[ index ];
}

const double& Vector::operator[]( const int index ) const
{
   return this->data[ index ];
}

Vector& Vector::operator -= ( const Vector& b )
{
   for( int i = 0; i < this->size; i++ )
      this->data[ i ] -= b[ i ];
}

void Vector::swap( Vector& v )
{
   this->data.swap( v.data );
}


std::ostream& operator << ( std::ostream& str, const Vector& v )
{
   for( int i = 0; i < v.getSize() - 1; i++ )
      str << v[ i ] << ", ";
   str << v[ v.getSize() - 1 ];
   return str;
}
