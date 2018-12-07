#include "AddressDecorator.h"
#include<iostream>
#include "Contact.h"



AddressDecorator::AddressDecorator(Contact* Cont, const string & oStreetAdd, const string & oDistrict,
	const string & oState, const string & oZipcode): ContactDecorator(Cont)
{
	this->StreetAddress = oStreetAdd;
	this->District = oDistrict;
	this->State = oState;
	this->ZipCode = oZipcode;
}

AddressDecorator::AddressDecorator(const AddressDecorator& AddDec):ContactDecorator(AddDec)
{
	*this = AddDec;
}

AddressDecorator::~AddressDecorator()
{

}

AddressDecorator AddressDecorator::operator=(const AddressDecorator & AddDec)
{
	this->StreetAddress = AddDec.StreetAddress;
	this->District = AddDec.District;
	this->State = AddDec.State;
	this->ZipCode = AddDec.ZipCode;
	return *this;
}

void AddressDecorator::display() const
{
	ContactDecorator::display();
	cout << "Contact Address: \n";
	cout << "Street Address: \t" << StreetAddress << " \n District: \t " << District << "\n State: \t" << State << "\n Zip Code: \t" << ZipCode <<"\n";
}
