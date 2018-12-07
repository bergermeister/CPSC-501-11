#include"WebDecorator.h"
#include"ContactDecorator.h"
#include"Contact.h"
#include<string>
#include<iostream>
using namespace std;

WebDecorator::WebDecorator(ContactDecorator* aopContact, string web) :ContactDecorator(*aopContact)
{  
	Website = web; 

}

WebDecorator::WebDecorator(const WebDecorator& aorDecorator):ContactDecorator(aorDecorator){

	*this = aorDecorator;
}

WebDecorator::~WebDecorator(void ){

}

WebDecorator& WebDecorator::operator=(const WebDecorator& aorDecorator)
{
	if (this != &aorDecorator)
	{
		ContactDecorator::operator=(aorDecorator);
		Website = aorDecorator.Website;
	}

	return(*this);
}

void WebDecorator::display(void) const
{
	ContactDecorator::display();
	cout << "Website:\t" << Website<< endl;
}

