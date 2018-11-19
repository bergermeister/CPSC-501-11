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
#include <set>
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
		cout << "Key: " + koIter->first + " \t|\t ";
      koIter->second->display( );
      cout << std::endl;
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
	ContType = mTrim( p.at( 1 ) );            // Get the type of contacts
	p.clear( );

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
}


void DMS::query( const char acResponse )
{
   using namespace std;

   //vector< string > koWords = Contact::mSplit( aorResponse, ' ' );
   //multimap< string, Contact* >::iterator koIter;

   this->voResults.clear( );

   switch( acResponse )
   {
   case 'd':   // Display entire directory
      this->DisplayDirectory( );
      break;
   case '1':   // Query by name ordered by type (Gender or category)
      this->mQuery1( );
      break;
   case '2':   // Query by whole name
      break;
   case '3':   // 
      break;
   case '4':   //
      break;
   case '5':   //
      break;
   case 'P':
   case 'p':
      this->mDisplay2( );
      break;
   }
}

void DMS::display_results( void )
{
   for( auto koIter = this->voResults.begin( ); koIter != this->voResults.end( ); koIter++ )
   {
      cout << *koIter << endl;
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
		v.push_back(mTrim(s.substr(i, j - i)));
		i = ++j;
		j = s.find(",", j);

		if (j < 0)
		{
			v.push_back(mTrim(s.substr(i, s.length())));
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

void DMS::mQuery1( void )
{
   string                       koName;
   multiset< string >           koResults;
   multiset< string >::iterator koSetIter;
   PersonAddressContact*        kopPerson;
   BusinessAddressContact*      kopBusiness;

   cout << "Enter the name: ";
   cin >> koName;

   // Iterate through the directory and save all Contacts 
   for( auto koIter = this->voDirectory.begin( ); koIter != this->voDirectory.end( ); koIter++ )
   {
      // If the contact contains the name provided
      if( koIter->second->MGetFullName( ).find( koName ) != string::npos )
      {
         // Ensure pointers are null to start
         kopPerson   = nullptr;
         kopBusiness = nullptr;

         // Attempt to cast to Person and Business Address Contact Pointers
         kopPerson   = dynamic_cast< PersonAddressContact* >( koIter->second );
         kopBusiness = dynamic_cast< BusinessAddressContact* >( koIter->second );

         // If the Contact was a PersonAddressContact
         if( kopPerson != nullptr )
         {
            koResults.insert( kopPerson->MGetState( ) );
         }
         // If the Contact was a BusinessAddressContact
         else if( kopBusiness != nullptr )
         {
            koResults.insert( kopBusiness->MGetState( ) );
         }
      }
   }

   koSetIter = koResults.begin( );

   while( koSetIter != koResults.end( ) )
   {
      this->voResults.push_back( *koSetIter + "\t" + to_string( koResults.count( *koSetIter ) ) );
      koSetIter = koResults.upper_bound( *koSetIter );
   }
}

void DMS::mDisplay2( void )
{
   string                  koName;
   multimap< string, Contact* >::iterator koIter;
   multimap< string, Contact* >::iterator koEnd;
   string                  koDetails;
   PersonContact*          kopPerson;
   PersonPhoneContact*     kopPhone;
   PersonEmailContact*     kopEmail;
   PersonAddressContact*   kopAddr;

   cout << "Enter the name: ";
   cin >> koName;

   koIter = this->voDirectory.begin( );
   while( koIter != this->voDirectory.end( ) )
   {
      // If the contact contains the name provided
      if( koIter->second->MGetFullName( ).find( koName ) != string::npos )
      {
         kopPerson = dynamic_cast< PersonContact* >( koIter->second );
         koDetails =  "Name:   \t" + kopPerson->MGetFullName( ) + "\n";
         koDetails += "Gender: \t" + kopPerson->MGetGender( )   + "\n";
         koEnd = this->voDirectory.upper_bound( koIter->first );
         while( koIter != koEnd )
         {
            koDetails += koIter->second->MToString( ) + "\n";
            koIter++;
         }
         this->voResults.push_back( koDetails );
      }
      // Contact does not match, skip its details
      else
      {
         koIter = this->voDirectory.upper_bound( koIter->first );
      }

      //koIter++;
   }
}

bool DMS::mCompareAddress( Contact* aopContact1, Contact* aopContact2 )
{
   string                  koState1;
   string                  koState2;
   const PersonAddressContact*   kopPerson;
   const BusinessAddressContact* kopBusiness;

   kopPerson   = dynamic_cast< PersonAddressContact* >( aopContact1 );
   kopBusiness = dynamic_cast< BusinessAddressContact* >( aopContact1 );
   if( kopPerson != nullptr )
   {
      //koState1 = kopPerson.
   }
   return( koState1 < koState2 );
}

std::string DMS::mTrim( const std::string& aorStr )
{
   string koResult;
   size_t kiFirst = aorStr.find_first_not_of( ' ' );
   size_t kiLast  = aorStr.find_last_not_of( ' ' );
   if( string::npos == kiFirst )
   {
      koResult = aorStr;
   }
   else
   {
      koResult = aorStr.substr( kiFirst, ( kiLast - kiFirst + 1 ) );
   }
   
   return( koResult );
}
