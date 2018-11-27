#include "Query.h"

Query::Query( void )
{
   // TODO
}

Query::Query( const Query& aorQuery )
{
   // Call assignment operator
   *this = aorQuery;
}

Query::~Query( )
{
   // TODO
}

Query& Query::operator=( const Query& aorQuery )
{
   if( this != &aorQuery )
   {
      // TODO
   }

   return( *this );
}
