#ifndef DMS_h
#define DMS_h

#include "Contact.h"
#include <string>
#include <map>
using namespace std;

class DMS
{
private:       // Private Attributes
   std::multimap< std::string, Contact* > voDirectory;

public:        // Public Methods
	DMS(void);
	void CreateDirectory(string Name, Contact* ContInfo); // Create directory of contacts
	void DisplayDirectory(); // Display just for testing :)
	DMS(const DMS& aorDMS);
   ~DMS(void);
   void PopulateDirectory(string FileName);
   DMS& operator=( const DMS& aorDMS );

   // TODO Implement input file read (validate each field)
   // TODO Implement Search Query
   // TODO Implement Display Query
};

#endif

