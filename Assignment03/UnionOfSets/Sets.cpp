#include "Sets.h"
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <strstream>
#include <iomanip>
#include <cctype>

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
   using std::string;
   using std::multiset;
   using std::vector;

   bool               kbStatus = false;  // Assume failure
   int                kiIndex;
   teType             keType[ 2 ]   = { xeTypeInt, xeTypeInt };
   string             koSetStr[ 2 ] = { aoSet1, aoSet2 };
   string             koWord;
   string::iterator   koIter;
   multiset< int > koWordSet[ 2 ];

   for( kiIndex = 0; kiIndex < 2; kiIndex++ )
   {
      koWord = "";
      for( koIter = koSetStr[ kiIndex ].begin( ); koIter != koSetStr[ kiIndex ].end( ); koIter++ )
      {
         if( *koIter == ',' )
         {
            break;
         }
         else
         {
            koWord += *koIter;
         }

         // If the current type is int a ':' is encountered, switch to time
         if( keType[ kiIndex ] == xeTypeInt )
         {
            if( *koIter == ':' )
            {
               // TODO Create time object
               keType[ kiIndex ] = xeTypeTime;
            }
         }

         // If 
         if( ( ( *koIter < '0' ) || ( *koIter > '9' ) ) && ( *koIter != ' ' ) && ( *koIter != ':' ) )
         {
            keType[ kiIndex ] = xeTypeString;
         }
      }
   }

   if( keType[ 0 ] == keType[ 1 ] )
   {
      // TODO Create a union
      switch( keType[ 0 ] )
      {
      case xeTypeInt:
         this->MUnion< int >( koSetStr );
         break;
      case xeTypeString:
         this->MUnion< std::string >( koSetStr );
         break;
      case xeTypeTime:
         // TODO: this->MUnion< 
         break;
      }
   }

   /*
   vector< int > koResult( 20 );
   vector< int >::iterator koRIter = koResult.begin( );
   try
   {
      koRIter = std::set_union( koWordSet[ 0 ].begin( ), koWordSet[ 0 ].end( ), 
                                koWordSet[ 1 ].begin( ), koWordSet[ 1 ].end( ), 
                                koResult.begin( ) );

      for( koRIter = koResult.begin( ); koRIter != koResult.end( ); koRIter++ )
      {
         std::cout << *koRIter << '\t';
      }

   }
   catch( std::exception kopException )
   {
   }
   */
   //koResult = this->MUnion< std::string >( koWordSet[ 0 ], koWordSet[ 1 ], koResult );

   // TODO

   //std::for_each( );

   return( kbStatus );
}

std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets )
{
   return( aorOut );
}

