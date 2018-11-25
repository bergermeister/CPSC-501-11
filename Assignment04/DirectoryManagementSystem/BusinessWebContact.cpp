/**
 * @file       BusinessWebContact.cpp
 * @author     Udaya Sree Reddy Teegulla, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Web Contact class implementation
 */
#include "BusinessWebContact.h"
#include <string>
#include <iostream>

using namespace std;


BusinessWebContact::BusinessWebContact(const string & oName, const string & oCategory, const string & oEmail, const string & oWebsite)
	: BusinessContact(oName, oCategory) // Deafult Constructor
{
   this->Email   = oEmail;
	this->Website = oWebsite;
}

BusinessWebContact::BusinessWebContact(const BusinessWebContact & oBWC) // Copy constructor
{
	*this = oBWC;
}

BusinessWebContact & BusinessWebContact::operator=(const BusinessWebContact & oBWC) // Copy Constructor 
{
	BusinessContact::operator=(static_cast<BusinessContact>(oBWC));
	this->Website = oBWC.Website;
	this->Email = oBWC.Email;
	return *this;
}

void BusinessWebContact::display(void)
{
	cout << "Business Web Contact    \t -> ";
   BusinessContact::display( );
}

BusinessWebContact::~BusinessWebContact()  // Destructor
{
}

string BusinessWebContact::MToString(void) const
{
	return( string( "Email:    \t\t" + this->Email) + "\n" +
           string( "Website:  \t\t" + this->Website));
}

string BusinessWebContact::GetBusinessEmail()
{
	return( this->Email );
}

string BusinessWebContact::GetWebsite( void ) const
{
   return( this->Website );
}
