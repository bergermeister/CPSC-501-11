/**
 * @file       PersonAddressContact.cpp
 * @author     Zainab Al Taweel, Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Person Address Contact class implementation
 */
#include "PersonAddressContact.h"
#include <string>
#include <iostream>

using namespace std;

PersonAddressContact::PersonAddressContact(const string & oName, const string & oGender, const string & oStreetAdd, const string & oDistrict,
	const string & oState, const string & oZipcode)
	: PersonContact(oName, oGender) // Deafult Constructor
{
   if( oDistrict.length( ) > 0 )
   {
	   this->StreetAddress = oStreetAdd;
	   this->District = oDistrict;
	   this->State = oState;
	   this->ZipCode = oZipcode;
   }
   else
   {
      vector< string > Words = Contact::mSplit( oStreetAdd, ',' );

      this->StreetAddress = Words[ 0 ];
      for( int i = 1; i < Words.size() - 3; i++ )
      {
         this->StreetAddress += "," + Words[ i ];
      }

      this->District = Words[ Words.size( ) - 3 ];
      this->State    = Words[ Words.size( ) - 2 ];
      this->ZipCode  = Words[ Words.size( ) - 1 ];
   }
}

PersonAddressContact::PersonAddressContact(const PersonAddressContact & oPAC) // Copy constructor
{
	*this = oPAC;
}

PersonAddressContact & PersonAddressContact::operator=(const PersonAddressContact & oPAC) // Copy Constructor 
{
	PersonContact::operator=(static_cast<PersonContact>(oPAC));
	this->StreetAddress = oPAC.StreetAddress;
	this->District = oPAC.District;
	this->State = oPAC.State;
	this->ZipCode = oPAC.ZipCode;
	return *this;
}

void PersonAddressContact::display(void)
{
	cout << this->StreetAddress << ", " << this->District << ", " << this->State << ", " << this->ZipCode;
}

PersonAddressContact::~PersonAddressContact()  // Destructor
{
}

string PersonAddressContact::MGetState( void ) const
{
   return( this->State );
}

string PersonAddressContact::MToString( void ) const
{
   return( "Address:\n\tStreet:  \t" + this->StreetAddress + "\n" +
                      "\tDistrict:\t" + this->District      + "\n" + 
                      "\tState:   \t" + this->State         + "\n" + 
                      "\tZip:     \t" + this->ZipCode       + "\n" );
}

