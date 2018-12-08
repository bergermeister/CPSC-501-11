/**
 * @file       main.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Main driver application for the Decorator Example
 */
#include "Contact.h"
#include "PersonContact.h"
#include "BusinessContact.h"
#include "ContactDecorator.h"
#include "AddressDecorator.h"
#include "PhoneDecorator.h"
#include "EmailDecorator.h"
#include "WebDecorator.h"
#include <iostream>

void testDecorators( Contact* aopContact );

int main(int aiArgc, char** acpArgv)
{
	int kiStatus = 0;

   testDecorators( new PersonContact( "Ed E", "Male" ) );
   std::cout << std::endl;
   testDecorators( new BusinessContact( "Sed LLC", "Law Firm" ) );

	std::cin.get();

	return(kiStatus);
}

void testDecorators( Contact* aopContact )
{
   ContactDecorator* aopDecor = new ContactDecorator( aopContact );
	AddressDecorator* aopAdd   = new AddressDecorator( aopDecor, "Atlantic Street", "Bridgeport ", "Connecticut", "06604" );
	PhoneDecorator*   aopPhone = new PhoneDecorator  ( aopAdd, "267 2030666" );
   EmailDecorator*   aopEmail = new EmailDecorator  ( aopPhone, "fake.email@gmail.com" );
   WebDecorator*     aopWeb   = new WebDecorator    ( aopEmail, "myhomepage.com" );

	aopWeb->display();

   delete aopWeb;
   delete aopEmail;
   delete aopPhone;
   delete aopAdd;
   delete aopDecor;
   delete aopContact;
}
