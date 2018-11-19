/**
 * @file       PersonEmailContact.h
 * @author     Zainab Al Taweel, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Person Email Contact class interface
 */
#ifndef PersonEmailContact_h
#define PersonEmailContact_h

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

   virtual string MToString( void ) const;

private:
	string Email;
};

#endif

