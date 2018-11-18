/**
 * @file       Contact.h
 * @author     Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Contact class interface
 */
#ifndef Contact_h
#define Contact_h

#include <string>
#include <vector>

class Contact
{
private:
   std::string voName;

public:
   Contact( const std::string& aorName = "" );
   Contact( const Contact& aorContact );
   virtual ~Contact( void );

   Contact& operator=( const Contact& aorContact );

   virtual void display( void );
   virtual bool MIsValid( const std::string& aorStr );

   std::string MGetFullName( void ) const;
   std::string MGetFirstName( void ) const;
   std::string MGetMiddleName( void ) const;
   std::string MGetLastName( void ) const;

public:
   static std::vector< std::string > mSplit( std::string aoString, char acDelim );
};

#endif

