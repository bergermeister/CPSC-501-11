/**
 * @file       AddressDecorator.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Address Decorator Class Interface
 */
#ifndef AddressDecorator_h
#define AddressDecorator_h

#include<string>
#include"Contact.h"
#include"ContactDecorator.h"

using namespace std;

class AddressDecorator :public ContactDecorator
{
private:
	string StreetAddress;
	string District;
	string State;
	string ZipCode;

public:
	AddressDecorator(Contact* Cont, const string & oStreetAdd = "", const string & oDistrict = "",
		const string & oState = "", const string & oZipcode = "");
	AddressDecorator(const AddressDecorator& AddDec);
	virtual ~AddressDecorator();
	AddressDecorator operator=(const AddressDecorator& AddDec);
	virtual void display() const;
};

#endif
