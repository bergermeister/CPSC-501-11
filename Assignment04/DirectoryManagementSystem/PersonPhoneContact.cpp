#include "PersonPhoneContact.h"
#include <string>
#include <iostream>

using namespace std;


PersonPhoneContact::PersonPhoneContact(const string & oName, const string & oGender, const int & oPhoneNo)
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
	Contact::display();
	PersonContact::display();
	cout << " The Phone Number is  is " << Phone;
}

PersonPhoneContact::~PersonPhoneContact()  // Destructor
{
}
