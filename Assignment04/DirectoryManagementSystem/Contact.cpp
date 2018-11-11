#include "Contact.h"
#include <string>
#include <iostream>

Contact::Contact( const std::string& aorName )
{
   this->voName = aorName;
}

Contact::Contact( const Contact& aorContact )
{
   // Call assignment operator
   *this = aorContact;
}

Contact::~Contact( void )
{
   // Nothing to destruct
}

Contact& Contact::operator=( const Contact& aorContact )
{
   // Copy Contact attributes
   this->voName = aorContact.voName;

   return( *this );
}

void Contact::display( void )
{
   std::cout << "Contact" << std::endl;
}
