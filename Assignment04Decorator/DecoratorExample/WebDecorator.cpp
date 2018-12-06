#include"WebDecorator.h"
#include"ContactDecorator.h"
#include"Contact.h"
#include<string>
#include<iostream>
using namespace std;

//WebDecorator::WebDecorator{

//}

WebDecorator::WebDecorator(Contact* aopContact, string web) :ContactDecorator(aopContact)
{ 
	Website = web; 

}

WebDecorator::WebDecorator(const WebDecorator& aorDecorator){

	*this = aorDecorator;
}

WebDecorator::~WebDecorator(void ){

}

WebDecorator& WebDecorator::operator=(const WebDecorator& aorDecorator)
{
	if (this != &aorDecorator)
	{
		this->vopContact = aorDecorator.vopContact;
	}

	return(*this);
}

void WebDecorator::display(void) const
{
	if (this->vopContact != nullptr)
	{
		this->vopContact->display();
	}
}

