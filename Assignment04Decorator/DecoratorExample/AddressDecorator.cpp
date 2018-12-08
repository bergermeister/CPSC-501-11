/**
 * @file       AddressDecorator.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Address Decorator class implementation
 */
#include "AddressDecorator.h"
#include <iostream>
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
	cout << "Address: \n";
	cout << "\tStreet Address:\t" << StreetAddress << " \n\tDistrict:\t " << District << "\n\tState:\t\t" << State << "\n\tZip Code:\t" << ZipCode <<"\n";
}
