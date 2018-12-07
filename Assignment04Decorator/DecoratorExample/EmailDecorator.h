#include"ContactDecorator.h"
#include<string>
#include<iostream>
using namespace std;

class EmailDecorator :public ContactDecorator {

private:
	string Email;
	Contact *vopContact;
public:

	EmailDecorator(ContactDecorator* aopContact, string email);
	//EmailDecorator(ContactDecorator * aopContact, string email);
	EmailDecorator(const EmailDecorator& aorDecorator);
	virtual ~EmailDecorator(void);

	EmailDecorator& operator=(const EmailDecorator& aorDecorator);

	virtual void display(void) const;

}; 
