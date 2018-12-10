/**
 * @file       main.cpp
 * @author     Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Main driver application for the Contact Hierarchy of classess
 */
#include "DMS.h"
#include "Query.h"
#include "TimingWheel.h"
#include "Factory.h"
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

void mPrintMenu( void );
void get_user_input( int aiArgc, char** acpArgv, int& airCountServer, int& airCountQuery, vector< string >& aorFiles );
void print_status( void );
void print_final_statistics( void );
void generate_query_queue( int aiCount, queue< Query >& aorQueries );

int main( int aiArgc, char** acpArgv )
{
   TimingWheel      koTW;
   DMS              koDMS;
   int              kiCountServer;
   int              kiCountQuery;
   vector< string > koFiles;
   queue< Query* >  koQueries;

   // Seed random number
   srand( time( NULL ) );

   // Obtain the User Input
   get_user_input( aiArgc, acpArgv, kiCountServer, kiCountQuery, koFiles );

   // Popule the DMS
   for( auto koIter = koFiles.begin( ); koIter != koFiles.end( ); koIter++ )
   {
      try
      {            
         koDMS.populateDirectory( *koIter );
      } 
      catch( exception koException )
      {             
         cerr << "Unable to read from file:" << endl;
         cerr << koException.what( ) << endl;
      }
   }

   // Generate a queue of Queries
  // generate_query_queue( kiCountQuery, koQueries );

   Factory Test;
   koQueries = Test.GenerateQueue(koDMS, kiCountQuery);
   cout << "Number of elements in Queue: " << koQueries.size()<<"\n";
   Query* p;
   while (!koQueries.empty())
   {
	   p = koQueries.front();
	   std::cout << " Query" << p->MSelection() << "\t SearchingTerm" << p->MSearch() <<"\n";
	   koQueries.pop();
   }
   cout << std::endl; 
   
   // TODO
   while( !koQueries.empty( ) )
   {
      // 

      koTW.schedule( koDMS );
      print_status( );
      koTW.clear_curr_slot( );


   }

   print_final_statistics( );

   // Check searching terms methods
    /*std::vector<std::string> AreaCodes = koDMS.GetAreaCodeTerms();
	for (size_t n = 0; n < AreaCodes.size(); n++)
		cout << AreaCodes[n] << " ";
	cout << endl;

	std::vector<std::string> Names = koDMS.GetFullNameTerms();
	for (size_t n = 0; n < Names.size(); n++)
		cout << Names[n] << " ";
	cout << endl;

	std::vector<std::string> BEmails = koDMS.GetBusinessEmailDomainTerms();
	for (size_t n = 0; n < BEmails.size(); n++)
		cout << BEmails[n] << " ";
	cout << endl;

	std::vector<std::string> PEmails = koDMS.GetPersonEmailDomainTerms();
	for (size_t n = 0; n < PEmails.size(); n++)
		cout << PEmails[n] << " ";
	cout << endl;
	cin.get();
	*/
   cin.get();

   return 0; 
}

void mPrintMenu( void )
{
   cout << "n \t Stop program"                           << endl;
   cout << "h \t Display Help Menu"                      << endl;
   cout << "d \t Display entire directory"               << endl;
   cout << "1 \t Query by name ordered by category"      << endl;
   cout << "2 \t Query person by email domain ordered by gender"               << endl;
   cout << "3 \t Query by business area code ordered by category"              << endl;
   cout << "4 \t Query by business email/website domain ordered by category"   << endl;
   cout << "5 \t Query by person with out of state area code ordered by state" << endl;
   cout << "b \t Display details of a Business"          << endl;
   cout << "p \t Display details of a Person"            << endl;
}

void get_user_input( int aiArgc, char** acpArgv, int& airCountServer, int& airCountQuery, vector< string >& aorFiles )
{
   int    kiCountFile;
   int    kiCountServer;
   int    kiCountQuery;
   string koFileName;

   // Clear the collection of files
   aorFiles.clear( );

   if( aiArgc < 4 )
   {
      cout << "Enter the number of servers: ";
      cin  >> kiCountServer;

      cout << "Enter the number of queries: ";
      cin  >> kiCountQuery;

      cout << "Enter the number of input files: " << endl;
      cin  >> kiCountFile;
      cout << "Enter the file names: " << endl; 
      for( int i = 0; i < kiCountFile; i++ )
      {         
         cin >> koFileName;
         aorFiles.push_back( koFileName );
      }
   }
   else
   {
      // Record the server and query counts
      kiCountServer = stoi( acpArgv[ 1 ] );
      kiCountQuery  = stoi( acpArgv[ 2 ] );

      // Record the list of files
      for( int kiIndex = 3; kiIndex < aiArgc; kiIndex++ )
      {
         aorFiles.push_back( string( acpArgv[ kiIndex ] ) );
      }
   }

   airCountServer = kiCountServer;
   airCountQuery  = kiCountQuery;

}


void print_status( void )
{
   //
}

void print_final_statistics( void )
{
   // TODO
}

void generate_query_queue( int aiCount, queue< Query >& aorQueries )
{
   // TODO
}
