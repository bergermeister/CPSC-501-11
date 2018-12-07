#ifndef ContactDecorator_h
#define ContactDecorator_h

#include "Contact.h"

class ContactDecorator: public Contact
{
private:
   Contact* vopContact;

public:
   ContactDecorator( Contact* aopContact );
   ContactDecorator( const ContactDecorator& aorDecorator );
   virtual ~ContactDecorator( void );

   ContactDecorator& operator=( const ContactDecorator& aorDecorator );

   virtual void display( void ) const;
};

#endif
