/**
 * @file       BusinessWebContact.h
 * @author     Udaya Sree Reddy Teegulla, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Web Contact class interface
 */
#ifndef BusinessWebContact_h
#define BusinessWebContact_h

#include <string>
#include <iostream>
#include "BusinessContact.h"
using namespace std;

class BusinessWebContact : public BusinessContact
{
public:
	BusinessWebContact(const string & oName = "", const string & oCategory = "", const string & Email = "", const string & oWebsite = ""); // Default constructor
	BusinessWebContact(const BusinessWebContact & oBWC);   // Copy Constructor
	BusinessWebContact& operator = (const BusinessWebContact & oBWC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~BusinessWebContact(); // Virtual Destructor

private:
	string Email;
	string Website;
};

#endif

