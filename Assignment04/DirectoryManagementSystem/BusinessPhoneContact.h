/**
 * @file       BusinessPhoneContact.h
 * @author     Udaya Sree Reddy Teegulla, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Phone Contact class interface
 */
#ifndef BusinessPhoneContact_h
#define BusinessPhoneContact_h

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

#endif

