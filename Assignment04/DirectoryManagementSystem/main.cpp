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
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void mPrintMenu( void );
void get_user_input( int aiArgc, char** acpArgv, int& airCountServer, int& airCountQuery, vector< string >& aorFiles );
void print_status( void );
void print_final_statistics( void );
void generate_query_queue( int aiCount, TimingWheel& aorTW );

int main( int aiArgc, char** acpArgv )
{
   TimingWheel      koTW;
   DMS              koDMS;
   int              kiCountServer;
   int              kiCountQuery;
   vector< string > koFiles;
   
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
   generate_query_queue( kiCountQuery, koTW );

   // TODO
   while( true /* Query Queue Not Empty? */ )
   {
      koTW.schedule( koDMS );
      print_status( );
      koTW.clear_curr_slot( );


   }

   print_final_statistics( );
   
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
}

void print_status( void )
{
   //
}

void print_final_statistics( void )
{
   // TODO
}

void generate_query_queue( int aiCount, TimingWheel& aorTW )
{
   // TODO
}
