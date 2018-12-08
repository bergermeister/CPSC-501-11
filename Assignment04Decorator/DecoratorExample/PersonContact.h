/**
 * @file       PersonContact.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Person Contact class interface
 */
#ifndef PersonContact_h
#define PersonContact_h

#include "Contact.h"
#include <string>

class PersonContact : public Contact
{
private:
   std::string voGender;

public:
   PersonContact( const std::string& aorName = "", const std::string& aorGender = "" );
   PersonContact( const PersonContact& aorContact );
   virtual ~PersonContact( void );

   PersonContact& operator=( const PersonContact& aorContact );

   virtual void display( void ) const;
};

#endif

