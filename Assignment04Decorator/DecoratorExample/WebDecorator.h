/**
 * @file       WebDecorator.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Web Decorator class interface
 */
#ifndef WebDecorator_h
#define WebDecorator_h

#include"ContactDecorator.h"
#include<string>
#include<iostream>
using namespace std;

class WebDecorator:public ContactDecorator{

private:
	string Website;

public:

	WebDecorator(ContactDecorator* aopContact, string web);
	WebDecorator(const WebDecorator& aorDecorator);
	virtual ~WebDecorator(void);

	WebDecorator& operator=(const WebDecorator& aorDecorator);

	virtual void display(void) const;

	//WebDecorator();

};

#endif