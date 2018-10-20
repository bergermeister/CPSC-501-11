#ifndef Sets_h
#define Sets_h

#include "Time.h"
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
      xeTypeInt     = 0,
      xeTypeString  = 1,
      xeTypeTime    = 2,
      xeTypeUnknown = 3
   };

   teType                       veType;
   std::multiset< int >         voSetInt;
   std::multiset< Time >        voSetTme;
   std::multiset< std::string > voSetStr;

public:        // Public Methods
   Sets( void );
   Sets( const Sets& aorSets );
   ~Sets( void );

   Sets& operator=( const Sets& aorSets );

   bool MProcess( std::string aoSet1, std::string aoSet2 );

   template< class GTcType >
   std::multiset< GTcType > MParse( const std::string aoSetStr )
   {
      GTcType                  koTemp;
      std::multiset< GTcType > koSet;
      std::istrstream          koStream( aoSetStr.c_str( ) );

      while( !koStream.fail( ) )
      {
         koStream >> koTemp;
         if( !koStream.fail( ) )
         {
            koSet.insert( koTemp );
         }
      }

      return( koSet );
   }

   template< class GTcType >
   std::multiset< GTcType > MUnion( const std::multiset< GTcType >& aorSet1, const std::multiset< GTcType >& aorSet2 )
   {
      std::multiset< GTcType > koUnion;

      std::set_union( aorSet1.begin( ), aorSet1.end( ), aorSet2.begin( ), aorSet2.end( ),
                      std::insert_iterator< std::multiset< GTcType > >( koUnion, koUnion.begin( ) ) );

      return( koUnion );
   }
   
   template< class GTcType >
   std::multiset< GTcType > MUnique( const std::multiset< GTcType >& aorSet )
   {
      std::multiset< GTcType > koUnique;
      
      std::unique_copy( aorSet.begin( ), aorSet.end( ),
                        std::insert_iterator< std::multiset< GTcType > >( koUnique, koUnique.begin( ) ) );

      return( koUnique );
   }

   friend std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets );

private:       // Private Methods
   teType mParseWord( std::string::iterator& aorBegin, const std::string::iterator aoEnd, std::string& aorWord );

   template< class GTcType >
   std::ostream& mPrint( std::ostream& aorOut, const std::multiset< GTcType >& aorSet ) const
   {
      for( auto koIter = aorSet.begin( ); koIter != aorSet.end( ); koIter++ )
      {
         aorOut << *koIter << ", ";
      }
      
      return( aorOut );
   }
};

#endif

