/**
 * @file       Sets.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Interface for the Union of Sets class
 */
#ifndef Sets_h
#define Sets_h

#include "Time.h"
#include <set>
#include <string>
#include <iostream>
#include <strstream>
#include <algorithm>
#include <iterator>

/** @brief Union of Sets class */
class Sets
{
private:       // Private Attributes
   /** @brief enumeration of supported types */
   enum teType
   {
      xeTypeUnknown = 0,
      xeTypeInt     = 1,
      xeTypeString  = 2,
      xeTypeTime    = 3,
      xeTypeDouble  = 4
   };

   std::multiset< int >         voSetInt; /**< Unique Union Set of Integers */
   std::multiset< Time >        voSetTme; /**< Unique Union Set of Time objects */
   std::multiset< std::string > voSetStr; /**< Unique Union Set of Strings */
   std::multiset< double >      voSetDbl; /**< Unique Union Set of Doubles */

public:        // Public Methods
   Sets( void );
   Sets( const Sets& aorSets );
   ~Sets( void );

   Sets& operator=( const Sets& aorSets );

   bool MProcess( const std::string aoSetStr );
   std::multiset< int >         MGetSetInt( void ) const;
   std::multiset< Time >        MGetSetTme( void ) const;
   std::multiset< std::string > MGetSetStr( void ) const;
   std::multiset< double >      MGetSetDbl( void ) const;

   friend std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets );

   /**
    * @brief Parses a string into a multiset of generic type
    *
    * Template method which parses the input string into a multiset of the instantiated type.
    *
    * @return  std::multiset of the instantiated type
    *
    * @par Formal Parameters
    * @PRM{ in, aoSetStr,     String representation of a set }
    * @PRM{ in, abrSuccess,   Call success indication }
    *
    * @par Local Symbols
    * @LOC{ koTemp,     Temporary storage for an individual element }
    * @LOC{ koSet,      multiset of parsed data to be returned }
    * @LOC{ koStream,   String stream used to parse the input string }
    */
   template< class GTcType >
   std::multiset< GTcType > MParse( const std::string aoSetStr, bool& abrSuccess )
   {
      GTcType                  koTemp;
      std::multiset< GTcType > koSet;
      std::istrstream          koStream( aoSetStr.c_str( ) );

      try
      {
         while( !koStream.fail( ) )
         {
            // Attempt to read an element from the string
            koStream >> koTemp;

            // Insert the element if the read was successful
            if( !koStream.fail( ) )
            {
               koSet.insert( koTemp );
            }
         }

         // Success only if end of stream is reached, otherwise data was missed
         abrSuccess = koStream.eof( );
      }
      catch( std::exception aoException )
      {
         std::cerr << "ERROR: Failed to parse string - " << aoSetStr << std::endl;
         std::cerr << aoException.what( );
         abrSuccess = false;
      }

      return( koSet );
   }

   /**
    * @brief Returns the union of two generic sets of the same type
    *
    * Performs std::set_union on the two given generic sets and returns the result
    *
    * @return  std::multiset of the union of the two sets
    *
    * @par Formal Parameters
    * @PRM{ in, aorSet1,   First multiset }
    * @PRM{ in, aorSet2,   Second multiset }
    *
    * @par Local Symbols
    * @LOC{ koUnion,   multiset union of the two sets }
    */
   template< class GTcType >
   std::multiset< GTcType > MUnion( const std::multiset< GTcType >& aorSet1, const std::multiset< GTcType >& aorSet2 )
   {
      std::multiset< GTcType > koUnion;
      try
      {
         std::set_union( aorSet1.begin( ), aorSet1.end( ), aorSet2.begin( ), aorSet2.end( ),
                         std::insert_iterator< std::multiset< GTcType > >( koUnion, koUnion.begin( ) ) );
      }
      catch( std::exception aoException )
      {
         std::cerr << "ERROR: Failed to perform std::set_union" << std::endl;
         std::cerr << aoException.what( );
      }

      return( koUnion );
   }
   
   /**
    * @brief Returns a multiset of unique elements
    *
    * Executes std::unique_copy to find the unique elements of the given multiset and returns it
    *
    * @return  multiset of unique elements
    *
    * @par Formal Parameters
    * @PRM{ in, aorSet,   Input multiset }
    *
    * @par Local Symbols
    * @LOC{ koUnique,   multiset of unique elements }
    */
   template< class GTcType >
   std::multiset< GTcType > MUnique( const std::multiset< GTcType >& aorSet )
   {
      std::multiset< GTcType > koUnique;
      
      try
      {
         std::unique_copy( aorSet.begin( ), aorSet.end( ),
                           std::insert_iterator< std::multiset< GTcType > >( koUnique, koUnique.begin( ) ) );
      }
      catch( std::exception aoException )
      {
         std::cerr << "ERROR: Failed to perform std::unique_copy" << std::endl;
         std::cerr << aoException.what( );
      }

      return( koUnique );
   }

private:       // Private Methods
   teType mParseWord( std::string::iterator aoBegin, const std::string::iterator aoEnd, std::string& aorWord );

   /**
    * @brief Prints the given multiset to the given stream
    *
    * Prints the title and formatted multiset data to the given stream
    *
    * @return  Output stream
    *
    * @par Formal Parameters
    * @PRM{ in, aorOut,     Output stream to print to }
    * @PRM{ in, aorSet,     multiset to print to the stream }
    * @PRM{ in, aorTitle,   Title to print before multiset data }
    *
    * @par Local Symbols
    * @LOC{ koIter,   multiset iterator }
    */
   template< class GTcType >
   std::ostream& mPrint( std::ostream& aorOut, const std::multiset< GTcType >& aorSet, const std::string aorTitle ) const
   {
      auto koIter = aorSet.begin( );

      // Print the title
      aorOut << aorTitle << std::endl;

      aorOut << "[ ";

      if( aorSet.size( ) > 0 )
      {
         try
         {
            // Print the data
            aorOut << *koIter++;
            for( ; koIter != aorSet.end( ); koIter++ )
            {
               aorOut << ", " << *koIter ;
            }
         }
         catch( std::exception aoException )
         {
            std::cerr << "ERROR: Failed to print set" << std::endl;
            std::cerr << aoException.what( );
         }
      }

      aorOut << " ]";

      return( aorOut );
   }
};

#endif

