#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

//#include <iostream>
//#include <stdlib.h>
#include <string>
using namespace std;

class Time
{
public:


    //getter setter functions for encapsulation
    unsigned int get_hour(){return hour;}
    unsigned int get_minute(){return minute;}

    void set_hour(unsigned int h){hour = h;}
    void set_minute(unsigned int m){minute = m;}


    //assignment overloading
    void operator = (Time &t)
    {
       hour = t.get_hour();
       minute = t.get_minute();
    }

    //comparison operators overload

    bool operator> (Time &t)
    {
        if(hour > t.get_hour())
            return true;
        else if (hour == t.get_hour() && minute > t.get_minute())
            return true;
        return false;
    }
    bool operator>= (Time &t)
    {
        if(hour > t.get_hour())
            return true;
        else if (hour == t.get_hour() && minute >= t.get_minute())
            return true;
        return false;
    }
     bool operator< (Time &t)
    {
        if(hour < t.get_hour())
            return true;
        else if (hour == t.get_hour() && minute < t.get_minute())
            return true;
        return false;
    }
    bool operator<= (Time &t)
    {
        if(hour < t.get_hour())
            return true;
        else if (hour == t.get_hour() && minute <= t.get_minute())
            return true;
        return false;
    }

    //ostream& operator<<(ostream& os, Time& dt)
    //{
      //  if(dt.minute() < 10)
        //    os << dt.hour << ":0" << dt.minute ;
        //else
         //   os << dt.hour << ":" << dt.minute ;
        //return os;
    //}
private:
    unsigned int hour;
    unsigned int minute;

};



#endif // TIME_H_INCLUDED
