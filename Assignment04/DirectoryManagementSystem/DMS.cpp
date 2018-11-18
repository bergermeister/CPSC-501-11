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
#include <vector>

using namespace std;

DMS::DMS( void )
{
   // TODO
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

void DMS::CreateDirectory(string Name, Contact* ContInfo)
{
	voDirectory.insert( pair< string, Contact* >( Name, ContInfo ) );
}

void DMS::DisplayDirectory( void )
{
	for (auto koIter = voDirectory.begin(); koIter != voDirectory.end(); koIter++)
	{
		cout << "Key: " + koIter->first + " \t|\t Type of Value: ";
		cout << typeid(*koIter->second).name() << std::endl;
	}
}

void DMS::populateDirectory( const std::string& FileName )
{
	int      ContNum;  // the number of contacts in the file
	string   ContType; // the type of contact weather it is person or business
   string   Line;
	ifstream inFile;
	inFile.open( FileName );
	if( !inFile.is_open( ) ) //Failed to open file
	{
		cout << " Could not open the file  " << FileName << endl;
		cout << "Program terminating. \n";
		exit( EXIT_FAILURE );
	}
	string FirstLine;
	getline( inFile, FirstLine );

	vector< string > p;
	split(FirstLine, p);
	for( unsigned i = 0; i < p.size( ); i++ )
   {
		cout << p.at(i) << "\n";
   }
	ContNum = stoi( p.at( 0 ) );     // Get the number of contacts
	ContType = p.at( 1 );            // Get the type of contacts
	p.clear( );

	Contact* PersonContacts[3]; // create array of pointers of type Contact. This array should be of constant size, I dont know how to do it here.

   for( int i = 0; i < ContNum; i++ )
   {
      getline( inFile, Line );
      if( ContType == "person" )
      {
         this->mParsePerson( Line );
      }
      else if( ContType == "business" )
      {
         this->mParseBusiness( Line );
      }
   }
   /*
	if (ContType == "person")
	{
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
		for (int i = 0; i < ContNum; i++)
		{
			getline(inFile, Line);
			vector<string>* p;
			p = new vector<string>();
			split(Line, *p);
			if (p->size() == 10)
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

				PersonContacts[0] = new BusinessPhoneContact(Name, Gender, Phone);
				PersonContacts[1] = new BusinessWebContact(Name, Gender, Email, web);
				PersonContacts[2] = new BusinessAddressContact(Name, Gender, StreetAdd, District, State, ZipCode);

				Directory.CreateDirectory(Name, PersonContacts[0]);
				Directory.CreateDirectory(Name, PersonContacts[1]);
				Directory.CreateDirectory(Name, PersonContacts[2]);

			}
			if (p->size() == 9)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Phone = p->at(2);
				Email = p->at(3);
				web = p->at(4);
				StreetAdd = p->at(4);
				District = p->at(5);
				State = p->at(6);
				ZipCode = p->at(7);

				p->clear();
				PersonContacts[0] = new BusinessPhoneContact(Name, Gender, Phone);
				PersonContacts[1] = new BusinessWebContact(Name, Gender, Email,web);
				PersonContacts[2] = new BusinessAddressContact(Name, Gender, StreetAdd, District, State, ZipCode);

				Directory.CreateDirectory(Name, PersonContacts[0]);
				Directory.CreateDirectory(Name, PersonContacts[1]);
				Directory.CreateDirectory(Name, PersonContacts[2]);

			}
			else if (p->size() == 4)
			{
				// storing the contacts info
				Name = p->at(0);
				Gender = p->at(1);
				Email = p->at(2);
				web = p->at(3);

				p->clear();
				PersonContacts[0] = new BusinessWebContact(Name, Gender, Email,web);

				Directory.CreateDirectory(Name, PersonContacts[0]);
			}
			else if (p->size() == 3)
			{
				Name = p->at(0);
				Gender = p->at(1);
				Email = p->at(2);

				p->clear();
				PersonContacts[0] = new PersonPhoneContact(Name, Gender, Email);

				Directory.CreateDirectory(Name, PersonContacts[0]);
			}
		}
		Directory.DisplayDirectory();
	}
   */
}


void DMS::query( const char acResponse )
{
   using namespace std;

   //vector< string > koWords = Contact::mSplit( aorResponse, ' ' );
   //multimap< string, Contact* >::iterator koIter;

   switch( acResponse )
   {
   case 'f':   // Query by first name
      //this->mQueryFirstName( );
      break;
   case 'l':   // Query by last name
      break;
   case 'w':   // Query by whole name
      break;
   }
}

void mQueryHelper( const std::vector< std::string >& aorWords, const int aiIndex )
{

}

void mQueryFirstName( void )
{
   using namespace std;

   string koFirstName;
   char   kcOrder;

   cout << "Enter the contact's first name: ";
   cin  >> koFirstName;

   cout << "Enter order column:";
   cin  >> kcOrder;

   
}

// Split function to seprate each piece of information and store it in a vector
// ref: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s24.html
void DMS::split( const string& s, vector< string >& v ) 
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

void DMS::mParsePerson( const std::string& aorLine )
{
   enum teField
   {
      xeFieldPhone = 0,
      xeFieldEmail,
      xeFieldAddress
   };

   string           koName    = "Unknown";
   string           koGender  = "Unknown";  // Person Gender
   string           koAddress = "";
	vector< string > koWords;
   int              kiIndex = 0;
   teField          keField = xeFieldPhone;

   split( aorLine, koWords );	

   if( koWords.size( ) > 0 )
   {
      // First word must be the name or there is no contact to create
      koName = koWords[ kiIndex ];
      kiIndex++;

      // Check if Gender is valid 
      if( PersonContact::MIsValid( koWords[ 1 ] ) )
      {
         koGender = koWords[ 1 ];
         kiIndex++;
      }

      for( ; kiIndex < koWords.size( ); kiIndex++ )
      {
         switch( keField )
         {
         case xeFieldPhone:
            if( mIsPhoneNum( koWords[ kiIndex ] ) )
            {
               this->voDirectory.insert( pair< string, Contact* >( koName, 
                                                                   new PersonPhoneContact( koName, 
                                                                                           koGender, 
                                                                                           koWords[ kiIndex ] ) ) );
            }
            else
            {
               // Move back to recheck the string
               kiIndex--;
            }
            // Move to the next field
            keField = xeFieldEmail;
            break;
         case xeFieldEmail:
            if( mIsEmail( koWords[ kiIndex ] ) )
            {
               this->voDirectory.insert( pair< string, Contact* >( koName,
                                                                   new PersonEmailContact( koName,
                                                                                           koGender,
                                                                                           koWords[ kiIndex ] ) ) );
            }
            else
            {
               // Move back to recheck this string
               kiIndex--;
            }
            keField = xeFieldAddress;
            break;
         case xeFieldAddress:
            // Address is always last, so no checks needed
            koAddress += koWords[ kiIndex ];
            if( kiIndex < ( koWords.size( ) - 1 ) )
            {
               // Add the comma back
               koAddress += ',';
            }
            break;
         }
      }

      // If an address was found
      if( koAddress.length( ) > 0 )
      {
         this->voDirectory.insert( pair< string, Contact* >( koName, new PersonAddressContact( koName,
                                                                                               koGender,
                                                                                               koAddress ) ) );
      }
   }
}

void DMS::mParseBusiness( const std::string& aorLine )
{
}

bool DMS::mIsPhoneNum( const std::string& aorStr )
{
   bool kbIsPhoneNum = false;
   int  kiIndex;

   if( aorStr.length( ) == 14 )
   {
      // Check the outlying values
      if( ( this->mIsNumber( aorStr[  0 ] ) ) &&
          ( this->mIsNumber( aorStr[ 13 ] ) ) &&
          ( aorStr[ 1 ] == '-' ) &&
          ( aorStr[ 5 ] == '-' ) &&
          ( aorStr[ 9 ] == '-' ) )
          
      {
         kbIsPhoneNum = true; // Assume true

         // Ensure the remaining characters are numbers
         for( kiIndex = 0; kiIndex < 3; kiIndex++ )
         {
            if( !( this->mIsNumber( aorStr[ kiIndex +  2 ] ) ) ||
                !( this->mIsNumber( aorStr[ kiIndex +  6 ] ) ) ||
                !( this->mIsNumber( aorStr[ kiIndex + 10 ] ) ) )
            {
               kbIsPhoneNum = false;
               break;
            }
         }
      }
   }

   return( kbIsPhoneNum );
}

bool DMS::mIsEmail( const std::string& aorStr )
{
   return( !( aorStr.find( '@' ) == string::npos ) );
}

bool DMS::mIsNumber( const char acChar )
{
   bool kbIsNumber = false;

   if( ( '0' <= acChar ) && ( acChar <= '9' ) )
   {
      kbIsNumber = true;
   }

   return( kbIsNumber );
}
