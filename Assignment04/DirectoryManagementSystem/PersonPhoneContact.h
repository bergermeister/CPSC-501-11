
#include <string>
#include <iostream>
#include "PersonContact.h"
using namespace std;

class PersonPhoneContact : public PersonContact
{
public:
	PersonPhoneContact(const string & oName = "", const string & oGender = "", const int & oPhoneNo = ""); // Default constructor
	PersonPhoneContact(const PersonPhoneContact & oPPC);   // Copy Constructor
	PersonPhoneContact& operator = (const PersonPhoneContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~PersonPhoneContact(); // Virtual Destructor

private:
	int Phone;
};



#pragma once
