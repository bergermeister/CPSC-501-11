/**
 * @file       EmailDecorator.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Email Decorator class implementation
 */
#include"EmailDecorator.h"
#include"ContactDecorator.h"
#include"Contact.h"
#include<string>
#include<iostream>
using namespace std;

EmailDecorator::EmailDecorator(ContactDecorator* aopContact, string email):ContactDecorator(*aopContact)
{
	Email = email;

}

EmailDecorator::EmailDecorator(const EmailDecorator& aorDecorator):ContactDecorator(aorDecorator){

	
	*this = aorDecorator;
}

EmailDecorator::~EmailDecorator(void) {

}

EmailDecorator& EmailDecorator::operator=(const EmailDecorator& aorDecorator)
{
	if (this != &aorDecorator) {
		ContactDecorator::operator=(aorDecorator);
		Email = aorDecorator.Email;
	}

	return(*this);
}

void EmailDecorator::display(void) const
{
	ContactDecorator::display();
	cout << "Email:\t" << Email << endl;
}


