/**
 * @file       Sets.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Implementation for the Union of Sets class
 */
#include "Sets.h"
#include "Time.h"
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <strstream>
#include <iomanip>

/**
 * @brief Default Constructor
 *
 * Constructs a Union of Sets object and empties the internal multisets to empty
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ None }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Sets::Sets( void )
{
   this->voSetInt.clear( );
   this->voSetDbl.clear( );
   this->voSetTme.clear( );
   this->voSetStr.clear( );
}

/**
 * @brief Copy Constructor
 *
 * Calls the assignment operator to copy the data of the given Union of Sets
 * to this Union of Sets
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ in, aorSets,   Reference to Union of Sets object to copy }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Sets::Sets( const Sets& aorSets )
{
   // Call assignment operator
   *this = aorSets;
}

/**
 * @brief Destructor
 *
 * Destructs the Union of Sets object
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ None }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Sets::~Sets( void )
{
   // Nothing to destruct
}

/**
 * @brief Assignment operator
 *
 * Copies the data of the given Union of Sets to this Union of Sets
 *
 * @return  Reference to this Union of Sets
 *
 * @par Formal Parameters
 * @PRM{ in, aorSets,   Reference to Union of Sets object to copy }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Sets& Sets::operator=( const Sets& aorSets )
{
   this->voSetInt = aorSets.voSetInt;
   this->voSetDbl = aorSets.voSetDbl;
   this->voSetTme = aorSets.voSetTme;
   this->voSetStr = aorSets.voSetStr;

   return( *this );
}

/**
 * @brief Converts the input string into a multiset and unions it with the working set
 *
 * Converts the input string into a multiset and unions it with the corresponding work set
 *
 * @return  True if conversion and union were successful, false otherwise
 *
 * @par Formal Parameters
 * @PRM{ in, aoSetStr,   String of a set }
 *
 * @par Local Symbols
 * @LOC{ kbStatus,   Call success indication }
 * @LOC{ koSetStr,   Local, modifiable copy of the set string }
 * @LOC{ koWord,     Word parsed from the string }
 * @LOC{ keType,     Type of the word parsed from the string }
 */
bool Sets::MProcess( const std::string aoSetStr )
{
   using std::string;
   using std::multiset;
   using std::vector;

   bool   kbStatus = true;       // Assume success
   string koSetStr = aoSetStr;   // Local, modifiable copy of the set string
   string koWord;
   teType keType;

   // Parse the first word in the string to determine it's type
   keType = this->mParseWord( koSetStr.begin( ), koSetStr.end( ), koWord );

   // Replace the commas with spaces to allow the operator>> to work for strings
   std::replace( koSetStr.begin( ), koSetStr.end( ), ',', ' ' );

   try
   {
      // Based on the type of the first word, union the working set
      switch( keType )
      {
         case xeTypeInt:
         {
            auto koSet     = this->MParse< int >( koSetStr, kbStatus );    // Create set of integers from the string
            this->voSetInt = this->MUnion< int >( this->voSetInt, koSet ); // Union the new set with the working set
            this->voSetInt = this->MUnique( this->voSetInt );              // Remove duplicate values
            break;
         }
         case xeTypeString:
         {
            auto koSet     = this->MParse< std::string >( koSetStr, kbStatus );     // Create set of strings from the string
            this->voSetStr = this->MUnion< std::string >( this->voSetStr, koSet );  // Union the new set with the working set
            this->voSetStr = this->MUnique( this->voSetStr );                       // Remove duplicate values
            break;
         }
         case xeTypeTime:
         {
            auto koSet     = this->MParse< Time >( koSetStr, kbStatus );      // Create a set of Time objects from the string
            this->voSetTme = this->MUnion< Time >( this->voSetTme, koSet );   // Union the new set with the working set
            this->voSetTme = this->MUnique( this->voSetTme );                 // Remove duplicate values
            break;
         }
         case xeTypeDouble:
         {
            auto koSet     = this->MParse< double >( koSetStr, kbStatus );    // Create a set of doubles from the string
            this->voSetDbl = this->MUnion< double >( this->voSetDbl, koSet ); // Union the new set with the working set
            this->voSetDbl = this->MUnique( this->voSetDbl );                 // Remove duplicate values
         }
         default:
            kbStatus = false;
            break;
      }
   }
   catch( std::exception aoException )
   {
      std::cerr << "ERROR: Exception encountered while processing type: " << keType << std::endl;
      std::cerr << aoException.what( ) << std::endl;
   }

   return( kbStatus );
}

/**
 * @brief Prints the Union of Sets object data to the output stream
 *
 * Prints the given Union of Sets object data to the given output stream
 *
 * @return  Output stream
 *
 * @par Formal Parameters
 * @PRM{ in, aorOut,    Output stream to print to }
 * @PRM{ in, aorSets,   Union of Sets object to print }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
std::ostream& operator<<( std::ostream& aorOut, const Sets& aorSets )
{
   aorOut << std::fixed << std::setprecision( 2 );

   aorSets.mPrint( aorOut, aorSets.voSetInt, "Union of Integers:" );
   aorOut << std::endl << std::endl;

   aorSets.mPrint( aorOut, aorSets.voSetTme, "Union of Time Objects:" );
   aorOut << std::endl << std::endl;

   aorSets.mPrint( aorOut, aorSets.voSetStr, "Union of Strings:" );
   aorOut << std::endl << std::endl;

   aorSets.mPrint( aorOut, aorSets.voSetDbl, "Union of Doubles:" );
   aorOut << std::endl << std::endl;

   return( aorOut );
}

/**
 * @brief Determines the type of the element pointed to by the string iterator
 *
 * Parses a single word starting at the given Begin iterator and returns its type.
 *
 * @return  Type of the next element
 *
 * @par Formal Parameters
 * @PRM{ in,  aoBegin,   Iterator pointing to the start of the word }
 * @PRM{ in,  aoEnd,     Iterator pointing to the end of the string }
 * @PRM{ out, aorWord,   Word parsed from the string }
 *
 * @par Local Symbols
 * @LOC{ keType,   Type of the parsed word }
 */
Sets::teType Sets::mParseWord( std::string::iterator aoBegin, const std::string::iterator aoEnd, std::string& aorWord )
{
   teType keType = xeTypeInt;    // Assume int

   // Initialize the word to empty string
   aorWord = "";

   // Find the next delimiter (,) or end of string
   for( ; aoBegin != aoEnd; aoBegin++ )
   {
      // If the current character is the delimiter
      if( *aoBegin == ',' )
      {
         // Move past the delimiter and break out of the loop
         aoBegin++;
         break;
      }
      else
      {
         aorWord += *aoBegin;
      }

      // If the current type is int
      if( keType == xeTypeInt )
      {
         // If a ':' is encountered
         if( *aoBegin == ':' )
         {
            keType = xeTypeTime; // Switch to time object
         }
         // If a '.' is encountered
         else if( *aoBegin == '.' )
         {
            keType = xeTypeDouble; // Switch to double
         }
         // Else if the current character is not a number and not a space
         else if( ( ( *aoBegin < '0' ) || ( *aoBegin > '9' ) ) && ( *aoBegin != ' ' ) )
         {
            keType = xeTypeString; // Switch to string
         }
      }
   }

   return( keType );
}

