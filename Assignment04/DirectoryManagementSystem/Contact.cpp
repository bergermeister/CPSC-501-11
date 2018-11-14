/**
 * @file       Contact.cpp
 * @author     Edward Eisenberger
 * @date       2018-11-11
 * @compiler   Visual C++ 2017
 *
 * @brief Contact class implementation
 */
#include "Contact.h"
#include <string>
#include <iostream>

Contact::Contact( const std::string& aorName )
{
   this->voName = aorName;
}

Contact::Contact( const Contact& aorContact )
{
   // Call assignment operator
   *this = aorContact;
}

Contact::~Contact( void )
{
   // Nothing to destruct
}

Contact& Contact::operator=( const Contact& aorContact )
{
   // Copy Contact attributes
   this->voName = aorContact.voName;

   return( *this );
}

void Contact::display( void )
{
   std::cout << "Contact" << std::endl;
}

std::string Contact::MGetFullName( void ) const
{
   return( this->voName );
}

std::string Contact::MGetFirstName( void ) const
{
   return( mSplit( this->voName, ' ' )[ 0 ] );
}

std::string Contact::MGetMiddleName( void ) const
{
   std::vector< std::string > koWords = mSplit( this->voName, ' ' );
   std::string                koMiddle = "";
   auto                       koIter = koWords.begin( );
   auto                       koEnd  = koWords.end( );

   if( koWords.size( ) > 2 )
   {
      koIter++;   // Skip the first word
      koEnd--;    // Skip the last word
      while( koIter != koEnd )
      {
         koMiddle += *koIter + " ";
      }
   }

   return( koMiddle );
}

std::string Contact::MGetLastName( void ) const
{
   std::vector< std::string > koWords = mSplit( this->voName, ' ' );
   std::string                koLast = "";

   if( koWords.size( ) > 1 )
   {
      koLast = koWords[ koWords.size( ) - 1 ];
   }

   return( koLast );
}

std::vector< std::string > Contact::mSplit( std::string aoString, char acDelim )
{
   std::vector< std::string > koWords;
   std::string                koWord = "";

   for( auto koIter = aoString.begin( ); koIter != aoString.end( ); koIter++ )
   {
      if( *koIter == acDelim )
      {
         koWords.push_back( koWord );
         koWord = "";
      }
      else
      {
         koWord += *koIter;
      }
   }

   koWords.push_back( koWord );

   return( koWords );
}
