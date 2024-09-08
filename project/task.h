#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED
#include <iostream>
#include <string>
#include<string.h>
using namespace std;


#include "Time.h"






class Task
{
public:
    //normal constructor
    Task()
    {

    };

    //constructor with given info
    Task(string t, string d, string m, string s, string f)
    {
        title = t;

        //converting strings to type int
        stringstream dd(d);
        dd >> day;
        stringstream mm(m);
        mm >> month;
        string s_hour = ""; s_hour += s[0]; s_hour += s[1]; stringstream ssh(s_hour); int x = 0; ssh >> x; start.set_hour(x);
        string s_minute =  ""; s_minute += s[3]; s_minute += s[4]; stringstream ssm(s_minute); ssm >> x; start.set_minute(x);
        string f_hour = ""; f_hour += f[0]; f_hour += f[1]; stringstream ffh(f_hour); ffh >> x; finish.set_hour(x);
        string f_minute = ""; f_minute += f[3]; f_minute += f[4]; stringstream ffm(f_minute); ffm >> x; finish.set_minute(x);

    }


    //getter functions
    string get_title() const {return title;}
    int get_day()const {return day;}
    int get_month()const {return month;}
    Time& get_finish() {return finish;}
    Time& get_start() {return start;}



    //write function for writing on binary file for resolving string writing problem
    void write(ostream& out)
    {
        //writing string
        size_t size;
        size = title.size();
        out.write((char*)(&size), sizeof(size_t));
        out.write((char*)title.c_str(), size);

        out.write((char*)&day, sizeof(int));
        out.write((char*)&month, sizeof(int));
        out.write((char*)&start, sizeof(Time));
        out.write((char*)&finish, sizeof(Time));
    }

    //read function with the correct order
    void read(istream& f)
    {
        //reading string
        size_t size;
        char* data;
        f.read((char*)&size, sizeof(size));
        data = new char[size + 1];
        f.read(data, size);
        data[size] = '\0';
        title = data;

        f.read((char*) &day, sizeof(int));
        f.read((char*) &month, sizeof(int));

        f.read((char*) &start, sizeof(Time));
        f.read((char*) &finish, sizeof(Time));


        delete data;
    }


/*/
    bool has_conflict(Task &t)
    {
        if(t.get_month() != month)
            return false;
        else if(t.get_day() != day)
            return false;
        else
        {
            if(finish <= t.get_start() || start >= t.get_finish())
                return false;
        }
        return true;
    }
/*/
private:
    string title;
    int day;
    int month;
    Time start;
    Time finish;
};



#endif // TASK_H_INCLUDED
