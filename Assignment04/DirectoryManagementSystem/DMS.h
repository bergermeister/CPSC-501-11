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
   std::vector< std::string >             voResults;

public:        // Public Methods
	DMS( void );
	DMS( const DMS& aorDMS );
   ~DMS( void );
   
   DMS& operator=( const DMS& aorDMS );

   void CreateDirectory( std::string Name, Contact* ContInfo); // Create directory of contacts
	void DisplayDirectory( void ); // Display just for testing :)
   void populateDirectory( const std::string& aorFile );
   void query( const char acResponse );
   void display_results( void );
  
private:       // Private Methods
   void split( const std::string& s, std::vector< std::string >& v );
   void mParsePerson( const std::string& aorLine );
   void mParseBusiness( const std::string& aorLine );
   
   bool mIsPhoneNum( const std::string& aorStr );
   bool mIsEmail( const std::string& aorStr );
   bool mIsNumber( const char acChar );

   void mQuery1( void );
   static bool mCompareAddress( Contact* aopContact1, Contact* aopContact2 );
   static std::string mTrim( const std::string& aorStr );
};

#endif

