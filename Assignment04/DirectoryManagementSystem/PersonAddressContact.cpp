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


PersonAddressContact::PersonAddressContact(const string & oName, const string & oGender, const string & oStreetAdd, const string & oDistrict,
	const string & oState, const string & oZipcode)
	: PersonContact(oName, oGender) // Deafult Constructor
{
	this->StreetAddress = oStreetAdd;
	this->District = oDistrict;
	this->State = oState;
	this->ZipCode = oZipcode;
}

PersonAddressContact::PersonAddressContact(const PersonAddressContact & oPAC) // Copy constructor
{
	*this = oPAC;
}

PersonAddressContact & PersonAddressContact::operator=(const PersonAddressContact & oPAC) // Copy Constructor 
{
	PersonContact::operator=(static_cast<PersonContact>(oPAC));
	this->StreetAddress = oPAC.StreetAddress;
	this->District = oPAC.District;
	this->State = oPAC.State;
	this->ZipCode = oPAC.ZipCode;
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
