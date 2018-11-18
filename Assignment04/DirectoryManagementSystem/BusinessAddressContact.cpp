/**
 * @file       BusinessAddressContact.cpp
 * @author     Udaya Sree Reddy Teegulla, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Address Contact class implementation
 */
#include "BusinessAddressContact.h"
#include <string>
#include <iostream>

using namespace std;


BusinessAddressContact::BusinessAddressContact(const string & oName, const string & oCategory, const string & oStreetAdd, const string & oDistrict,
	const string & oState, const string & oZipcode)
	: BusinessContact(oName, oCategory) // Deafult Constructor
{
	this->StreetAddress = oStreetAdd;
	this->District = oDistrict;
	this->State = oState;
	this->ZipCode = oZipcode;
}

BusinessAddressContact::BusinessAddressContact(const BusinessAddressContact & oBAC) // Copy constructor
{
	*this = oBAC;
}

BusinessAddressContact & BusinessAddressContact::operator=(const BusinessAddressContact & oPAC) // Copy Constructor 
{
	BusinessContact::operator=(static_cast<BusinessContact>(oPAC));
	this->StreetAddress = oPAC.StreetAddress;
	this->District = oPAC.District;
	this->State = oPAC.State;
	this->ZipCode = oPAC.ZipCode;
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

string BusinessAddressContact::MGetState( void ) const
{
   return( this->State );
}
