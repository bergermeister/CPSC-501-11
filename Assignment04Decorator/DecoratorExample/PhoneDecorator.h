#pragma once
#pragma once
#include<string>
#include"Contact.h"
#include"ContactDecorator.h"

using namespace std;

class PhoneDecorator :public ContactDecorator
{
private:
	string PhoneNumber;

public:
	PhoneDecorator(Contact* Cont, const string & oPhoneNo);
	PhoneDecorator(const PhoneDecorator& AddDec);
	virtual ~PhoneDecorator();
	PhoneDecorator operator=(const PhoneDecorator& AddDec);
	virtual void display() const;
};
