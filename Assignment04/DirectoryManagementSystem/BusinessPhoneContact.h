#include <string>
#include <iostream>
#include "BusinessContact.h"
using namespace std;

class BusinessPhoneContact : public BusinessContact
{
public:
	BusinessPhoneContact(const string & oName = "", const string & oGender = "", const int & oPhoneNo = 0); // Default constructor
	BusinessPhoneContact(const BusinessPhoneContact & oPPC);   // Copy Constructor
	BusinessPhoneContact& operator = (const BusinessPhoneContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~BusinessPhoneContact(); // Virtual Destructor

private:
	int Phone;
};



#pragma once
