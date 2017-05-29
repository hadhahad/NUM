#include "FDMProblem.h"

double FDMProblem::evaluateP(const double& x)
{
    return exp(-sin(x));
}

double FDMProblem::evaluateQ(const double& x)
{
    return -sin(x)*exp(-sin(x));
}

double FDMProblem::evaluateRightHandSide(const double& x)
{
    return 0;
}

void FDMProblem::solve( const double& initialTime, const double& finalTime, 
                             const double& initialCondition_ini, const double& initialCondition_fin, 
                             const int& m, Vector& mesh, Vector& x, const int& verbose )
{    
    if( verbose )
    {
        std::cout << "Variables allocation...";
    }
    int diagonalDominance( 2 );
    const double step = (finalTime - initialTime) / m;
    double* p;
    double *q;
    Vector rightHandSide;
    TridiagonalMatrix A;
          
    A.setDimensions( m + 1, m + 1 );
    p = new double[ m + 1 ];
    q = new double[ m + 1 ];
    rightHandSide.setSize( m + 1 );
    
    if( verbose )
    {
        std::cout << "........OK" << std::endl;
        std::cout << "Variables initialization...";
    }
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
        rightHandSide[ i ] = evaluateRightHandSide( mesh[ i ] );
    }
          
    A( 0, 0 ) = 1;
    A( m, m ) = 1;
    for(int i = 1; i < m; i++)
    {
        A( i, i - 1 ) = -p[ i ] / ( step * step );
        A( i, i ) = q[ i ] + ( p[ i ] + p[ i + 1 ] ) / ( step * step );
        A( i, i + 1 ) = -p[ i + 1 ] / ( step * step );
        if ( verbose )
        {
            if( std::abs( A( i, i ) ) >= std::abs( A( i, i - 1 ) ) + std::abs( A( i, i + 1 ) ) )
            {
                diagonalDominance += 1;
            }  
        } 
    }
    delete[] p;
    delete[] q; 
    if( verbose )
    {
        std::cout << "....OK" << std::endl;
        std::cout << "Matrix diagonal dominance...";
        if ( diagonalDominance == m + 1 )
        {
            std::cout << "...OK" << std::endl;
        }
        else 
        {
            std::cout << "...NO" << std::endl;
        }
        std::cout << "Thomas algorithm...";
    }
    
    if ( ThomasAlgorithm( A, rightHandSide ) )
    {
        if( verbose )
        {
            std::cout << "............OK" << std::endl;
        }
        x = rightHandSide;  
    }
    else
    {
        std::cerr << " Thomas algorithm was unsuccessful. " << std::endl;      
    }
           
}

bool FDMProblem::writeSolution( const char*  fileName, Vector& mesh, Vector& x)
{
    std::fstream file;
    file.open( fileName, std::ios::out );
    for(int i = 0; i < x.getSize(); i++)
    {
       file << mesh[i] << " " << x[i] << std::endl;
    }
}
