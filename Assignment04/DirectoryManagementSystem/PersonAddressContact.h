
#include <string>
#include <iostream>
#include "PersonContact.h"
using namespace std;

class PersonAddressContact : public PersonContact
{
public:
	PersonAddressContact(const string & oName="", const string & oGender = "", const string & oAddress = ""); // Default constructor
	PersonAddressContact(const PersonAddressContact & oPAC);   // Copy Constructor
	PersonAddressContact& operator = (const PersonAddressContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~PersonAddressContact(); // Virtual Destructor

private:
	string Address;
};



