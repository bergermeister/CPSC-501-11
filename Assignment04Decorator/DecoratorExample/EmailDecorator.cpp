#include"EmailDecorator.h"
#include"ContactDecorator.h"
#include"Contact.h"
#include<string>
#include<iostream>
using namespace std;

EmailDecorator::EmailDecorator(Contact* aopContact, string email) :ContactDecorator(aopContact)
{
	Email = email;

}

EmailDecorator::EmailDecorator(const EmailDecorator& aorDecorator) {
	*this = aorDecorator;
}

EmailDecorator::~EmailDecorator(void) {

}

EmailDecorator& EmailDecorator::operator=(const EmailDecorator& aorDecorator)
{
	if (this != &aorDecorator)
	{
		this->vopContact = aorDecorator.vopContact;
	}

	return(*this);
}

void EmailDecorator::display(void) const
{
	if (this->vopContact != nullptr)
	{
		this->vopContact->display();
	}
}


