/**
 * @file       PersonPhoneContact.h
 * @author     Zainab Al Taweel, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Person Phone Contact class interface
 */
#ifndef PersonPhoneContact_h
#define PersonPhoneContact_h

#include <string>
#include <iostream>
#include "PersonContact.h"
using namespace std;

class PersonPhoneContact : public PersonContact
{
public:
	PersonPhoneContact(const string & oName = "", const string & oGender = "", const string & oPhoneNo = ""); // Default constructor
	PersonPhoneContact(const PersonPhoneContact & oPPC);   // Copy Constructor
	PersonPhoneContact& operator = (const PersonPhoneContact & oPAC);  // = operator overloading
	virtual void display(void);  // modified display functoin 
	virtual ~PersonPhoneContact(); // Virtual Destructor

   virtual std::string MToString( void ) const;

private:
	string Phone;
};

#endif
