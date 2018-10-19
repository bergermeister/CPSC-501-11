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
      xeTypeInt     = 0,
      xeTypeString  = 1,
      xeTypeTime    = 2,
      xeTypeUnknown = 3
   };

   teType                       veType;
   std::multiset< std::string > voSetStr;
   std::multiset< int >         voSetInt;
   
   // TODO: Need to implement Time class and multiset of Time Class

public:        // Public Methods
   Sets( void );
   Sets( const Sets& aorSets );
   ~Sets( void );

   Sets& operator=( const Sets& aorSets );

   bool MProcess( std::string aoSet1, std::string aoSet2 );

   template< class GTcType >
   void MInsert( std::string aoWord, std::multiset< GTcType >& aorSet )
   {
      GTcType         koObject;
      std::istrstream koStream( aoWord.c_str( ) );

      while( !koStream.eof( ) )
      {
         koStream >> koObject;
         aorSet.insert( koObject );
      }
   }

   template< class GTcType >
   std::multiset< GTcType > MUnique( std::multiset< GTcType >& aorSet )
   {
      std::multiset< GTcType > koResult;

      for( auto koIter = aorSet.begin( ); 
           koIter != aorSet.end( ); 
           koIter = std::upper_bound( koIter, aorSet.end( ), *koIter ) )
      {
         koResult.insert( *koIter );
      }

      return( koResult );
   }

   friend std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets );

private:       // Private Methods
   teType mParseWord( std::string::iterator& aorBegin, const std::string::iterator aoEnd, std::string& aorWord );

   template< class GTcType >
   std::ostream& mPrint( std::ostream& aorOut, const std::multiset< GTcType >& aorSet ) const
   {
      for( auto koIter = aorSet.begin( ); koIter != aorSet.end( ); koIter++ )
      {
         aorOut << *koIter << '\t';
      }
      aorOut << std::endl;
      
      return( aorOut );
   }
};

#endif

