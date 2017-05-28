/* 
 * File:   Vector.h
 * Author: hadhahad
 *
 * Created on May 24, 2017, 6:56 PM
 */

#ifndef VECTOR_H
#define VECTOR_H


#include <vector>
#include <cmath>
#include <ostream>


class Vector
{
   public:
   
      void setSize( const int size );
      
      int getSize() const;
      
      double& operator[]( const int index );
      
      const double& operator[]( const int index ) const;
      
      Vector& operator -= ( const Vector& b );
      
      void swap( Vector& v );
         
   protected:
      
      std::vector< double > data;
      
      int size;
};

std::ostream& operator << ( std::ostream& str, const Vector& v );

#endif /* VECTOR_H */

