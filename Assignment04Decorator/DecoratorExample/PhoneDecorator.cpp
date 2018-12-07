#include "PhoneDecorator.h"
#include<iostream>

PhoneDecorator::PhoneDecorator(Contact* Cont, const string & oPhoneNo):ContactDecorator(Cont)
{
	this->PhoneNumber = oPhoneNo;
}

PhoneDecorator::PhoneDecorator(const PhoneDecorator & AddDec):ContactDecorator(AddDec)
{
	*this = AddDec;
}

PhoneDecorator::~PhoneDecorator()
{

}

PhoneDecorator PhoneDecorator::operator=(const PhoneDecorator & AddDec)
{
	this->PhoneNumber = AddDec.PhoneNumber;
	return *this;
}

void PhoneDecorator::display() const
{
	ContactDecorator::display();
	cout << "\n Contact Phone Number: \t" << PhoneNumber;
}
