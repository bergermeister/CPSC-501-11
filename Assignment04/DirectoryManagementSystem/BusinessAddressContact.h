#include <string>
#include <iostream>
#include "BusinessContact.h"
using namespace std;

class BusinessAddressContact : public BusinessContact
{
public:
	BusinessAddressContact(const string & oName = "", const string & oGender = "", const string & oAddress = ""); // Default constructor
	BusinessAddressContact(const BusinessAddressContact & oPAC);   // Copy Constructor
	BusinessAddressContact& operator = (const BusinessAddressContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~BusinessAddressContact(); // Virtual Destructor

private:
	string Address;
};
