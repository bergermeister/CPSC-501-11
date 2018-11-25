
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

DMS::DMS(void)
{
	// TODO
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


void DMS::query(const char acResponse)
{
	using namespace std;

   string koTerm;
   
   cout << "Enter search term: ";
   cin  >> koTerm;

	this->voResults.clear();

	switch (acResponse)
	{
	case 'd':   // Display entire directory
		this->DisplayDirectory();
		break;
	case '1':   // Query by name ordered by type (Gender or category)
		this->mQuery1( koTerm );
		break;
	case '2':   // Query by email domain is “.edu” ordered by the gender.
		this->mQuery2( koTerm );
		break;
	case '3':   //query Organization by phone number that start with the area code ‘203’ ordered by category.
		this->mQuery3( koTerm );
		break;
	case '4':   //Query Organisation by email and website domain is ".com" ordered by the category
		this->mQuery4( koTerm );
		break;
	case '5':   //Query by phone numbers out-of-state area codes ordered by the state.
		this->mQuery5( koTerm );
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

void DMS::mQuery1( const std::string& aorTerm )
{
	multiset< string >           koResults;
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
				koResults.insert(kopPerson->MGetState());
			}
			// If the Contact was a BusinessAddressContact
			else if (kopBusiness != nullptr)
			{
				koResults.insert(kopBusiness->MGetState());
			}
		}
	}

	Graph g("State", "Number of " + aorTerm, "Search Query 1");

	koSetIter = koResults.begin();
	while (koSetIter != koResults.end())
	{
		this->voResults.push_back(*koSetIter + "\t" + to_string(koResults.count(*koSetIter)));
		g.addItem(*koSetIter, koResults.count(*koSetIter));
		koSetIter = koResults.upper_bound(*koSetIter);
	}
	cout << "Number of " << aorTerm << " in the directory ordered by State: " << endl;
	// g.display();
	g.initializeGraph();
	g.generateGraph();
}

// the number of people in the directory whose email domain is “.edu” ordered by the gender.
void DMS::mQuery2( const std::string& aorTerm )
{
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
	this->voResults.push_back("Male \t" + to_string(MaleCount) + "\nFemale \t" + to_string(FemaleCount) + "\n");
	Graph g("Gender", "No of Males and Females", "Search Query 2");
	g.addItem("Males ", MaleCount);
	g.addItem("Females ", FemaleCount);
	cout << "Number of people in the directory whose email domain is \"" << aorTerm << "\" ordered by Gender: " << endl;
	//g.display();
	g.initializeGraph();
	g.generateGraph();

} 

//query Organization by phone number that start with the area code ‘203’ ordered by category.
void DMS::mQuery3( const std::string& aorTerm )
{
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
	Graph g("Category", "Number of organazation with phone number starts with " + aorTerm, "Search Query 3");
	while (BCI != BCategory.end())
	{
		this->voResults.push_back(*BCI + "\t" + to_string(BCategory.count(*BCI)));
		g.addItem(*BCI, BCategory.count(*BCI));
		BCI = BCategory.upper_bound(*BCI);
	}
	cout << "Number of organizations with phone number starts with " << aorTerm << " ordered by category: " << endl;
	//g.display();
	g.initializeGraph();
	g.generateGraph();

}

void DMS::mQuery4( const std::string& aorTerm )
{
	BusinessWebContact *BIt = nullptr;
	string PWeb;
	string PWebAt;
	string Domain;
	multiset< string > BCategory;
	multiset< string >::iterator BCI;
	for (auto It = this->voDirectory.begin(); It != this->voDirectory.end(); It++)
	{
		BIt = dynamic_cast<BusinessWebContact*>(It->second);
		if (BIt != nullptr)
		{
			PWeb = BIt->GetBusinessEmail();
			//int i = PEmail.find('@');
			//PWebAt = (PWeb.substr(i + 1, PWeb.length()));
			int j = PWebAt.find("com");
			//if(j=="com")
			//BCategory.insert(BIt->GetCategory());
		}
	}
	BCI = BCategory.begin();
	Graph g("Category", "Number of organazation with .com email or website", "Search Query 4");
	while (BCI != BCategory.end())
	{
		this->voResults.push_back(*BCI + "\t" + to_string(BCategory.count(*BCI)));
		g.addItem(*BCI, BCategory.count(*BCI));
		BCI = BCategory.upper_bound(*BCI);
	}
	cout << "Number of organisations in the directory whose email or website domain is “.com” ordered by Category: " << endl;
	//g.display();
	g.initializeGraph();
	g.generateGraph();
}

void DMS::mQuery5( const std::string& aorTerm )
{
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
