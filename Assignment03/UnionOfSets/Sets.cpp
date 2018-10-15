#include "Sets.h"
#include <set>

Sets::Sets( void )
{
   // TODO
}

Sets::Sets( const Sets& aorSets )
{
   // Call assignment operator
   *this = aorSets;
}

Sets::~Sets( void )
{
   // TODO
}

Sets& Sets::operator=( const Sets& aorSets )
{
   // TODO

   return( *this );
}

bool Sets::MProcess( std::string aoSet1, std::string aoSet2 )
{
   bool kbStatus = false;  // Assume failure

   // TODO

   return( kbStatus );
}

std::multiset< int > Sets::MUnion( std::string aoSet1, std::string aoSet2 )
{
   std::multiset< int > koUnion;

   // TODO: This should be a template function or the class should become a template

   return( koUnion );
}