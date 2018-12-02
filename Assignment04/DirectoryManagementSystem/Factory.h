#include "Contact.h"
#include <string>
#include <map>
#include <queue>
#include <queue>
#include "Query.h"
#include"DMS.h"

using namespace std;
class Factory
{
public:

	Factory();
	Factory(Factory & F);
	~Factory();
	Factory& operator=(const Factory& F);
	void GenerateSerchingTerms();
	queue<Query*> GenerateQueue(DMS& DMSo, int QueryCount);
	
private:
	//int QueryCount;
	char QueryChar;
	string QueryTerm;
	queue<Query*> Queue;
	vector<string> SearchingTerms1;
	char ConvertToChar(int a);
	string SelectSearchingTerm(DMS DMSo, int b);
};
