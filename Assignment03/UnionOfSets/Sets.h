#ifndef Sets_h
#define Sets_h

#include <set>
#include <string>
#include <iostream>
#include <strstream>
#include <algorithm>
#include <iterator>

class Sets
{
private:       // Private Attributes
   enum teType
   {
      xeTypeInt    = 0,
      xeTypeString = 1,
      xeTypeTime   = 2
   };

   std::multiset< int > aoInts;
   // TODO: Need to implement Time class and multiset of Time Class

public:        // Public Methods
   Sets( void );
   Sets( const Sets& aorSets );
   ~Sets( void );

   Sets& operator=( const Sets& aorSets );

   bool MProcess( std::string aoSet1, std::string aoSet2 );

   template< class GTcType >
   std::multiset< GTcType >& MUnion( std::string aoSetStr[ 2 ] )
   {
      std::multiset< GTcType > koSet;
      std::string::iterator    koIter;
      int                      kiIndex;
      std::istrstream          koStream0( aoSetStr[ 0 ].c_str( ) );
      std::istrstream          koStream1( aoSetStr[ 1 ].c_str( ) );
      GTcType                  koTemp;
      char                     koComma;

      while( !koStream0.eof( ) )
      {
         koStream0 >> koTemp;
         koStream0 >> koComma;
         koSet.insert( koTemp );
      }

      /*
      for( kiIndex = 0; kiIndex < 2; kiIndex++ )
      {
         for( koIter = aoSetStr[ kiIndex ].begin( ); koIter != aoSetStr[ kiIndex ].end( ); koIter++ )
         {
            //koSet.insert( *koIter );
         }
      }
      */

      return( koSet );
   }

   friend std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets );

private:       // Private Methods

};

#endif

