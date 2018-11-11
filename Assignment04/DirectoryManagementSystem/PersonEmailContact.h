#pragma once

#include <string>
#include <iostream>
#include "PersonContact.h"
using namespace std;

class PersonEmailContact : public PersonContact
{
public:
	PersonEmailContact(const string & oName = "", const string & oGender = "", const string & oEmail = ""); // Default constructor
	PersonEmailContact(const PersonEmailContact & oPEC);   // Copy Constructor
	PersonEmailContact& operator = (const PersonEmailContact & oPEC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~PersonEmailContact(); // Virtual Destructor

private:
	string Email;
};



