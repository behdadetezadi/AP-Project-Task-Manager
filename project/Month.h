#ifndef MONTH_H_INCLUDED
#define MONTH_H_INCLUDED

#include <vector>
#include "Day.h"


class Month
{
public:

    //subscript operator overload for finding day
    Day& operator[](int index)
    {
        return days[index];
    }

    //getter setter for number of days 31/30/29/28
    int get_numberofdays()
    {
        return numberofdays;
    }

    void set_numberofdays(int n){numberofdays = n;}

private:
    Day days[32];
    int numberofdays;

};


#endif // MONTH_H_INCLUDED
