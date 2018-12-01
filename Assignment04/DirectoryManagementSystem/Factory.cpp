#include "Factory.h"
#include "Query.h"
#include"DMS.h"
#include<queue>
#include<vector>
#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Factory::Factory()
{
}

Factory::Factory(Factory & F)
{
	*this = F;
}

Factory::~Factory()
{
}

Factory & Factory::operator=(const Factory & F)
{
	this->Queue = F.Queue;
	return *this;
}


void Factory::GenerateSerchingTerms()
{
	
}

queue<Query*> Factory::GenerateQueue(DMS& koDMS, int QueryCount)
{
	int ran;
	string SearchingTerm;
	Query* p;
	for (int i = 0; i < QueryCount; i++)
	{
		srand(time(NULL));// choose a random number between 1 and 5 to select one of the queries
		ran = (rand() % 4) + 1;

		char c = ConvertToChar(ran);
		SearchingTerm = SelectSearchingTerm(koDMS, ran);
		Queue.push(new Query(c, SearchingTerm));
		while (!Queue.empty())
		{
			p = Queue.front();

			std::cout << " Query" << p->MSelection() << "\t SearchingTerm" << p->MSearch();
			Queue.pop();
		}
		cout << std::endl;
	}
	cin.get();

	/*std::vector<std::string> AreaCodes = koDMS.GetAreaCodeTerms();
	for (size_t n = 0; n < AreaCodes.size(); n++)
		cout << AreaCodes[n] << " ";
	cout << endl;

	std::vector<std::string> Names = koDMS.GetFullNameTerms();
	for (size_t n = 0; n < Names.size(); n++)
		cout << Names[n] << " ";
	cout << endl;

	std::vector<std::string> BEmails = koDMS.GetBusinessEmailDomainTerms();
	for (size_t n = 0; n < BEmails.size(); n++)
		cout << BEmails[n] << " ";
	cout << endl;

	std::vector<std::string> PEmails = koDMS.GetPersonEmailDomainTerms();
	for (size_t n = 0; n < PEmails.size(); n++)
		cout << PEmails[n] << " ";
	cout << endl;
	cin.get();
	*/
	return Queue;
}
char Factory::ConvertToChar(int a)
{
	switch (a)
	{
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	}
}

string Factory::SelectSearchingTerm(DMS DMSo, int b)
{

	/*vector<string> BusinessDomainTerms;
	BusinessDomainTerms.reserve(DMSo.GetBusinessWebDomainTerms().size() + DMSo.GetBusinessEmailDomainTerms().size());
	BusinessDomainTerms.insert(BusinessDomainTerms.end(), DMSo.GetBusinessWebDomainTerms().begin(), DMSo.GetBusinessWebDomainTerms().end());
	BusinessDomainTerms.insert(BusinessDomainTerms.end(), DMSo.GetBusinessEmailDomainTerms().begin(), DMSo.GetBusinessEmailDomainTerms().end());
	*/
	string SearchTerm;
	switch (b)
	{
	case 1:
		this->SearchingTerms = DMSo.GetFullNameTerms();
		break;
	case 2:
		this->SearchingTerms = DMSo.GetPersonEmailDomainTerms();

		break;
	case 3:
		this->SearchingTerms = DMSo.GetAreaCodeTerms();

		return SearchTerm;
		break;
	case 4:
		this->SearchingTerms = DMSo.GetBusinessEmailDomainTerms();
		break;
	}
	//int randomIndex = rand() % SearchingTerms.size();
	//SearchTerm = SearchingTerms[randomIndex];
	return SearchTerm;
}
