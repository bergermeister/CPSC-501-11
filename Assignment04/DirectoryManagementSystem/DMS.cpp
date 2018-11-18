#include "DMS.h"
#include "Contact.h"
#include "PersonContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "PersonEmailContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessAddressContact.h"
#include "BusinessWebContact.h"
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

inline void split(const string& s, vector<string>& v) // Split function to seprate each piece of information and store it in a vector
// ref: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s24.html
{
	int i = 0;
	int j = s.find(",");

	while (j >= 0)
	{
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(",", j);

		if (j < 0)
		{
			v.push_back(s.substr(i, s.length()));
		}
	}
}
DMS::DMS( void )
{/*
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonPhoneContact  ( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonAddressContact( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Edward Eisenberger", new PersonEmailContact  ( "Edward Eisenberger" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Zainab Al Taweel", new PersonPhoneContact  ( "Zainab Al Taweel" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Zainab Al Taweel", new PersonAddressContact( "Zainab Al Taweel" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Zainab Al Taweel", new PersonEmailContact  ( "Zainab Al Taweel" ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Udaya Sree Reddy Teegulla", new PersonPhoneContact  ( "Udaya Sree Reddy Teegulla " ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Udaya Sree Reddy Teegulla", new PersonAddressContact( "Udaya Sree Reddy Teegulla " ) ) );
   voDirectory.insert( std::pair< std::string, Contact* >( "Udaya Sree Reddy Teegulla", new PersonEmailContact  ( "Udaya Sree Reddy Teegulla " ) ) );

   std::cout << "Contact Types for Edward Eisenberger: " << std::endl;
   for( auto koIter = voDirectory.lower_bound( "Edward Eisenberger" ); 
        koIter != voDirectory.upper_bound( "Udaya Sree Reddy Teegulla" ); 
        koIter++ )
   {
      std::cout << "Key: " + koIter->first + " \t|\t Type of Value: ";
      std::cout << typeid( *koIter->second ).name( ) << std::endl;
   }
   */
}

void DMS::CreateDirectory(string Name, Contact* ContInfo)
{
	voDirectory.insert(pair<string, Contact*>(Name, ContInfo));
}

void DMS::DisplayDirectory()
{
	for (auto koIter = voDirectory.begin(); koIter != voDirectory.end(); koIter++)
	{
		cout << "Key: " + koIter->first + " \t|\t Type of Value: ";
		cout << typeid(*koIter->second).name() << std::endl;
	}
}

DMS::DMS( const DMS& aorDMS )
{
   // Call assignment operator
   *this = aorDMS;
}

DMS::~DMS( void )
{
   // Delete all contacts to free memory
   for( auto koIter = voDirectory.begin( ); koIter != voDirectory.end( ); koIter++ )
   {
      delete koIter->second;
   }
}

void DMS::PopulateDirectory(string FileName)
{
	// the number of contacts in the file
	string ContType; // the type of contact weather it is person or business
	ifstream inFile;
	inFile.open(FileName);
	if (!inFile.is_open()) //Failed to open file
	{
		cout << " Could not open the file  " << FileName << endl;
		cout << "Program terminating. \n";
		exit(EXIT_FAILURE);
	}
	string FirstLine;
	getline(inFile, FirstLine);

	vector<string>* p;
	p = new vector<string>();
	split(FirstLine, *p);
	for (unsigned i = 0; i < p->size(); i++)
		cout << p->at(i) << "\n";
	int const ContNum = stoi(p->at(0));
	ContType = p->at(1);
	p->clear();

	Contact* PersonContacts[18]; // create array of pointers of type Contact. This array should be of constant size, I dont know how to do it here.

	if (ContType == "person")
	{
		string Line;
		string Name;
		string Gender;
		string Phone;
		string Email;
		string PoBox;
		string StreetAdd;
		string District;
		string State;
		string ZipCode;
		
		DMS Directory;
		for (int i = 0; i < 6; i++)
		{
			getline(inFile, Line);
			vector<string>* p;
			p = new vector<string>();
			split(Line, *p);
			if (p->size() == 9)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender= p->at(1);
				Phone = p->at(2);
				Email = p->at(3);
				PoBox = p->at(4);
				StreetAdd = p->at(5);
				District = p->at(6);
				State = p->at(7);
				ZipCode = p->at(8);
				StreetAdd = PoBox + StreetAdd;
				p->clear();

				PersonContacts[i] = new PersonPhoneContact(Name, Gender, Phone);
				PersonContacts[i + 1] = new PersonEmailContact(Name, Gender, Email);
				PersonContacts[i + 2] = new PersonAddressContact(Name, Gender, StreetAdd, District, State, ZipCode);

				Directory.CreateDirectory(Name, PersonContacts[i]);
				Directory.CreateDirectory(Name, PersonContacts[i + 1]);
				Directory.CreateDirectory(Name, PersonContacts[i + 2]);

			}
			if (p->size() == 8)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);
				Email = p->at(3);
				StreetAdd = p->at(4);
				District = p->at(5);
				State = p->at(6);
				ZipCode = p->at(7);

				p->clear();
				PersonContacts[i] = new PersonPhoneContact(Name, Gender, Phone);
				PersonContacts[i + 1] = new PersonEmailContact(Name, Gender, Email);
				PersonContacts[i + 2] = new PersonAddressContact(Name, Gender, StreetAdd, District, State, ZipCode);

				Directory.CreateDirectory(Name, PersonContacts[i]);
				Directory.CreateDirectory(Name, PersonContacts[i + 1]);
				Directory.CreateDirectory(Name, PersonContacts[i + 2]);

			}
			else if (p->size() == 4)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);
				Email = p->at(3);
				
				p->clear();
				PersonContacts[i] = new PersonPhoneContact(Name, Gender, Phone);
				PersonContacts[i + 1] = new PersonEmailContact(Name, Gender, Email);
				
				Directory.CreateDirectory(Name, PersonContacts[i]);
				Directory.CreateDirectory(Name, PersonContacts[i + 1]);
			}
			else if (p->size() == 3)
			{
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);

				p->clear();
				PersonContacts[i] = new PersonPhoneContact(Name, Gender, Phone);

				Directory.CreateDirectory(Name, PersonContacts[i]);
			}
		}
		Directory.DisplayDirectory();
	}

	if (ContType == "business")
	{
		string Line;
		string Name;
		string Gender;
		string Phone;
		string Email;
		string web;
		string PoBox;
		string StreetAdd;
		string District;
		string State;
		string ZipCode;

		DMS Directory;
		for (int i = 0; i < 6; i++)
		{
			getline(inFile, Line);
			vector<string>* p;
			p = new vector<string>();
			split(Line, *p);
			if (p->size() == 9)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);
				Email = p->at(3);
				web = p->at(4);
				PoBox = p->at(5);
				StreetAdd = p->at(6);
				District = p->at(7);
				State = p->at(8);
				ZipCode = p->at(9);
				StreetAdd = PoBox + StreetAdd;
				p->clear();

				PersonContacts[i] = new BusinessPhoneContact(Name, Gender, Phone);
				PersonContacts[i + 1] = new BusinessWebContact(Name, Gender, Email, web);
				PersonContacts[i + 2] = new BusinessAddressContact(Name, Gender, StreetAdd, District, State, ZipCode);

				Directory.CreateDirectory(Name, PersonContacts[i]);
				Directory.CreateDirectory(Name, PersonContacts[i + 1]);
				Directory.CreateDirectory(Name, PersonContacts[i + 2]);

			}
			if (p->size() == 8)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);
				Email = p->at(3);
				StreetAdd = p->at(4);
				District = p->at(5);
				State = p->at(6);
				ZipCode = p->at(7);

				p->clear();
				PersonContacts[i] = new BusinessPhoneContact(Name, Gender, Phone);
				PersonContacts[i + 1] = new BusinessWebContact(Name, Gender, Email);
				PersonContacts[i + 2] = new BusinessAddressContact(Name, Gender, StreetAdd, District, State, ZipCode);

				Directory.CreateDirectory(Name, PersonContacts[i]);
				Directory.CreateDirectory(Name, PersonContacts[i + 1]);
				Directory.CreateDirectory(Name, PersonContacts[i + 2]);

			}
			else if (p->size() == 4)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);
				Email = p->at(3);

				p->clear();
				PersonContacts[i] = new BusinessPhoneContact(Name, Gender, Phone);
				PersonContacts[i + 1] = new BusinessWebContact(Name, Gender, Email);

				Directory.CreateDirectory(Name, PersonContacts[i]);
				Directory.CreateDirectory(Name, PersonContacts[i + 1]);
			}
			else if (p->size() == 3)
			{
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);

				p->clear();
				PersonContacts[i] = new PersonPhoneContact(Name, Gender, Phone);

				Directory.CreateDirectory(Name, PersonContacts[i]);
			}
		}
		Directory.DisplayDirectory();
	}
}

DMS& DMS::operator=(const DMS& aorDMS)
{
	// Prevent self copy
	if (this != &aorDMS)
	{
		// Copy directory
		this->voDirectory = aorDMS.voDirectory;
	}

	return(*this);
}

