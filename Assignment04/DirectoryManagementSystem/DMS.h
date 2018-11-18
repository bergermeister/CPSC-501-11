#ifndef DMS_h
#define DMS_h

#include "Contact.h"
#include <string>
#include <map>
#include <vector>

class DMS
{
private:       // Private Attributes
   enum teField
   {
      xeFieldName = 0,
      xeFieldType,
      xeFieldPPhone,
      xeFieldEmail,
      xeField
   };

   std::multimap< std::string, Contact* > voDirectory;

public:        // Public Methods
	DMS( void );
	DMS( const DMS& aorDMS );
   ~DMS( void );
   
   DMS& operator=( const DMS& aorDMS );

   void CreateDirectory( std::string Name, Contact* ContInfo); // Create directory of contacts
	void DisplayDirectory( void ); // Display just for testing :)
   void populateDirectory( const std::string& aorFile );
   void query( const char acResponse );

   // TODO Implement input file read (validate each field)
   // TODO Implement Search Query
   // TODO Implement Display Query
  
private:       // Private Methods
   //void mQueryHelper( const std::vector< std::string >& aorWords, const int aiIndex );
   //void mQueryFirstName( void );
   void split( const std::string& s, std::vector< std::string >& v );
   void mParsePerson( const std::string& aorLine );
   void mParseBusiness( const std::string& aorLine );
   
   bool mIsPhoneNum( const std::string& aorStr );
   bool mIsEmail( const std::string& aorStr );
   bool mIsNumber( const char acChar );
};

#endif

