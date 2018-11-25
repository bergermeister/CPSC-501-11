/**
 * @file       BusinessPhoneContact.cpp
 * @author     Udaya Sree Reddy Teegulla, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Phone Contact class implementation
 */
#include "BusinessPhoneContact.h"
#include <string>
#include <iostream>

using namespace std;


BusinessPhoneContact::BusinessPhoneContact(const string & oName, const string & oCategory, const string & oPhoneNo)
	: BusinessContact(oName, oCategory) // Deafult Constructor
{
	this->Phone = oPhoneNo;
}

BusinessPhoneContact::BusinessPhoneContact(const BusinessPhoneContact & oBPC) // Copy constructor
{
	*this = oBPC;
}

BusinessPhoneContact & BusinessPhoneContact::operator=(const BusinessPhoneContact & oBPC) // Copy Constructor 
{
	BusinessContact::operator=(static_cast<BusinessContact>(oBPC));
	this->Phone = oBPC.Phone;
	return *this;
}

void BusinessPhoneContact::display(void)
{
	cout << "Business Phone Contact    \t -> ";
   BusinessContact::display( );
}

BusinessPhoneContact::~BusinessPhoneContact()  // Destructor
{
}


string BusinessPhoneContact::GetBusinessPhone()
{
	return Phone;
}

std::string BusinessPhoneContact::MToString( void ) const
{
   return( std::string( "Phone number:\t" + this->Phone ) );
}
