/**
 * @file       PhoneDecorator.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Phone Decorator class interface
 */
#ifndef PhoneDecorator_h
#define PhoneDecorator_h

#include<string>
#include"Contact.h"
#include"ContactDecorator.h"

using namespace std;

class PhoneDecorator :public ContactDecorator
{
private:
	string PhoneNumber;

public:
	PhoneDecorator(Contact* Cont, const string & oPhoneNo);
	PhoneDecorator(const PhoneDecorator& AddDec);
	virtual ~PhoneDecorator();
	PhoneDecorator operator=(const PhoneDecorator& AddDec);
	virtual void display() const;
};

#endif
