#include "BusinessPhoneContact.h"
#include <string>
#include <iostream>

using namespace std;


BusinessPhoneContact::BusinessPhoneContact(const string & oName, const string & oGender, const int & oPhoneNo)
	: BusinessContact(oName, oGender) // Deafult Constructor
{
	this->Phone = oPhoneNo;
}

BusinessPhoneContact::BusinessPhoneContact(const BusinessPhoneContact & oBPC) // Copy constructor
{
	*this = oBPC;
}

BusinessPhoneContact & BusinessPhoneContact::operator=(const BusinessPhoneContact & oBPC) // Copy Constructor 
{
	BusinessContact::operator=(static_cast<BusinessContact>(oBPC));
	this->Phone = oBPC.Phone;
	return *this;
}

void BusinessPhoneContact::display(void)
{
	Contact::display();
	BusinessContact::display();
	cout << " The Phone Number is  is " << Phone;
}

BusinessPhoneContact::~BusinessPhoneContact()  // Destructor
{
}