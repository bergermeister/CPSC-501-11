/**
 * @file       Factory.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel
 * @date       2018-12-11
 * @compiler   Visual C++ 2017
 *
 * @brief Factory class implementation
 */
#include "Factory.h"
#include "Query.h"
#include"DMS.h"
#include<queue>
#include<vector>
#include<iostream>
#include <cstdlib>

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

queue<Query*> & Factory::GenerateQueue(const DMS& DMSo, int QueryCount)
{
	int ran;
	//string SearchingTerm;
	//SearchingTerm = SelectSearchingTerm(koDMS, ran);

	Query* p;
	for (int i = 0; i < QueryCount; i++)
	{
		ran = (rand() % 4) + 1;
		char c = ConvertToChar(ran);

		string SearchTerm;
		switch (ran)
		{
		case 1:
			this->SearchingTerms1 = DMSo.GetFullNameTerms();
			break;
		case 2:
			this->SearchingTerms1 = DMSo.GetPersonEmailDomainTerms();
			break;
		case 3:
			this->SearchingTerms1 = DMSo.GetAreaCodeTerms();
			break;
		case 4:
			this->SearchingTerms1 = DMSo.GetBusinessEmailDomainTerms();
			break;
		}
		int randomIndex = rand() % SearchingTerms1.size();
		SearchTerm = SearchingTerms1[randomIndex];
		Queue.push(new Query(c, SearchTerm));

		/*while (!Queue.empty())
		{
			p = Queue.front();
			std::cout << " Query" << p->MSelection() << "\t SearchingTerm" << p->MSearch();
			Queue.pop();
		}
		cout << std::endl;*/
	}
	//cin.get();
	
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

/*string Factory::SelectSearchingTerm(DMS DMSo, int b)
{
	string SearchTerm;
	switch (b)
	{
	case 1:
		this->SearchingTerms1 = DMSo.GetFullNameTerms();
		break;
	case 2:
		this->SearchingTerms1 = DMSo.GetPersonEmailDomainTerms();
		break;
	case 3:
		this->SearchingTerms1 = DMSo.GetAreaCodeTerms();
		break;
	case 4:
		this->SearchingTerms1 = DMSo.GetBusinessEmailDomainTerms();
		break;
	}

	int randomIndex = rand() % SearchingTerms1.size();
	SearchTerm = SearchingTerms1[randomIndex];
	return SearchTerm;
}*/
