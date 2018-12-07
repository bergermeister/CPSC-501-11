#include "Contact.h"
#include "PersonContact.h"
#include "BusinessContact.h"
#include "ContactDecorator.h"
#include "AddressDecorator.h"
#include "PhoneDecorator.h"
#include <iostream>

int main(int aiArgc, char** acpArgv)
{
	int kiStatus = 0;

	ContactDecorator* aopDecor = new ContactDecorator(new PersonContact("Ed E", "Male"));
	AddressDecorator* Add = new AddressDecorator(aopDecor, "Atlantic Street", "Bridgeport ", "Connecticut", "06604");
	PhoneDecorator* Phone = new PhoneDecorator(Add, "267 2030666");

	Phone->display();

	std::cin.get();

	return(kiStatus);
}
