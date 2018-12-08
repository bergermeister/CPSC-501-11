/**
 * @file       ContactDecorator.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Contact Decorator class interface
 */
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
