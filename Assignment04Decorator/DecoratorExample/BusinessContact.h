/**
 * @file       BusinessContact.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Business Contact class interface
 */
#ifndef BusinessContact_h
#define BusinessContact_h

#include "Contact.h"
#include <string>

class BusinessContact : public Contact
{
private:
   std::string voType;

public:
   BusinessContact( const std::string& aorName = "", const std::string& aorType = "" );
   BusinessContact( const BusinessContact& aorContact );
   virtual ~BusinessContact( void );

   BusinessContact& operator=( const BusinessContact& aorContact );

   virtual void display( void ) const;
};

#endif

