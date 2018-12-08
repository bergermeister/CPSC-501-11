/**
 * @file       EmailDecorator.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Email Decorator class interface
 */
#ifndef EmailDecorator_h
#define EmailDecorator_h

#include"ContactDecorator.h"
#include<string>
#include<iostream>
using namespace std;

class EmailDecorator :public ContactDecorator {

private:
	string Email;

public:

	EmailDecorator(ContactDecorator* aopContact, string email);
	//EmailDecorator(ContactDecorator * aopContact, string email);
	EmailDecorator(const EmailDecorator& aorDecorator);
	virtual ~EmailDecorator(void);

	EmailDecorator& operator=(const EmailDecorator& aorDecorator);

	virtual void display(void) const;

}; 

#endif

