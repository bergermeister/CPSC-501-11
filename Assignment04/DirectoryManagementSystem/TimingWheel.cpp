#include "TimingWheel.h"
#include <iostream>
using namespace std;
TimingWheel::TimingWheel( const int aiMaxDelay, const int aiServerCount )
{
   int kiIndex;

   // If the given delay is greater than or equal to the Min Delay
   if( aiMaxDelay >= xiMinDelay )
   {
      // Set the Max delay to the given delay
      this->viSlotCount = aiMaxDelay + 1;
   }
   else
   {
      // Otherwise use the default
      this->viSlotCount = xiMaxDelayDefault + 1;
   }

   // Allocate memory for the max delay
   this->vopSlot = new Partition*[ this->viSlotCount ];

   // Ensure each slot is null
   for( kiIndex = 0; kiIndex < this->viSlotCount; kiIndex++ )
   {
      this->vopSlot[ kiIndex ] = nullptr;
   }

   // Start at slot 0
   this->viCurrentSlot = 0;

   // Enqueue the initial list of servers
   for( kiIndex = 0; kiIndex < aiServerCount; kiIndex++ )
   {
      this->voAvailServer.push( kiIndex + 1 );
   }
}

TimingWheel::TimingWheel( const TimingWheel& aorWheel )
{
   // Call assignment operator
   *this = aorWheel;
}

TimingWheel::~TimingWheel( void )
{
   // Loop through each slot
   for( auto kiIndex = 0; kiIndex < this->viSlotCount; kiIndex++ )
   {
      // If the slot is not empty
      if( this->vopSlot[ kiIndex ] != nullptr )
      {
         // Free the allocated memory
         delete this->vopSlot[ kiIndex ];
      }
   }

   // Free the allocated memory for the array
   delete[ ] this->vopSlot;
}

TimingWheel& TimingWheel::operator=( const TimingWheel& aorWheel )
{
   if( this != &aorWheel )
   {
	   this->vopSlot = aorWheel.vopSlot;
	   this->voAvailServer = aorWheel.voAvailServer;
	   this->viCurrentSlot = aorWheel.viCurrentSlot;
	   this->viSlotCount = aorWheel.viSlotCount;
   }

   return( *this );
}

TimingWheel& TimingWheel::operator++( void )
{
   this->viCurrentSlot = ( this->viCurrentSlot + 1 ) % this->viSlotCount;
   return( *this );
}

void TimingWheel::insert( int aiProcessingTime, int aiServerNum, Query aoQuery )
{
   int        kiIndex;
   Partition* kopPartition;

   // Ensure the processing time is valid
   if( ( aiProcessingTime >= xiMinDelay ) && ( aiProcessingTime <= this->viSlotCount ) )
   {
      // Determine the slot index
      kiIndex = ( this->viCurrentSlot + aiProcessingTime ) % this->viSlotCount;

      // Insert a new Partition in the slot with the appropriate delay
      this->vopSlot[ kiIndex ] = new Partition( aiServerNum, aoQuery, this->vopSlot[ kiIndex ] );
   }
}

void TimingWheel::schedule( DMS& aorDMS )
{
   Partition* kopPartition = this->vopSlot[ this->viCurrentSlot ];

   while( kopPartition != nullptr )
   {
      // TODO Process the Query
      kopPartition->MProcess( aorDMS );

      // Partition completed, return server to available queue
      this->voAvailServer.push( kopPartition->MServerNum( ) );

      // Move to the next Partition
      kopPartition = kopPartition->MGetNext( );
   }
}

void TimingWheel::clear_curr_slot( void )
{
   // If there are partitions in the current slot
   if( this->vopSlot[ this->viCurrentSlot ] != nullptr )
   {
      // Free the allocated memory for the given slot
      delete this->vopSlot[ this->viCurrentSlot ];
      this->vopSlot[ this->viCurrentSlot ] = nullptr;
   }
}

bool TimingWheel::MServerAvailable( void ) const
{
   return( !this->voAvailServer.empty( ) );
}

int TimingWheel::MNextAvailable( void )
{
   int kiServer = -1;

   if( !this->voAvailServer.empty( ) )
   {
      kiServer = this->voAvailServer.front( );
      this->voAvailServer.pop( );
   }

   return( kiServer );
}

