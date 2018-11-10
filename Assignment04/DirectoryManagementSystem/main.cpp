#include "Contact.h"
#include "PersonContact.h"
#include "BusinessContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "PersonEmailContact.h"

int main( int aiArgc, char** aiArgv )
{
   static const int xiCount = 6;

   int      kiStatus = 0;
   int      kiIndex;
   Contact* kopDir[ xiCount ];

   kopDir[ 0 ] = new PersonAddressContact();
   kopDir[ 1 ] = new PersonPhoneContact();
   kopDir[ 2 ] = new PersonEmailContact();
   kopDir[ 3 ] = new BusinessAddressContact();
   kopDir[ 4 ] = new BusinessPhoneContact();
   kopDir[ 5 ] = new BusinessWebContact(); 

   for( kiIndex = 0; kiIndex < xiCount; kiIndex++ )
   {
      kopDir[ kiIndex ]->display( );
   }

   return( kiStatus );
}