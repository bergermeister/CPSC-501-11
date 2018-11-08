#include "BusinessContact.h"
#include <string>
#include <iostream>

BusinessContact::BusinessContact( const std::string& aorName, const std::string& aorType )
   : Contact( aorName )
{
   this->voType = aorType;
}

BusinessContact::BusinessContact( const BusinessContact& aorBusiness )
{
   // Call assignment operator
   *this = aorBusiness;
}

BusinessContact::~BusinessContact( void )
{
   // Nothing to destruct
}

BusinessContact& BusinessContact::operator=( const BusinessContact& aorBusiness )
{
   // Copy Contact attributes
   Contact::operator=( static_cast< Contact >( aorBusiness ) );

   // Copy Business Contact attributes
   this->voType = aorBusiness.voType;

   return( *this );
}

void BusinessContact::display( void )
{
   std::cout << "Business Contact object" << std::endl;
}
