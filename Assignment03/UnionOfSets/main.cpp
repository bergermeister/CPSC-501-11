/**
 * @file       main.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Main driver application for the Union of Sets class
 */
#include "Sets.h"
#include <iostream>
#include <fstream>

static void MGenerateFile( const int aiInitialSize, const int aiSetCount );

/**
 * @brief Main driver application entry
 *
 * Main driver application that instantiates an instance of the Union of Sets class,
 * reads in the set data from the input file, and passes the set data into the Union 
 * of Sets class
 *
 * @return  Execution status, 0 is success, all others indicate errors
 *
 * @par Formal Parameters
 * @PRM{ in, aiArgc,    Number of arguments }
 * @PRM{ in, acpArgv,   C-String arguments passed in at launch }
 *
 * @par Local Symbols
 * @LOC{ kiStatus,    Execution status }
 * @LOC{ kiLineNum,   Line number of the last line read from the input file }
 * @LOC{ koSetStr,    String representing a set of elements }
 * @LOC{ koFin,       Input File Stream }
 * @LOC{ koSets,      Union of Sets object }
 */
int main( int aiArgc, char** acpArgv )
{
   int           kiStatus = 0;
   int           kiLineNum = 0;
   std::string   koSetStr;
   std::ifstream koFin;
   int Count = 10;


   MGenerateFile( 100, 5 );

   // If no arguments were specified 
   if( aiArgc < 2 )
   {
      // Indicate error to user
      std::cerr << "Invalid number of arguments. ";
      std::cerr << "Please enter the file path for the input file.";
      std::cerr << std::endl;
      kiStatus = 1;
   }
   // At least one argument was specified
   else
   {
      // First argument must be input file, open it
      koFin.open( acpArgv[ 1 ], std::ifstream::in );

      // If the file failed to open
      if( !koFin.is_open( ) )
      {
         // Indicate error to user
         std::cerr << "Failed to open file: " << acpArgv[ 1 ] << std::endl;
         kiStatus = 2;
      }
      // Else parse the input file
      else
      {
         // Read to the end of the file
         while( !koFin.eof( ) )
         {
			 Count = Count * 10;
			 std::cout << "Number of Elements are :" << Count;
			 Sets          koSets;
            // Read a line. Each line is expected to be a set
            std::getline( koFin, koSetStr );
            kiLineNum++;

            // Process the sets
			koSets.MProcess(koSetStr);
			std::getline(koFin, koSetStr);
			kiLineNum++;

			// Process the sets
			koSets.MProcess(koSetStr);
         }

         // Close the file stream
         koFin.close( );

         // Print the results
         //std::cout << "Union of sequences are:" << std::endl;
        // std::cout << koSets << std::endl;
      }
   }

   std::cout << "Press enter key to continue ...";
   getchar( );

   return( kiStatus );
}

static void MGenerateFile( const int aiInitialSize, const int aiSetCount )
{
   int kiSize = aiInitialSize;
   int kiIdx;
   int kiSet;
   int kiLoop;
   int kiVal;
   std::ofstream koOut;

   srand( time( NULL ) );

   koOut.open( "InputTiming.txt" );

   for( kiSet = 0; kiSet < aiSetCount; kiSet++ )
   {
      for( kiLoop = 0; kiLoop < 2; kiLoop++ )
      {
         for( kiIdx = 0; kiIdx < kiSize; kiIdx++ )
         {
            kiVal = rand( ) % kiSize;

            koOut << kiVal; 
            if( kiIdx < kiSize - 1 )
            {
               koOut << ",";
            }
            else
            {
               koOut << std::endl;
            }
         }
      }
      kiSize *= 10;
   }
}
