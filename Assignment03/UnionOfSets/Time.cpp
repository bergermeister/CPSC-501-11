/**
 * @file       Time.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Implementation for the Time class
 */
#include "Time.h"

/**
 * @brief Default Constructor
 *
 * Constructs a Time object
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ None }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Time::Time( void )
{
   viHours = viMinutes = 0;
}

/**
 * @brief Parameterized Constructor
 *
 * Constructs a Time object and initializes its members to the given values
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ in, aiHours,     Initialization value for hours }
 * @PRM{ in, aiMinutes,   Initialization value for minutes }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Time::Time( int aiHours, int aiMinutes )
{
   viHours = aiHours;
   viMinutes = aiMinutes;
}

/**
 * @brief Copy Constructor
 *
 * Constructs a Time object and initializes its members to the given Time object's members
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ in, aorTime,   Time object to copy }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Time::Time( const Time& aorTime )
{
   *this = aorTime;
}

/**
 * @brief Destructor
 *
 * Destructs the Time object
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ None }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Time::~Time( void )
{
   // Nothing to destruct
}

/**
 * @brief Assignment operator
 *
 * Copies the hours and minutes of the given Time object to this Time object
 *
 * @return  Reference to this Time object
 *
 * @par Formal Parameters
 * @PRM{ in, aorTime,   Time object to copy }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
Time& Time::operator=( const Time& aorTime )
{
   this->viHours   = aorTime.viHours;
   this->viMinutes = aorTime.viMinutes;

   return( *this );
}

/**
 * @brief Increment the time by the given number of minutes
 *
 * Increments the time by the given number of minutes and checks for wrapping into hours
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ in, aiMinutes,   Number of minutes to increment the time by }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
void Time::AddMin( int aiMinutes )
{
   viMinutes += aiMinutes;
   viHours   += viMinutes / 60;
   viMinutes %= 60;
}

/**
 * @brief Adds to the number of hours
 *
 * Adds the given hours to the current hours
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ in, aiHours,   Number of hours to add to the Time }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
void Time::AddHr( int aiHours )
{
   viHours += aiHours;
}

/**
 * @brief Resets the hours and minutes to the given hours and minutes
 *
 * Resets the hours and minutes to the given hours and minutes, or 0 if
 * none are provided
 *
 * @return  None
 *
 * @par Formal Parameters
 * @PRM{ in, aiHours,     Initialization value for hours }
 * @PRM{ in, aiMinutes,   Initialization value for minutes }
 *
 * @par Local Symbols
 * @LOC{ None }
 */
void Time::Reset( int aiHours, int aiMinutes )
{
   viHours   = aiHours;
   viMinutes = aiMinutes;
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
Time Time::operator+( const Time& aorTime ) const
{
   Time koSum;

   koSum.viMinutes = viMinutes + aorTime.viMinutes;
   koSum.viHours   = viHours + aorTime.viHours + ( koSum.viMinutes / 60 );
   koSum.viMinutes %= 60;

   return( koSum );
}

Time Time::operator-( const Time& aorTime ) const
{
   Time koDiff;
   int  kiTot1, kiTot2;

   kiTot1           = aorTime.viMinutes + ( 60 * aorTime.viHours );
   kiTot2           = viMinutes + ( 60 * viHours );
   koDiff.viMinutes = ( kiTot2 - kiTot1 ) % 60;
   koDiff.viHours   = ( kiTot2 - kiTot1 ) / 60;

   return( koDiff );
}

Time Time::operator*( double adFactor ) const
{
   Time koResult;
   long kiTotalMin    = ( long )( ( double )viHours * adFactor * 60.0 ) + ( ( double )viMinutes * adFactor );
   koResult.viHours   = kiTotalMin / 60;
   koResult.viMinutes = kiTotalMin % 60;
   return( koResult );
}

bool Time::operator<( const Time& aorTime ) const
{
   bool kbLT = false;

   if( this->viHours < aorTime.viHours )
   {
      kbLT = true;
   }
   else if( ( this->viHours == aorTime.viHours ) && ( this->viMinutes < aorTime.viMinutes ) )
   {
      kbLT = true;
   }

   return( kbLT );
}

bool Time::operator()( const Time& aorT1, const Time& aorT2 ) const
{
   return( aorT1 < aorT2 );
}

bool Time::operator==( const Time& aorTime ) const
{
   return( ( this->viHours == aorTime.viHours ) && ( this->viMinutes == aorTime.viMinutes ) );
}

Time operator*( double adFactor, const Time& aorTime )
{ 
   return( aorTime * adFactor ); 
}

std::ostream& operator<<( std::ostream& aorOut, const Time& aorTime )
{
   std::tm koTM;
   koTM.tm_hour = aorTime.viHours;
   koTM.tm_min  = aorTime.viMinutes;

   // put_time errors out on 4:60, which is not a valid time
   aorOut << std::put_time( &koTM, "%H:%M" );

   return( aorOut ); 
}

std::istream& operator>>( std::istream& aorIn, Time& aorTime )
{
   char kcColon;

   aorIn >> aorTime.viHours >> kcColon >> aorTime.viMinutes;

   if( aorTime.viMinutes >= 60 )
   {
      aorTime.viHours   += aorTime.viMinutes / 60;
      aorTime.viMinutes %= 60;
   }

   return( aorIn );
}
