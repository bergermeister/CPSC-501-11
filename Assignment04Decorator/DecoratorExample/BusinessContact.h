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

