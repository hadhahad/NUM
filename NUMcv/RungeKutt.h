/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RungeKutt.h
 * Author: Vladislav Belov
 *
 * Created on April 21, 2017, 4:04 PM
 */

#ifndef RUNGEKUTT_H
#define RUNGEKUTT_H


template< typename Problem >
class RungeKutt : public IntegratorBase
{
   public:
      
      RungeKutt( Problem& problem )
      {
         this->k1 = new double[ problem.getDegreesOfFreedom() ];
         this->k2 = new double[ problem.getDegreesOfFreedom() ];
         this->aux = new double[ problem.getDegreesOfFreedom() ];
      }
     
      bool solve( Problem& problem,
                  double* u )
      {
         const int dofs = problem.getDegreesOfFreedom();
         double tau = std::min( this->integrationTimeStep, this->stopTime - this->time );
         long int iteration( 0 );
         while( this->time < this->stopTime )
         {
            /****
             * Compute k1
             */
            problem.getRightHandSide( this->time, u, k1 );
            
            /****
             * Compute k2
             */
            for( int i = 0; i < dofs; i++ )
                aux[ i ] = u[ i ] + tau * k1[ i ];
            problem.getRightHandSide( this->time + tau, aux, k2 );
            
            
             /***
             *
             */
            
            for( int i = 0; i < dofs; i++ )
                  u[ i ] += ( tau / 2.0 ) * ( k1[ i ] + k2[ i ] );
               this->time += tau;
               iteration++;
               if( iteration > 100000 )
               {
                  std::cerr << "The solver has reached the maximum number of iteratoins. " << std::endl;
                  return false;
               }
            tau = std::min( tau, this->stopTime - this->time );
            std::cout << "ITER: " << iteration << " \t tau = " << tau << " \t time= " << time << "         \r " << std::flush;  
         }
         std::cout << std::endl;
         return true;
      }
      
      ~RungeKutt()
      {
         delete[] k1;
         delete[] k2;
         delete[] aux;
      }
      
   protected:
      
      double *k1, *k2, *aux;
      
};

#endif /* RUNGEKUTT_H */

