/**
 * @file       Contact.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-12-07
 * @compiler   Visual C++ 2017
 *
 * @brief Contact class interface
 */
#ifndef Contact_h
#define Contact_h

#include <string>

class Contact
{
private:
   std::string voName;

public:
   Contact( const std::string& aorName = "" );
   Contact( const Contact& aorContact );
   virtual ~Contact( void );

   Contact& operator=( const Contact& aorContact );

   virtual void display( void ) const;
};

#endif
