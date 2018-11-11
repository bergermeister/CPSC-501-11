/**
 * @file       BusinessContact.cpp
 * @author     Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Contact class implementation
 */
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
   std::cout << "Business Contact \t -> ";
   Contact::display( );
}
