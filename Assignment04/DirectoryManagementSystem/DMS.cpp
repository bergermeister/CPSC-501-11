#include "DMS.h"
#include "Contact.h"
#include "PersonContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "PersonEmailContact.h"
#include <string>
#include <map>

DMS::DMS( void )
{
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonPhoneContact  ( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonAddressContact( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonEmailContact  ( "Edward Eisenberger" ) ) );

   for( auto koIter = voDirectory.begin( ); koIter != voDirectory.end( ); koIter++ )
   {
      koIter->second->display( );
   }
}

DMS::~DMS( void )
{
   // Delete all contacts to free memory
   for( auto koIter = voDirectory.begin( ); koIter != voDirectory.end( ); koIter++ )
   {
      delete koIter->second;
   }
}
