/**
 * @file       TimingWheel.h
 * @author     Edward Eisenberger, Zainab Al Taweel
 * @date       2018-12-11
 * @compiler   Visual C++ 2017
 *
 * @brief Directory Management System class interface
 */
#ifndef TimingWheel_h
#define TimingWheel_h

#include "DMS.h"
#include "Query.h"
#include "Partition.h"
#include <queue>
#include <iostream>

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
   int ProccessedQueriesNum;

public:
   TimingWheel( const int aiMaxDelay = xiMaxDelayDefault, const int aiServerCount = xiServerCountDefault );
   TimingWheel( const TimingWheel& aorWheel );
   ~TimingWheel( void );

   TimingWheel& operator=( const TimingWheel& aorWheel );
   TimingWheel& operator++( void );

   void insert( int aiProcessingTime, int aiServerNum, Query aoQuery );
   void schedule( DMS& aorDMS );
   void clear_curr_slot( void );

   bool MServerAvailable( void ) const;
   int  MServerCount( void ) const;
   int  MNextAvailable( void );

   friend std::ostream& operator<<( std::ostream& aorOut, const TimingWheel& aorTW );
   int GetProccessedQueriesNum();
};

#endif
