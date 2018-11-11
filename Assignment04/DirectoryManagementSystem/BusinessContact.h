/**
 * @file       BusinessContact.h
 * @author     Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Business Contact class interface
 */
#ifndef BusinessContact_h
#define BusinessContact_h

#include "Contact.h"
class BusinessContact : public Contact
{
private:
   std::string voType;

public:
   BusinessContact( const std::string& aorName = "", const std::string& aorType = "" );
   BusinessContact( const BusinessContact& aorBusiness );
   virtual ~BusinessContact( void );

   BusinessContact& operator=( const BusinessContact& aorBusiness );

   virtual void display( void );
};

#endif
