#include "PersonContact.h"
#include <string>
#include <iostream>

PersonContact::PersonContact( const std::string& aorName, const std::string& aorGender )
   : Contact( aorName )
{
   this->voGender = aorGender;
}

PersonContact::PersonContact( const PersonContact& aorContact )
{
   // Call assignment operator
   *this = aorContact;
}

PersonContact::~PersonContact( void )
{
   // Nothing to destruct
}

PersonContact& PersonContact::operator=( const PersonContact& aorPerson )
{
   // Copy Contact attributes
   Contact::operator=( static_cast< Contact >( aorPerson ) );

   // Copy PersonContact attributes
   this->voGender = aorPerson.voGender;

   return( *this );
}

void PersonContact::display( void )
{
   std::cout << "Person Contact object" << std::endl;
}
