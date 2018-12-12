/**
 * @file       DMS.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel
 * @date       2018-12-11
 * @compiler   Visual C++ 2017
 *
 * @brief Directory Management System class implementation
 */
#include "Contact.h"
#include "PersonContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "PersonEmailContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessAddressContact.h"
#include "BusinessWebContact.h"
#include "Graph.h"
#include "DMS.h"
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>

using namespace std;

DMS::DMS(bool abGraphEn)
{
	this->vbGraphEn = abGraphEn;
}

DMS::DMS(const DMS& aorDMS)
{
	// Call assignment operator
	*this = aorDMS;
}

DMS::~DMS(void)
{
	// Delete all contacts to free memory
	for (auto koIter = voDirectory.begin(); koIter != voDirectory.end(); koIter++)
	{
      if( koIter->second != nullptr )
      {
		   delete koIter->second;
      }
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
	voDirectory.insert(pair< string, Contact* >(Name, ContInfo));
}

void DMS::DisplayDirectory(void)
{
	for (auto koIter = voDirectory.begin(); koIter != voDirectory.end(); koIter++)
	{
		cout << "Key: " + koIter->first + " \t|\t ";
		koIter->second->display();
		cout << std::endl;
	}
}

void DMS::populateDirectory(const std::string& FileName)
{
	int      ContNum;  // the number of contacts in the file
	string   ContType; // the type of contact weather it is person or business
	string   Line;
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

	vector< string > p;
	split(FirstLine, p);
	ContNum = stoi(p.at(0));     // Get the number of contacts
	ContType = mTrim(p.at(1));            // Get the type of contacts
	p.clear();

	for (int i = 0; i < ContNum; i++)
	{
		getline(inFile, Line);
		if( ( ContType.find( "erson" ) != string::npos ) || ( ContType.find( "eople" ) != string::npos ) )
		{
			this->mParsePerson(Line);
		}
		else if( ContType.find( "usiness" ) != string::npos )
		{
			this->mParseBusiness(Line);
		}
	}
}


std::vector< std::pair< std::string, int > > DMS::query( const char acType, const string& aorSearch )
{
	using namespace std;

   string                        koTerm;
   string                        koTitleG, koTitleX, koTitleY;
   vector< pair< string, int > > koResults;
   
   // If the search term was no provided
   if( aorSearch.length( ) == 0 )
   {
      // Prompt the user for the search term
      cout << "Enter search term: ";
      cin  >> koTerm;
   }
   else
   {
      // Record the given search term
      koTerm = aorSearch;
   }

   // Clear the results
	this->voResults.clear();

   // Switch based on the type of query
	switch( acType )
	{
	case 'd':   // Display entire directory
		this->DisplayDirectory();
		break;
	case '1':   // Query by name ordered by type (Gender or category)
		koResults = this->MQuery1( koTerm );
      koTitleX = "State";
      koTitleY = "Number of " + koTerm;
      koTitleG = "Search Query 1";
		break;
	case '2':   // Query by email domain is “.edu” ordered by the gender.
		koResults = this->MQuery2( koTerm );
      koTitleX = "Gender";
      koTitleY = "No of Males and Females";
      koTitleG = "Search Query 2";
		break;
	case '3':   //query Organization by phone number that start with the area code ‘203’ ordered by category.
		koResults = this->MQuery3( koTerm );
      koTitleX = "Category";
      koTitleY = "Number of organazation with phone number starts with " + koTerm;
      koTitleG = "Search Query 3";
		break;
	case '4':   //Query Organisation by email and website domain is ".com" ordered by the category
		koResults = this->MQuery4( koTerm );
      koTitleX = "Category";
      koTitleY = "Number of organazation with " + koTerm + " email or website";
      koTitleG = "Search Query 4";
		break;
	case '5':   //Query by phone numbers out-of-state area codes ordered by the state.
		koResults = this->MQuery5( koTerm );
		break;
   case 'B':   // Fall through
   case 'b':   // Display details of a Business
      this->mDisplay1( koTerm );
      break;
	case 'P':   // Fall through
	case 'p':   // Display details of a person
		this->mDisplay2( koTerm );
		break;
	}

   if( ( koResults.size( ) > 0 ) && ( vbGraphEn ) )
   {
      Graph koGraph( koTitleX, koTitleY, koTitleG );
      
      for( auto koIter = koResults.begin( ); koIter != koResults.end( ); koIter++ )
      {
		   koGraph.addItem( koIter->first, koIter->second );
	   }
	   
	   koGraph.initializeGraph();
	   koGraph.generateGraph();
   }

   return( koResults );
}

std::vector< std::pair< std::string, int > > DMS::MQuery1( const std::string& aorTerm )
{
   std::vector< std::pair< std::string, int > > koResults;
	multiset< string >           koResultSet;
	multiset< string >::iterator koSetIter;
	PersonAddressContact*        kopPerson;
	BusinessAddressContact*      kopBusiness;

	// Iterate through the directory and save all Contacts 
	for (auto koIter = this->voDirectory.begin(); koIter != this->voDirectory.end(); koIter++)
	{
		// If the contact contains the name provided
		if (koIter->second->MGetFullName().find( aorTerm ) != string::npos)
		{
			// Ensure pointers are null to start
			kopPerson = nullptr;
			kopBusiness = nullptr;

			// Attempt to cast to Person and Business Address Contact Pointers
			kopPerson = dynamic_cast<PersonAddressContact*>(koIter->second);
			kopBusiness = dynamic_cast<BusinessAddressContact*>(koIter->second);

			// If the Contact was a PersonAddressContact
			if (kopPerson != nullptr)
			{
				koResultSet.insert(kopPerson->MGetState());
			}
			// If the Contact was a BusinessAddressContact
			else if (kopBusiness != nullptr)
			{
				koResultSet.insert(kopBusiness->MGetState());
			}
		}
	}

   koSetIter = koResultSet.begin();
	while( koSetIter != koResultSet.end( ) )
	{
		koResults.push_back( pair< string, int >( *koSetIter, koResultSet.count( *koSetIter ) ) );
		koSetIter = koResultSet.upper_bound( *koSetIter );
	}

   return( koResults );
}

std::vector< std::pair< std::string, int > > DMS::MQuery2( const std::string& aorTerm )
{
   std::vector< std::pair< std::string, int > > koResults;
	PersonEmailContact* PIt = nullptr;
	string PEmail;
	string PEmailAt;
	string Domain;
	int MaleCount = 0;
	int FemaleCount = 0;

	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		PIt = dynamic_cast<PersonEmailContact*>(It->second);
		if (PIt != nullptr)
		{
			PEmail = PIt->GetPersonEmail();
			int i = PEmail.find('@');
			PEmailAt = (PEmail.substr(i + 1, PEmail.length()));
			int j = PEmailAt.find(aorTerm);
			string Gender = PIt->MGetGender();
			if ((j != -1) && (Gender == "Male"))
				MaleCount++;
			if ((j != -1) && (Gender == "Female"))
				FemaleCount++;
		}
	}
   koResults.push_back( pair< string, int >( "Males", MaleCount ) );
   koResults.push_back( pair< string, int >( "Females", FemaleCount ) );

   return( koResults );
} 

std::vector< std::pair< std::string, int > > DMS::MQuery3( const std::string& aorTerm )
{
   std::vector< std::pair< std::string, int > > koResults;
	BusinessPhoneContact* BIt = nullptr;
	string BPhone;
	string BAreaCode;
	multiset< string > BCategory;
	multiset< string >::iterator BCI;

	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		BIt = dynamic_cast<BusinessPhoneContact*>(It->second);
		if (BIt != nullptr)
		{
			BPhone = BIt->GetBusinessPhone();
			BAreaCode = BPhone.substr(2, 3);
			if (BAreaCode == aorTerm)
				BCategory.insert(BIt->GetCategory());
		}
	}
	BCI = BCategory.begin();
	while (BCI != BCategory.end())
	{
      koResults.push_back( pair< string, int >( *BCI, BCategory.count( *BCI ) ) );
		BCI = BCategory.upper_bound(*BCI);
	}

   return( koResults );
}

std::vector< std::pair< std::string, int > > DMS::MQuery4( const std::string& aorTerm )
{
   std::vector< std::pair< std::string, int > > koResults;
	BusinessWebContact *BIt = nullptr;
	string Temp;
	multiset< string > BCategory;
	multiset< string >::iterator BCI;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		BIt = dynamic_cast<BusinessWebContact*>(It->second);
		if( BIt != nullptr )
		{
         int i, j;
         Temp = BIt->GetBusinessEmail();
         if( ( i = Temp.find('@') ) != string::npos )
         {
			   if( ( Temp.substr( i + 1, Temp.length( ) ) ) == aorTerm )
            {
			      BCategory.insert( BIt->GetCategory( ) );
            }
         }

         Temp = BIt->GetWebsite( );
         if( ( i = Temp.find_last_of('.') ) != string::npos )
         {
			   if( ( Temp.substr( i + 1, Temp.length( ) ) ) == aorTerm )
            {
			      BCategory.insert( BIt->GetCategory( ) );
            }
         }
		}
	}
	BCI = BCategory.begin();
	
	while (BCI != BCategory.end())
	{
      koResults.push_back( pair< string, int >( *BCI, BCategory.count( *BCI ) ) );
		BCI = BCategory.upper_bound(*BCI);
	}

   return( koResults );
}

std::vector< std::pair< std::string, int > > DMS::MQuery5( const std::string& aorTerm )
{
   std::vector< std::pair< std::string, int > > koResults;
	PersonPhoneContact* PIt = nullptr;
	PersonAddressContact* AddIt = nullptr;
	multiset< string > Result;
	string PhoneNo;
	string AreaCode;
	string State;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		AddIt = dynamic_cast<PersonAddressContact*>(It->second);
		PIt = static_cast<PersonPhoneContact*>(It->second);
		if (PIt != nullptr)
		{
			PhoneNo = PIt->GetPersonPhone();
			AreaCode = PhoneNo.substr(2, 3);
			if (AreaCode != "203") // || AreaCode == "475" || AreaCode == "860" || AreaCode == "959")
			{
				if (AddIt != nullptr)
				{
					//State = AddIt->MGetState();
					Result.insert(AddIt->MGetState());
					cout << AreaCode << "\t" << PhoneNo << "\n";
				}
			}
		}
	}

   return( koResults );
}

void DMS::display_results(void)
{
	for (auto koIter = this->voResults.begin(); koIter != this->voResults.end(); koIter++)
	{
		cout << *koIter << endl;
	}
}

// Split function to seprate each piece of information and store it in a vector
// ref: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s24.html
void DMS::split(const string& s, vector< string >& v)
{
	int i = 0;
	int j = s.find(',');

	while (j >= 0)
	{
		v.push_back(mTrim(s.substr(i, j - i)));
		i = ++j;
		j = s.find(',', j);

		if (j < 0)
		{
			v.push_back(mTrim(s.substr(i, s.length())));
		}
	}
}

void DMS::mParsePerson(const std::string& aorLine)
{
	enum teField
	{
		xeFieldPhone = 0,
		xeFieldEmail,
		xeFieldAddress
	};

	string           koName = "Unknown";
	string           koGender = "Unknown";  // Person Gender
	string           koAddress = "";
	vector< string > koWords;
	int              kiIndex = 0;
	teField          keField = xeFieldPhone;

	split(aorLine, koWords);

	if (koWords.size() > 0)
	{
		// First word must be the name or there is no contact to create
		koName = koWords[kiIndex];
		kiIndex++;

		// Check if Gender is valid 
		if (PersonContact::MIsValid(koWords[1]))
		{
			koGender = koWords[1];
			kiIndex++;
		}

		for (; kiIndex < koWords.size(); kiIndex++)
		{
			switch (keField)
			{
			case xeFieldPhone:
				if (mIsPhoneNum(koWords[kiIndex]))
				{
					this->voDirectory.insert(pair< string, Contact* >(koName,
						new PersonPhoneContact(koName,
							koGender,
							koWords[kiIndex])));
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
				if (mIsEmail(koWords[kiIndex]))
				{
					this->voDirectory.insert(pair< string, Contact* >(koName,
						new PersonEmailContact(koName,
							koGender,
							koWords[kiIndex])));
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
				koAddress += koWords[kiIndex];
				if (kiIndex < (koWords.size() - 1))
				{
					// Add the comma back
					koAddress += ',';
				}
				break;
			}
		}

		// If an address was found
		if (koAddress.length() > 0)
		{
			this->voDirectory.insert(pair< string, Contact* >(koName, new PersonAddressContact(koName,
				koGender,
				koAddress)));
		}
	}
}

void DMS::mParseBusiness(const std::string& aorLine)
{
	enum teField
	{
		xeFieldPhone = 0,
		xeFieldWeb,
		xeFieldAddress
	};

	string           koName = "Unknown";
	string           Category = "Unknown";  // Business Category
	string           koAddress = "";
	vector< string > koWords;
	int              kiIndex = 0;
	teField          keField = xeFieldPhone;

	split(aorLine, koWords);

	if (koWords.size() > 0)
	{
		// First word must be the name or there is no contact to create
		koName = koWords[kiIndex];
		kiIndex++;
		// Second word is the business Category
		Category = koWords[1];
		kiIndex++;

		for (; kiIndex < koWords.size(); kiIndex++)
		{
			switch (keField)
			{
			case xeFieldPhone:
				if (mIsPhoneNum(koWords[kiIndex]))
				{
					this->voDirectory.insert(pair< string, Contact* >(koName,
						new BusinessPhoneContact(koName,
							Category,
							koWords[kiIndex])));
				}
				else
				{
					// Move back to recheck the string
					kiIndex--;
				}
				// Move to the next field
				keField = xeFieldWeb;
				break;
			case xeFieldWeb:
				if (mIsWeb(koWords[kiIndex])) // check if the field is email
				{
					if (mIsEmail(koWords[kiIndex+1]))
					{
						this->voDirectory.insert(pair< string, Contact* >(koName,
							new BusinessWebContact(koName,
								Category,
								koWords[kiIndex+1], koWords[kiIndex])));
						kiIndex++;
					}
					else
					{
						this->voDirectory.insert(pair< string, Contact* >(koName,
							new BusinessWebContact(koName,
								Category,
								"", koWords[kiIndex])));
					}
				}
            else if(mIsEmail(koWords[kiIndex]))
            {
               this->voDirectory.insert(pair< string, Contact* >(koName,
							new BusinessWebContact(koName,
								Category,
                        koWords[kiIndex] )));
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
				koAddress += koWords[kiIndex];
				if (kiIndex < (koWords.size() - 1))
				{
					// Add the comma back
					koAddress += ',';
				}
				break;
			}
		}

		// If an address was found
		if (koAddress.length() > 0)
		{
			this->voDirectory.insert(pair< string, Contact* >(koName, new BusinessAddressContact(koName,
				Category,
				koAddress)));
		}
	}
}

bool DMS::mIsPhoneNum(const std::string& aorStr)
{
	bool kbIsPhoneNum = false;
	int  kiIndex;

	if (aorStr.length() == 14)
	{
		// Check the outlying values
		if ((this->mIsNumber(aorStr[0])) &&
			(this->mIsNumber(aorStr[13])) &&
			(aorStr[1] == '-') &&
			(aorStr[5] == '-') &&
			(aorStr[9] == '-'))

		{
			kbIsPhoneNum = true; // Assume true

			// Ensure the remaining characters are numbers
			for (kiIndex = 0; kiIndex < 3; kiIndex++)
			{
				if (!(this->mIsNumber(aorStr[kiIndex + 2])) ||
					!(this->mIsNumber(aorStr[kiIndex + 6])) ||
					!(this->mIsNumber(aorStr[kiIndex + 10])))
				{
					kbIsPhoneNum = false;
					break;
				}
			}
		}
	}

	return(kbIsPhoneNum);
}

bool DMS::mIsEmail(const std::string& aorStr)
{
	return(!(aorStr.find('@') == string::npos));
}

bool DMS::mIsWeb(const std::string& aorStr) // checking if the field is a website or not 
{
	return(!(aorStr.find('www.') == string::npos));
}

bool DMS::mIsNumber(const char acChar)
{
	bool kbIsNumber = false;

	if (('0' <= acChar) && (acChar <= '9'))
	{
		kbIsNumber = true;
	}

	return(kbIsNumber);
}

void DMS::mDisplay1( const std::string& aorTerm )
{
	multimap< string, Contact* >::iterator koIter;
	multimap< string, Contact* >::iterator koEnd;
	string                                 koDetails;
	BusinessContact*                       kopBusiness;

	koIter = this->voDirectory.begin();
	while( koIter != this->voDirectory.end( ) )
	{
		// If the contact contains the name provided
		if( koIter->second->MGetFullName( ).find( aorTerm ) != string::npos )
		{
			kopBusiness = dynamic_cast< BusinessContact* >( koIter->second );
			koDetails =  "Name:     \t" + kopBusiness->MGetFullName( ) + "\n";
			koDetails += "Category: \t" + kopBusiness->GetCategory( ) + "\n";
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
	}
}

void DMS::mDisplay2( const std::string& aorTerm )
{
	multimap< string, Contact* >::iterator koIter;
	multimap< string, Contact* >::iterator koEnd;
	string                                 koDetails;
	PersonContact*                         kopPerson;

	koIter = this->voDirectory.begin();
	while (koIter != this->voDirectory.end())
	{
		// If the contact contains the name provided
		if (koIter->second->MGetFullName().find(aorTerm) != string::npos)
		{
			kopPerson = dynamic_cast<PersonContact*>(koIter->second);
			koDetails = "Name:   \t" + kopPerson->MGetFullName() + "\n";
			koDetails += "Gender: \t" + kopPerson->MGetGender() + "\n";
			koEnd = this->voDirectory.upper_bound(koIter->first);
			while (koIter != koEnd)
			{
				koDetails += koIter->second->MToString() + "\n";
				koIter++;
			}
			this->voResults.push_back(koDetails);
		}
		// Contact does not match, skip its details
		else
		{
			koIter = this->voDirectory.upper_bound(koIter->first);
		}
	}
}

bool DMS::mCompareAddress(Contact* aopContact1, Contact* aopContact2)
{
	string                  koState1;
	string                  koState2;
	const PersonAddressContact*   kopPerson;
	const BusinessAddressContact* kopBusiness;

	kopPerson = dynamic_cast<PersonAddressContact*>(aopContact1);
	kopBusiness = dynamic_cast<BusinessAddressContact*>(aopContact1);
	if (kopPerson != nullptr)
	{
		//koState1 = kopPerson.
	}
	return(koState1 < koState2);
}

std::string DMS::mTrim(const std::string& aorStr)
{
	string koResult;
	size_t kiFirst = aorStr.find_first_not_of(' ');
	size_t kiLast = aorStr.find_last_not_of(' ');
	if (string::npos == kiFirst)
	{
		koResult = aorStr;
	}
	else
	{
		koResult = aorStr.substr(kiFirst, (kiLast - kiFirst + 1));
	}

	return(koResult);
}
int DMS::GetDirectorySize() const
{
	return this->voDirectory.size();
}
std::vector<std::string> DMS::GetFullNameTerms() const
{
	std::vector<std::string> FullNameTerms;
	string FullName;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		FullName = It->second->MGetFullName();
		if (std::find(FullNameTerms.begin(), FullNameTerms.end(), FullName) != FullNameTerms.end())
			continue;
		else
			FullNameTerms.push_back(FullName);
	}
	return FullNameTerms;
}

std::vector<std::string> DMS::GetAreaCodeTerms() const
{
	std::vector<std::string> AreaCodeTerms;
	BusinessPhoneContact* BIt = nullptr;
	string BPhone;
	string BAreaCode;
	vector< string >::iterator BCI;

	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		BIt = dynamic_cast<BusinessPhoneContact*>(It->second);
		if (BIt != nullptr)
		{
			BPhone = BIt->GetBusinessPhone();
			BAreaCode = BPhone.substr(2, 3);
			if (std::find(AreaCodeTerms.begin(), AreaCodeTerms.end(), BAreaCode) != AreaCodeTerms.end())
				continue;
			else
				AreaCodeTerms.push_back(BAreaCode);
		}
	}
	return AreaCodeTerms;
}

std::vector<std::string> DMS::GetPersonEmailDomainTerms() const
{
	std::vector<std::string> EmailDomainTerms;

	PersonEmailContact* PIt = nullptr;
	string PEmail;
	string PEmailAt;
	string Domain;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		PIt = dynamic_cast<PersonEmailContact*>(It->second);
		if (PIt != nullptr)
		{
			PEmail = PIt->GetPersonEmail();
			int i = PEmail.find('@');
			PEmailAt = (PEmail.substr(i + 1, PEmail.length()));
			int j = PEmailAt.find(".");
			Domain = (PEmailAt.substr(j + 1, PEmailAt.length()));
			if (std::find(EmailDomainTerms.begin(), EmailDomainTerms.end(), Domain) != EmailDomainTerms.end())
				continue;
			else
				EmailDomainTerms.push_back(Domain);
		}
	}
	return EmailDomainTerms;
}
std::vector<std::string> DMS::GetBusinessEmailDomainTerms() const
{
	std::vector<std::string> BusinessEmailDomainTerms;
	BusinessWebContact *BIt = nullptr;
	string BEmail;
	string BEmailAt;
	string Domain;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		BIt = dynamic_cast<BusinessWebContact*>(It->second);
		if (BIt != nullptr)
		{
			BEmail = BIt->GetBusinessEmail();
			int i = BEmail.find('@');
			BEmailAt = (BEmail.substr(i + 1, BEmail.length()));
			int j = BEmailAt.find(".");
			Domain = (BEmailAt.substr(j + 1, BEmailAt.length()));
			if (std::find(BusinessEmailDomainTerms.begin(), BusinessEmailDomainTerms.end(), Domain) != BusinessEmailDomainTerms.end())
				continue;
			else
				BusinessEmailDomainTerms.push_back(Domain);
		}
	}
	return BusinessEmailDomainTerms;
}
std::vector<std::string> DMS::GetBusinessWebDomainTerms() const
{
	std::vector<std::string> BusinessWebDomainTerms;
	BusinessWebContact *BIt = nullptr;
	string Website;
	string WebsiteAt;
	string WebDomain;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		BIt = dynamic_cast<BusinessWebContact*>(It->second);
		if (BIt != nullptr)
		{
			Website = BIt->GetWebsite();
			int x = Website.find('@');
			WebsiteAt = (Website.substr(x + 1, Website.length()));
			int y = WebsiteAt.find(".");
			WebDomain = (WebsiteAt.substr(y + 1, WebsiteAt.length()));
			if (std::find(BusinessWebDomainTerms.begin(), BusinessWebDomainTerms.end(), (WebDomain)) != BusinessWebDomainTerms.end())
				continue;
			else
				BusinessWebDomainTerms.push_back(WebDomain);
		}
	}
	return BusinessWebDomainTerms;
}
