#ifndef DMS_h
#define DMS_h

#include "Contact.h"
#include <string>
#include <map>
#include <vector>

class DMS
{
private:       // Private Attributes
   std::multimap< std::string, Contact* > voDirectory;

public:        // Public Methods
   DMS( void );
   DMS( const DMS& aorDMS );
   ~DMS( void );

   DMS& operator=( const DMS& aorDMS );

   void populateDirectory( const std::string& aorFile );
   void query( const char acResponse );

   // TODO Implement input file read (validate each field)
   // TODO Implement Search Query
   // TODO Implement Display Query
  
private:       // Private Methods
   void mQueryHelper( const std::vector< std::string >& aorWords, const int aiIndex );
   void mQueryFirstName( void );
};

#endif

