#include "Query.h"

Query::Query( void )
{
   // TODO
}

Query::Query(char ch, std::string SearchingTerm)
{
	vcSelection = ch;
	voSearch = SearchingTerm;
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

const char Query::MSelection( void ) const
{
   return( this->vcSelection );
}

const std::string& Query::MSearch( void ) const
{
   return( this->voSearch );
}
