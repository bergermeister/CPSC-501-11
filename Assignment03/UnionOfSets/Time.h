/**
 * @file       Time.h
 * @author     Edward Eisenberger, Zainab Al Taweel, Udaya Sree Reddy Teegulla
 * @date       2018-10-20
 * @compiler   Visual C++ 2017
 *
 * @brief Interface for the Time class
 */
#ifndef Time_h
#define Time_h

#include <iostream>
#include <ctime>
#include <iomanip>

/** @brief Time class */
class Time
{
private:
    int viHours;     /**< Storage for hours */
    int viMinutes;   /**< Storage for minutes */

public:
   Time( void );
   Time( int aiHours, int aiMinutes = 0 );
   Time( const Time& aorTime );
   ~Time( void );

   Time& operator=( const Time& aorTime );

   void AddMin( int aiMinutes );
   void AddHr ( int aiHours );
   void Reset ( int aiHours = 0, int aiMinutes = 0 );
   Time operator+( const Time& aorTime ) const;
   Time operator-( const Time& aorTime ) const;
   Time operator*( double adFactor ) const;
   bool operator<( const Time& aorTime ) const;
   bool operator()( const Time& aorT1, const Time& aorT2 ) const;
   friend Time operator*( double adFactor, const Time& aorTime );
   friend std::ostream& operator<<( std::ostream& aorOut, const Time& aorTime );
   friend std::istream& operator>>( std::istream& aorIn,  Time& aorTime );
};

#endif
