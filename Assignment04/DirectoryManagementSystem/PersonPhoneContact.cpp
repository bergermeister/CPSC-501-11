/**
 * @file       PersonPhoneContact.cpp
 * @author     Zainab Al Taweel, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Person Phone Contact class implementation
 */
#include "PersonPhoneContact.h"
#include <string>
#include <iostream>

using namespace std;


PersonPhoneContact::PersonPhoneContact(const string & oName, const string & oGender, const string & oPhoneNo)
	: PersonContact(oName, oGender) // Deafult Constructor
{
	this->Phone = oPhoneNo;
}

PersonPhoneContact::PersonPhoneContact(const PersonPhoneContact & oPPC) // Copy constructor
{
	*this = oPPC;
}

PersonPhoneContact & PersonPhoneContact::operator=(const PersonPhoneContact & oPPC) // Copy Constructor 
{
	PersonContact::operator=(static_cast<PersonContact>(oPPC));
	this->Phone = oPPC.Phone;
	return *this;
}

void PersonPhoneContact::display(void)
{
	cout << this->Phone;
}

PersonPhoneContact::~PersonPhoneContact()  // Destructor
{
}

string PersonPhoneContact::MToString( void ) const
{
   return( "Phone Number:\t" + this->Phone );
}

string PersonPhoneContact::GetPersonPhone()
{
	return Phone;
}

