/**
 * @file       Contact.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Contact class implementation
 */
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
   if( this != &aorContact )
   {
      this->voName = aorContact.voName;
   }

   return( *this );
}

void Contact::display( void ) const
{
   std::cout << "Name:\t" << this->voName << std::endl;
}