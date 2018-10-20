// mytime3.h -- Time class with friends
#ifndef Time_h
#define Time_h
#include <iostream>
#include <ctime>
#include <iomanip>

class Time
{
private:
    int hours;
    int minutes;

public:
    Time( void )
    {
      hours = minutes = 0;
    }
    Time( int h, int m = 0 );
    Time( const Time& aorTime )
    {
       *this = aorTime;
    }
    ~Time( void )
    {
       // Nothing to destruct
    }
    Time& operator=( const Time& aorTime )
    {
      this->hours   = aorTime.hours;
      this->minutes = aorTime.minutes;

      return( *this );
    }

    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h = 0, int m = 0);
    Time operator+(const Time & t) const;
    Time operator-(const Time & t) const;
    Time operator*(double n) const;
    bool operator<( const Time& aorTime ) const
    {
      bool kbLT = false;

      if( this->hours < aorTime.hours )
      {
         kbLT = true;
      }
      else if( ( this->hours == aorTime.hours ) && ( this->minutes < aorTime.minutes ) )
      {
         kbLT = true;
      }

      return( kbLT );
    }
    bool operator()( const Time& aorT1, const Time& aorT2 ) const
    {
       return( aorT1 < aorT2 );
    }
    friend Time operator*(double m, const Time & t)
        { return t * m; }   // inline definition
    friend std::ostream& operator<<( std::ostream& os,    const Time & t)
   {
      std::tm koTM;
      koTM.tm_hour = t.hours;
      koTM.tm_min  = t.minutes;

      // put_time errors out on 4:60, which is not a valid time
      // TODO: os << std::put_time( &koTM, "%H:%M" );

       os << t.hours << ":" << t.minutes;

       return os; 
   }
    friend std::istream& operator>>( std::istream& aorIn, Time& aorTime )
    {
      char kcColon;

      aorIn >> aorTime.hours >> kcColon >> aorTime.minutes;

      return( aorIn );
    }
};
#endif
