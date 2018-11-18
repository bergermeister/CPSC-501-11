/**
 * @file       BusinessAddressContact.h
 * @author     Udaya Sree Reddy Teegulla, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Address Contact class interface
 */
#ifndef BusinessAddressContact_h
#define BusinessAddressContact_h

#include <string>
#include <iostream>
#include "BusinessContact.h"
using namespace std;

class BusinessAddressContact : public BusinessContact
{
public:
	BusinessAddressContact(const string & oName="", const string & oCategory="", const string & oStreetAdd="", const string & oDistrict="",
		const string & oState = "", const string & oZipcode=""); // Default constructor
	BusinessAddressContact(const BusinessAddressContact & oPAC);   // Copy Constructor
	BusinessAddressContact& operator = (const BusinessAddressContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~BusinessAddressContact(); // Virtual Destructor

private:
	string StreetAddress;
	string District;
	string State;
	string ZipCode;
};

#endif
