#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class commands
{
public:

    void today()
    {
        time_t now = time(0);
        char *date = ctime(& now);
        string month;
        string m = "";
        string day = "";
        string time = "";
        day += date[8];
        day += date[9];
        for(int i = 11; i < 16; i++)
            time+=date[i];
        for(int i = 4; i < 7; i++)
            m+=date[i];
        if(m == "Jan")
            month = "01";
        else if(m == "Feb")
            month = "02";
        else if(m == "Mar")
            month = "03";
        else if(m == "Apr")
            month = "04";
        else if(m == "May")
            month = "05";
        else if(m == "Jun")
            month = "06";
        else if(m == "Jul")
            month = "07";
        else if(m == "Aug")
            month = "08";
        else if(m == "Sep")
            month = "09";
        else if(m == "Oct")
            month = "10";
        else if(m == "Nov")
            month = "11";
        else if(m == "Dec")
            month = "12";

        cout << month << "-" << day << " " << time << endl;
    }






};

#endif // COMMANDS_H_INCLUDED
