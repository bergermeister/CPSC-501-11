#include "PersonAddressContact.h"
#include <string>
#include <iostream>

using namespace std;


PersonAddressContact::PersonAddressContact(const string & oName, const string & oGender, const string & oAddress) 
	: PersonContact(oName, oGender) // Deafult Constructor
{
	this->Address = oAddress;
}

PersonAddressContact::PersonAddressContact(const PersonAddressContact & oPAC) // Copy constructor
{
	*this = oPAC;
}

PersonAddressContact & PersonAddressContact::operator=(const PersonAddressContact & oPAC) // Copy Constructor 
{
	PersonContact::operator=(static_cast<PersonContact>(oPAC));
	this->Address = oPAC.Address;
	return *this;
}

void PersonAddressContact::display(void)
{
	Contact::display(); 
	PersonContact::display();
	cout << " The address is " << Address;
}

PersonAddressContact::~PersonAddressContact()  // Destructor
{
}
