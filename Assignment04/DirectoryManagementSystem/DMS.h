#ifndef DMS_h
#define DMS_h

#include "Contact.h"
#include <string>
#include <map>

class DMS
{
private:       // Private Attributes
   std::multimap< std::string, Contact* > voDirectory;

public:        // Public Methods
   DMS( void );
   ~DMS( void );
};

#endif

