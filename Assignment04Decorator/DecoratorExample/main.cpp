#include "Contact.h"
#include "PersonContact.h"
#include "BusinessContact.h"
#include "ContactDecorator.h"
#include <iostream>

int main( int aiArgc, char** acpArgv )
{
   int kiStatus = 0;
   ContactDecorator* aopDecor = new ContactDecorator( new PersonContact( "Ed E", "Male" ) );

   aopDecor->display( );

   std::cin.get( );

   return( kiStatus );
}