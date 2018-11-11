#include <string>
#include <iostream>
#include "BusinessContact.h"
using namespace std;

class BusinessWebContact : public BusinessContact
{
public:
	BusinessWebContact(const string & oName = "", const string & oGender = "", const string & oWebsite = ""); // Default constructor
	BusinessWebContact(const BusinessWebContact & oBWC);   // Copy Constructor
	BusinessWebContact& operator = (const BusinessWebContact & oBWC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~BusinessWebContact(); // Virtual Destructor

private:
	string Website;
};

