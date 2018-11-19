/**
 * @file       main.cpp
 * @author     Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Main driver application for the Contact Hierarchy of classess
 */
#include "Contact.h"
#include "PersonContact.h"
#include "BusinessContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "PersonEmailContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessAddressContact.h"
#include "BusinessWebContact.h"
#include "DMS.h"

void mPrintMenu( void );

int main( int aiArgc, char** acpArgv )
{
   DMS dms;
   int file_count;
   char response;
   
   if( aiArgc < 2 )
   {
      cout << "Enter the number of input files: " << endl;
      cin >> file_count;
      string* file_names = new string[ file_count ];
      cout << "Enter the file names: " << endl; 
      for( int i = 0; i < file_count; i++ )
      {         
         cin >> file_names[ i ];
         try
         {             
            dms.populateDirectory( file_names[ i ] );
         } 
         catch( exception e )
         {             
            cout << "Unable to read from file!" << endl;
         }
      }
   }
   else
   {
      for( int kiIndex = 1; kiIndex < aiArgc; kiIndex++ )
      {
         dms.populateDirectory( acpArgv[ kiIndex] );
      }
   }

   //This section should be replaced by an interactive menu      
   cout << "Querying the Directory Management System(DMS). Enter h for help or n to stop." << endl;
   cin >> response;          
   while( response != 'n' )
   {           
      if( response == 'h' )
      {
         mPrintMenu( );
      }
      else
      {
         dms.query( response );         
         dms.display_results( );
      }
      cout << "Querying the Directory Management System(DMS). Enter n to stop." << endl; 
      cin >> response;
   }          
   
   cout << "Exiting the Directory Management System." << endl;
   
   return 0; 
}

void mPrintMenu( void )
{
   cout << "n \t Stop program"                      << endl;
   cout << "h \t Display Help Menu"                 << endl;
   cout << "d \t Display entire directory"          << endl;
   cout << "1 \t Query by name ordered by category" << endl;
}
