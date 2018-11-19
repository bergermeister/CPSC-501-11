/**
 * @file       PersonAddressContact.h
 * @author     Zainab Al Taweel, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Person Address Contact class interface
 */
#ifndef PersonAddressContact_h
#define PersonAddressContact_h

#include <string>
#include <iostream>
#include "PersonContact.h"
using namespace std;

class PersonAddressContact : public PersonContact
{
public:
	PersonAddressContact(const string & oName="", const string & oGender = "", const string & oStreetAdd = "", const string & oDistrict = "",
		const string & oState = "", const string & oZipcode = ""); // Default constructor
	PersonAddressContact(const PersonAddressContact & oPAC);   // Copy Constructor
	PersonAddressContact& operator = (const PersonAddressContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~PersonAddressContact(); // Virtual Destructor

   string MGetState( void ) const;
   virtual std::string MToString( void ) const;

private:
	string StreetAddress;
	string District;
	string State;
	string ZipCode;
};

#endif

