#pragma once
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
