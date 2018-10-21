/**
 * @file       UTSets.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Unit Test methods for the Union of Sets class
 */
#include "CppUnitTest.h"
#include "..\UnionOfSets\Sets.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnionOfSetsUT
{		
	TEST_CLASS( UTSets )
	{
	public:
      TEST_METHOD( MUTProcess )
      {
         int         kiIndex;
         std::string koSetStr[ 9 ] =  { "10, 20, 10, 30, 10",
                                        "40, 40, 50, 75, 75",
                                        "10.1, 10.2, 10.3, 10.75",
                                        "10.75, 10.2, 10.4, 10.5",
                                        "1:39, 2:40, 3:41, 4:60, 5:00",
                                        "2:00, 2:40, 5:01, 1:39, 3:41",
                                        "A, B, C, D, E ",
                                        "F, G, A, B, H ", 
                                        "20, 10, 31, 32, 35 " };
         int         kiResultInt[ 9 ] = { 10, 20, 30, 31, 32, 35, 40, 50, 75 };
         double      kdResultDbl[ 6 ] = { 10.1, 10.2, 10.3, 10.4, 10.5, 10.75 };
         Time        koResultTme[ 6 ] = { Time( 1, 39 ), Time( 2, 0 ), Time( 2, 40 ), Time( 3, 41 ), Time( 5, 0 ), Time( 5, 1 ) };
         std::string koResultStr[ 8 ] = { "A", "B", "C", "D", "E", "F", "G", "H" };
         Sets        koSets;
         std::multiset< int >         koSetInt;
         std::multiset< Time >        koSetTime;
         std::multiset< std::string > koSetString;
         std::multiset< double >      koSetDouble;

         for( kiIndex = 0; kiIndex < 9; kiIndex++ )
         {
            Assert::IsTrue( koSets.MProcess( koSetStr[ kiIndex ] ), ( const wchar_t* )"ERROR: Failed to process line" );
         }

         koSetInt    = koSets.MGetSetInt( );
         koSetTime   = koSets.MGetSetTme( );
         koSetString = koSets.MGetSetStr( );
         koSetDouble = koSets.MGetSetDbl( );

         Assert::AreEqual( 9, ( int )koSetInt.size( ), ( const wchar_t* )"ERROR: Incorrect integer union size" );
         Assert::AreEqual( 6, ( int )koSetTime.size( ), ( const wchar_t* )"ERROR: Incorrect Time union size" );
         Assert::AreEqual( 8, ( int )koSetString.size( ), ( const wchar_t* )"ERROR: Incorrect string union size" );
         Assert::AreEqual( 6, ( int )koSetDouble.size( ), ( const wchar_t* )"ERROR: Incorrect double union size" );

         kiIndex = 0;
         for( auto koIter = koSetInt.begin( ); koIter != koSetInt.end( ); koIter++ )
         {
            Assert::AreEqual( kiResultInt[ kiIndex ], *koIter, ( const wchar_t* )"ERROR: Incorrect integer value" );
            kiIndex++;
         }

         kiIndex = 0;
         for( auto koIter = koSetTime.begin( ); koIter != koSetTime.end( ); koIter++ )
         {
            Assert::IsTrue( koResultTme[ kiIndex ] == *koIter, ( const wchar_t* )"ERROR: Incorrect Time value" );
            kiIndex++;
         }

         kiIndex = 0;
         for( auto koIter = koSetString.begin( ); koIter != koSetString.end( ); koIter++ )
         {
            Assert::AreEqual( koResultStr[ kiIndex ], *koIter, ( const wchar_t* )"ERROR: Incorrect string value" );
            kiIndex++;
         }

         kiIndex = 0;
         for( auto koIter = koSetDouble.begin( ); koIter != koSetDouble.end( ); koIter++ )
         {
            Assert::AreEqual( kdResultDbl[ kiIndex ], *koIter, ( const wchar_t* )"ERROR: Incorrect double value" );
            kiIndex++;
         }
      }

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