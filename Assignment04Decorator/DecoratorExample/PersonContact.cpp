#include "PersonContact.h"
#include "Contact.h"
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

PersonContact& PersonContact::operator=( const PersonContact& aorContact )
{
   if( this != &aorContact )
   {
      Contact::operator=( static_cast< Contact >( aorContact ) );
      this->voGender = aorContact.voGender;
   }

   return( *this );
}

void PersonContact::display( void ) const
{
   Contact::display( );
   std::cout << "Gender:\t" << this->voGender << std::endl;
}