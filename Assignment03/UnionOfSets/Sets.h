#ifndef Sets_h
#define Sets_h

#include <set>
#include <string>

class Sets
{
private:       // Private Attributes
   std::multiset< int > aoInts;
   // TODO: Need to implement Time class and multiset of Time Class

public:        // Public Methods
   Sets( void );
   Sets( const Sets& aorSets );
   ~Sets( void );

   Sets& operator=( const Sets& aorSets );

   bool                 MProcess( std::string aoSet1, std::string aoSet2 );
   std::multiset< int > MUnion( std::string aoSet1, std::string aoSet2 );
};

#endif

