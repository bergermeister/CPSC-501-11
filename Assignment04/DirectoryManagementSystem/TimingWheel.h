#ifndef TimingWheel_h
#define TimingWheel_h

#include "DMS.h"
#include "Query.h"
#include "Partition.h"
#include <queue>

class TimingWheel
{
private:
   static const int xiMinDelay           =  3;
   static const int xiMaxDelayDefault    = 10;
   static const int xiServerCountDefault = 4;

   Partition**       vopSlot;
   int               viSlotCount;
   int               viCurrentSlot;
   std::queue< int > voAvailServer;

public:
   TimingWheel( const int aiMaxDelay = xiMaxDelayDefault, const int aiServerCount = xiServerCountDefault );
   TimingWheel( const TimingWheel& aorWheel );
   ~TimingWheel( void );

   TimingWheel& operator=( const TimingWheel& aorWheel );

   void insert( int aiProcessingTime, int aiServerNum, Query aoQuery );
   void schedule( DMS& aorDMS );
   void clear_curr_slot( void );

   bool MServerAvailable( void ) const;
   int  MNextAvailable( void );
};

#endif
