#include"ContactDecorator.h"
#include<string>
#include<iostream>
using namespace std;

class WebDecorator:public ContactDecorator{

private:
	string Website;
	ContactDecorator *vopContact;
public:

	WebDecorator(ContactDecorator* aopContact, string web);
	WebDecorator(const WebDecorator& aorDecorator);
	virtual ~WebDecorator(void);

	WebDecorator& operator=(const WebDecorator& aorDecorator);

	virtual void display(void) const;

	//WebDecorator();

};