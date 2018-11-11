#include "BusinessAddressContact.h"
#include <string>
#include <iostream>

using namespace std;


BusinessAddressContact::BusinessAddressContact(const string & oName, const string & oGender, const string & oAddress)
	: BusinessContact(oName, oGender) // Deafult Constructor
{
	this->Address = oAddress;
}

BusinessAddressContact::BusinessAddressContact(const BusinessAddressContact & oBAC) // Copy constructor
{
	*this = oBAC;
}

BusinessAddressContact & BusinessAddressContact::operator=(const BusinessAddressContact & oPAC) // Copy Constructor 
{
	BusinessContact::operator=(static_cast<BusinessContact>(oPAC));
	this->Address = oPAC.Address;
	return *this;
}

void BusinessAddressContact::display(void)
{
	cout << "Business Address Contact    \t -> ";
   BusinessContact::display( );
}

BusinessAddressContact::~BusinessAddressContact()  // Destructor
{
}