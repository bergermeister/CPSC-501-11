#include "Sets.h"
#include <iostream>
#include <fstream>

int main( int aiArgc, char** acpArgv )
{
   int           kiStatus = 0;
   std::string   koSet[ 2 ];
   std::ifstream koFin;
   Sets          koSets;

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
            // Read 2 lines at a line. Each line is expected to be a set
            std::getline( koFin, koSet[ 0 ] );
            std::getline( koFin, koSet[ 1 ] );

            koSets.MProcess( koSet[ 0 ], koSet[ 1 ] );
         }

         /* Close the file stream */
         koFin.close( );
      }
   }

   std::cout << "Press enter key to continue ...";
   getchar( );

   return( kiStatus );
}
