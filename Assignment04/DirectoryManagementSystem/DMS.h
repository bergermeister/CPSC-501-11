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
   DMS( const DMS& aorDMS );
   ~DMS( void );

   DMS& operator=( const DMS& aorDMS );

   // TODO Implement input file read (validate each field)
   // TODO Implement Search Query
   // TODO Implement Display Query
};

#endif

