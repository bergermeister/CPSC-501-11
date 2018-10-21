/**
 * @file       Time.cpp
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Implementation for the Time class
 */
#include "Time.h"

Time::Time( void )
{
   viHours = viMinutes = 0;
}

Time::Time( int aiHours, int aiMinutes )
{
   viHours = aiHours;
   viMinutes = aiMinutes;
}

Time::Time( const Time& aorTime )
{
   *this = aorTime;
}

Time::~Time( void )
{
   // Nothing to destruct
}

Time& Time::operator=( const Time& aorTime )
{
   this->viHours   = aorTime.viHours;
   this->viMinutes = aorTime.viMinutes;

   return( *this );
}

void Time::AddMin( int aiMinutes )
{
   viMinutes += aiMinutes;
   viHours   += viMinutes / 60;
   viMinutes %= 60;
}

void Time::AddHr( int aiHours )
{
   viHours += aiHours;
}

void Time::Reset( int aiHours, int aiMinutes )
{
   viHours   = aiHours;
   viMinutes = aiMinutes;
}

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
