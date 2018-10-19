#include "CppUnitTest.h"
#include "..\UnionOfSets\Sets.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnionOfSetsUT
{		
	TEST_CLASS( UTSets )
	{
	public:
		TEST_METHOD( MUTUnique )
		{
         int         kiIndex;
         int         kiDataInt[ 10 ] = { 10, 20, 10, 30, 10, 
                                         40, 40, 50, 75, 75 };
         std::string koDataStr[ 10 ] = { "Test 1", "Test 2", "Test 1", "Test 3", "Test 4", 
                                         "Test 1", "Test 2", "Test 5", "Test 6", "Test 5" };
         int         kiResultInt[ 6 ] = { 10, 20, 30, 40, 50, 75 };
         std::string koResultStr[ 6 ] = { "Test 1", "Test 2", "Test 3", "Test 4", "Test 5", "Test 6" };
         std::multiset< int >         koSetInt[ 2 ];
         std::multiset< std::string > koSetStr[ 2 ];
         Sets                         koSets;

         for( kiIndex = 0; kiIndex < 10; kiIndex++ )
         {
            koSetInt[ 0 ].insert( kiDataInt[ kiIndex ] );
            koSetStr[ 0 ].insert( koDataStr[ kiIndex ] );
         }

         koSetInt[ 1 ] = koSets.MUnique( koSetInt[ 0 ] );
         koSetStr[ 1 ] = koSets.MUnique( koSetStr[ 0 ] );

         //kiCount = koSetInt[ 1 ].count( );

         Assert::AreEqual( ( size_t )6, koSetInt[ 1 ].size( ), ( const wchar_t* )"FAILURE: Incorrect size - Integer Set" );
         Assert::AreEqual( ( size_t )6, koSetStr[ 1 ].size( ), ( const wchar_t* )"FAILURE: Incorrect size - String Set" );

         kiIndex = 0;
         for( auto koIter = koSetInt[ 1 ].begin( ); koIter != koSetInt[ 1 ].end( ); koIter++ )
         {
            Assert::AreEqual( kiResultInt[ kiIndex ], *koIter, ( const wchar_t* )"FAILURE: Value mismatch - Integer Set" );
            kiIndex++;
         }

         kiIndex = 0;
         for( auto koIter = koSetStr[ 1 ].begin( ); koIter != koSetStr[ 1 ].end( ); koIter++ )
         {
            Assert::AreEqual( koResultStr[ kiIndex ], *koIter, ( const wchar_t* )"FAILURE: Value mismatch - String Set" );
            kiIndex++;
         }
		}

	};
}