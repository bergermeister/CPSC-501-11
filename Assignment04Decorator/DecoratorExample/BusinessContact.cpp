#include "BusinessContact.h"
#include "Contact.h"
#include <string>
#include <iostream>

BusinessContact::BusinessContact( const std::string& aorName, const std::string& aorType )
   : Contact( aorName )
{
   this->voType = aorType;
}

BusinessContact::BusinessContact( const BusinessContact& aorContact )
{
   // Call assignment operator
   *this = aorContact;
}

BusinessContact::~BusinessContact( void )
{
   // Nothing to destruct
}

BusinessContact& BusinessContact::operator=( const BusinessContact& aorContact )
{
   if( this != &aorContact )
   {
      Contact::operator=( aorContact );
      this->voType = aorContact.voType;
   }

   return( *this );
}

void BusinessContact::display( void ) const
{
   Contact::display( );
   std::cout << "Type:\t" << this->voType << std::endl;
}
