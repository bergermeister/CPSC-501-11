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

int main( int aiArgc, char** aiArgv )
{
   static const int xiCount = 6;

   int      kiStatus = 0;
   int      kiIndex;
   Contact* kopDir[ xiCount ];
   DMS      koDMS;

   koDMS.PopulateDirectory("Input1.txt");
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

   std::cin.get();

   return( kiStatus );
}