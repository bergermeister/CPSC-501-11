#ifndef Partition_h
#define Partition_h

#include "Query.h"
#include "DMS.h"
#include <iostream>

class Partition
{
private:
   Query      voQuery;
   int        viServerNum;
   Partition* vopNext;

public:
   Partition( const int aiServerNum, Query aoQuery, Partition* aopNext = nullptr );
   Partition( const Partition& aorPartition );
   ~Partition( void );

   Partition& operator=( const Partition& aorPartition );

   int        MServerNum( void ) const;
   Partition* MGetNext( void );
   void       MProcess( DMS& aorDMS );

   friend std::ostream& operator<<( std::ostream& aorOut, const Partition& aorPartition );
};

#endif

