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

   bool   kbStatus = true;  // Assume success
   int    kiIndex;
   string koSetStr[ 2 ] = { aoSet1, aoSet2 };
   string koWord;
   teType keType;

   this->voSetInt.clear( );       // Clear the integer set
   this->voSetStr.clear( );       // Clear the string set
   this->veType = xeTypeUnknown;

   // Loop through each input set string
   for( kiIndex = 0; kiIndex < 2; kiIndex++ )
   {
      for( auto koIter = koSetStr[ kiIndex ].begin( ); 
           koIter != koSetStr[ kiIndex ].end( );
           /* koIter is increment in the mParseWord routine */ )
      {
         // Advance the iterator and parse the next word
         keType = this->mParseWord( koIter, koSetStr[ kiIndex ].end( ), koWord );

         // If the type is not set
         if( this->veType == xeTypeUnknown )
         {
            // Set to type of the first element
            this->veType = keType;
         }
         else if( this->veType != keType )
         {
            // Indicate failure
            kbStatus = false;
            break;
         }

         // Build the correct multiset
         switch( this->veType )
         {
         case xeTypeInt:
            this->MInsert( koWord, this->voSetInt );
            break;
         case xeTypeTime:
            // TODO:
            break;
         case xeTypeUnknown:  // Fall through to default
         case xeTypeString:   // Treat default case a string
         default:
            this->MInsert( koWord, this->voSetStr );
            break;
         }
      }
   }

   // TODO Create a union
   switch( this->veType )
   {
   case xeTypeInt:
      this->voSetInt = this->MUnique( this->voSetInt );
      break;
   case xeTypeString:
      this->voSetStr = this->MUnique( this->voSetStr );
      break;
   case xeTypeTime:
      // TODO: this->MUnion< 
      break;
   }

   return( kbStatus );
}

std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets )
{
   switch( aorSets.veType )
   {
   case Sets::xeTypeInt:
      aorSets.mPrint( aorOut, aorSets.voSetInt );
      break;
   case Sets::xeTypeTime:
      // TODO
      break;
   case Sets::xeTypeUnknown:
   case Sets::xeTypeString:
   default:
      aorSets.mPrint( aorOut, aorSets.voSetStr );
      break;
   }

   return( aorOut );
}

Sets::teType Sets::mParseWord( std::string::iterator& aorBegin, const std::string::iterator aoEnd, std::string& aorWord )
{
   teType keType = xeTypeInt;    // Assume int

   // Initialize the word to empty string
   aorWord = "";

   // Find the next delimiter (,) or end of string
   for( ; aorBegin != aoEnd; aorBegin++ )
   {
      // If the current character is the delimiter
      if( *aorBegin == ',' )
      {
         // Move past the delimiter and break out of the loop
         aorBegin++;
         break;
      }
      else
      {
         aorWord += *aorBegin;
      }

      // If the current type is int a ':' is encountered, switch to time
      if( keType == xeTypeInt )
      {
         if( *aorBegin == ':' )
         {
            // TODO Create time object
            keType = xeTypeTime;
         }
      }

      // If 
      if( ( ( *aorBegin < '0' ) || ( *aorBegin > '9' ) ) && ( *aorBegin != ' ' ) && ( *aorBegin != ':' ) )
      {
         keType = xeTypeString;
      }
   }

   return( keType );
}

