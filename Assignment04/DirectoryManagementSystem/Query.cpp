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
      this->vcSelection = aorQuery.vcSelection;
      this->voSearch    = aorQuery.voSearch;
   }

   return( *this );
}

const char Query::MSelection( void ) const
{
   return( this->vcSelection );
}

const std::string& Query::MSearch( void ) const
{
   return( this->voSearch );
}
