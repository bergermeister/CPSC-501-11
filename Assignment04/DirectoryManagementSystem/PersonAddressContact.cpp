/**
 * @file       PersonAddressContact.cpp
 * @author     Zainab Al Taweel, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Person Address Contact class implementation
 */
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
	cout << "Person Address Contact    \t -> ";
   PersonContact::display( );
}

PersonAddressContact::~PersonAddressContact()  // Destructor
{
}
