#include "BusinessWebContact.h"
#include <string>
#include <iostream>

using namespace std;


BusinessWebContact::BusinessWebContact(const string & oName, const string & oGender, const string & oWebsite)
	: BusinessContact(oName, oGender) // Deafult Constructor
{
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