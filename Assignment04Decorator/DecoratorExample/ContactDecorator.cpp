/**
 * @file       ContactDecorator.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Contact Decorator class implementation
 */
#include "ContactDecorator.h"
#include "Contact.h"
#include <iostream>

ContactDecorator::ContactDecorator( Contact* aopContact )
{
   this->vopContact = aopContact;
}

ContactDecorator::ContactDecorator( const ContactDecorator& aorDecorator )
{
   // Call the assignment operator
   *this = aorDecorator;
}

ContactDecorator::~ContactDecorator( void )
{
   // Nothing to destruct
}

ContactDecorator& ContactDecorator::operator=( const ContactDecorator& aorDecorator )
{
   if( this != &aorDecorator )
   {
      this->vopContact = aorDecorator.vopContact;
   }

   return( *this );
}

void ContactDecorator::display( void ) const
{
   if( this->vopContact != nullptr )
   {
      this->vopContact->display( );
   }
}
