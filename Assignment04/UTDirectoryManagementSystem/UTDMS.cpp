#include "CppUnitTest.h"
#include "..\DirectoryManagementSystem\DMS.h"
#include <vector>
#include <map>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

namespace UTDirectoryManagementSystem
{		
	TEST_CLASS( UTDMS )
	{
	public:
		
		TEST_METHOD( UTQuery1 )
		{
         using namespace std;

         vector< pair< string, int > > koResults;
			DMS                           koDMS;
         string                        koDir = EXPAND( PATH );
         koDir.erase( 0, 1 );                // erase the first quote
         koDir.erase( koDir.size( ) - 2 );   // erase the last quote and the dot

         koDMS.populateDirectory( koDir + "UTInput1.txt" );
         koResults = koDMS.MQuery1( "Freya" );
         
         Assert::IsTrue( koResults.size( ) == 1,       ( const wchar_t* )"Incorrect Number of Contacts" );
         Assert::IsTrue( koResults[ 0 ].first == "MD", ( const wchar_t* )"Incorrect State" );
         Assert::IsTrue( koResults[ 0 ].second == 1,   ( const wchar_t* )"Incorrect Count in State" );
		}

     TEST_METHOD( UTQuery2 )
      {
		  using namespace std;
		  vector< pair< string, int > > koResults;
		  DMS                           koDMS;
		  string                        koDir = EXPAND(PATH);
		  koDir.erase(0, 1);                // erase the first quote
		  koDir.erase(koDir.size() - 2);   // erase the last quote and the dot
		  koDMS.populateDirectory(koDir + "UTInput1.txt");
		  koResults = koDMS.MQuery2("edu");

		  Assert::IsTrue(koResults.size() == 2, (const wchar_t*)"Incorrect Number of Contacts");
		  Assert::IsTrue(koResults[0].first == "Males", (const wchar_t*)"Incorrect Category");
		  Assert::IsTrue(koResults[0].second == 0, (const wchar_t*)"Incorrect Count of .edu in Male Category");
		  Assert::IsTrue(koResults[1].first == "Females", (const wchar_t*)"Incorrect Category");
		  Assert::IsTrue(koResults[1].second == 1, (const wchar_t*)"Incorrect Count of .edu in Female Category");

      }
	};
}