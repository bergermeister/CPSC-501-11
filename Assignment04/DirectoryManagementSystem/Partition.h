#ifndef Partition_h
#define Partition_h

#include "Query.h"

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

   Partition* MGetNext( void );
};

#endif

