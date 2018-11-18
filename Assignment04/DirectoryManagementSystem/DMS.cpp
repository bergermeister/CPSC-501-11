#include "DMS.h"
#include "Contact.h"
#include "PersonContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "PersonEmailContact.h"
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>

DMS::DMS( void )
{
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonPhoneContact  ( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonAddressContact( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonEmailContact  ( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Zainab Al Taweel", new PersonPhoneContact  ( "Zainab Al Taweel" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Zainab Al Taweel", new PersonAddressContact( "Zainab Al Taweel" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Zainab Al Taweel", new PersonEmailContact  ( "Zainab Al Taweel" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Udaya Sree Reddy Teegulla", new PersonPhoneContact  ( "Udaya Sree Reddy Teegulla " ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Udaya Sree Reddy Teegulla", new PersonAddressContact( "Udaya Sree Reddy Teegulla " ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Udaya Sree Reddy Teegulla", new PersonEmailContact  ( "Udaya Sree Reddy Teegulla " ) ) );

   std::cout << "Contact Types for Edward Eisenberger: " << std::endl;
   for( auto koIter = voDirectory.lower_bound( "Edward Eisenberger" ); 
        koIter != voDirectory.upper_bound( "Edward Eisenberger" ); 
        koIter++ )
   {
      std::cout << "Key: " + koIter->first + " \t|\t Type of Value: ";
      std::cout << typeid( *koIter->second ).name( ) << std::endl;
   }
}

DMS::DMS( const DMS& aorDMS )
{
   // Call assignment operator
   *this = aorDMS;
}

DMS::~DMS( void )
{
   // Delete all contacts to free memory
   for( auto koIter = voDirectory.begin( ); koIter != voDirectory.end( ); koIter++ )
   {
      delete koIter->second;
   }
}

DMS& DMS::operator=( const DMS& aorDMS )
{
   // Prevent self copy
   if( this != &aorDMS )
   {
      // Copy directory
      this->voDirectory = aorDMS.voDirectory;
   }

   return( *this );
}

void DMS::populateDirectory( const std::string& aorFile )
{

}

void DMS::query( const char acResponse )
{
   using namespace std;

   //vector< string > koWords = Contact::mSplit( aorResponse, ' ' );
   //multimap< string, Contact* >::iterator koIter;

   switch( acResponse )
   {
   case 'f':   // Query by first name
      this->mQueryFirstName( );
      break;
   case 'l':   // Query by last name
      break;
   case 'w':   // Query by whole name
      break;
   }
}

void mQueryHelper( const std::vector< std::string >& aorWords, const int aiIndex )
{

}

void mQueryFirstName( void )
{
   using namespace std;

   string koFirstName;
   char   kcOrder;

   cout << "Enter the contact's first name: ";
   cin  >> koFirstName;

   cout << "Enter order column:";
   cin  >> kcOrder;

   
}
