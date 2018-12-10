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
void generate_query_queue( int aiCount, queue< Query* >& aorQueries, DMS CurrentDMS);

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
   generate_query_queue( kiCountQuery, koQueries, koDMS);

   // TODO
   while( !koQueries.empty( ) )
   {
      // check if there is an available server 
	   if (koTW.MServerAvailable())
	   {	//Find the next available server
		   // create random time for each query 
		   int ProcessingTime = (rand() % 9) + 1;
		   int ServerNum = koTW.MNextAvailable();
		   //koTW.insert(8, ServerNum, koQueries.front());
		   koTW.schedule(koDMS);
		   print_status();
		   koTW.clear_curr_slot();
	   }
   }

   print_final_statistics( );
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

void generate_query_queue( int aiCount, queue< Query* >& aorQueries, DMS CurrentDMS )
{
	Factory Test;
	aorQueries = Test.GenerateQueue(CurrentDMS, aiCount);
	cout << "Number of elements in Queue: " << aorQueries.size() << "\n";
	/*Query* p;
	while (!aorQueries.empty())
	{
		p = aorQueries.front();
		std::cout << " Query" << p->MSelection() << "\t SearchingTerm" << p->MSearch() << "\n";
		aorQueries.pop();
	}
	cout << std::endl;*/
}
