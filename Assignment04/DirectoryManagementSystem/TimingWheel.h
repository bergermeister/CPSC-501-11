#ifndef TimingWheel_h
#define TimingWheel_h

#include "DMS.h"
#include "Query.h"
#include "Partition.h"

class TimingWheel
{
private:
   static const int xiMinDelay        =  3;
   static const int xiMaxDelayDefault = 10;

   Partition** vopSlot;
   int         viMaxDelay;
   int         viCurrentSlot;

public:
   TimingWheel( const int aiMaxDelay = xiMaxDelayDefault );
   TimingWheel( const TimingWheel& aorWheel );
   ~TimingWheel( void );

   TimingWheel& operator=( const TimingWheel& aorWheel );

   void insert( int aiProcessingTime, int aiServerNum, Query aoQuery );
   void schedule( DMS& aorDMS );
   void clear_curr_slot( void );
};

#endif
