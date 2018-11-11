#include "PersonEmailContact.h"
#include <string>
#include <iostream>

using namespace std;


PersonEmailContact::PersonEmailContact(const string & oName, const string & oGender, const string & oEmail)
	: PersonContact(oName, oGender) // Deafult Constructor
{
	this->Email = oEmail;
}

PersonEmailContact::PersonEmailContact(const PersonEmailContact & oPEC) // Copy constructor
{
	*this = oPEC;
}

PersonEmailContact & PersonEmailContact::operator=(const PersonEmailContact & oPEC) // Copy Constructor 
{
	PersonContact::operator=(static_cast<PersonContact>(oPEC));
	this->Email = oPEC.Email;
	return *this;
}

void PersonEmailContact::display(void)
{
	cout << "Person Email Contact    \t -> ";
   PersonContact::display( );
}

PersonEmailContact::~PersonEmailContact()  // Destructor
{
}