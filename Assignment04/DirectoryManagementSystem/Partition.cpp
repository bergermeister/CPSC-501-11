#include "Partition.h"

Partition::Partition( const int aiServerNum, Query aoQuery, Partition* aopNext )
{
   this->viServerNum = aiServerNum;
   this->voQuery     = aoQuery;
   this->vopNext     = aopNext;
}

Partition::Partition( const Partition& aorPartition )
{
   // Call assignment operator
   *this = aorPartition;
}

Partition::~Partition( void )
{
   // TODO: Verify this will delete all Partitions in the Linked List
   if( this->vopNext != nullptr )
   {
      delete this->vopNext;
   }
}

Partition& Partition::operator=( const Partition& aorPartition )
{
   if( this != &aorPartition )
   {
      // TODO
   }

   return( *this );
}

int Partition::MServerNum( void ) const
{
   return( this->viServerNum );
}

Partition* Partition::MGetNext( void )
{
   return( this->vopNext );
}

void Partition::MProcess( DMS& aorDMS )
{
   aorDMS.query( this->voQuery.MSelection( ), this->voQuery.MSearch( ) );
}
