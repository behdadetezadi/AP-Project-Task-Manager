#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include <vector>
#include "Time.h"
#include "task.h"
#include <string>
using namespace std;

class Employee
{
public:
    //EMPLOYEE CONSTRUCTOR
   Employee(string n, long id, Time s, Time f)
   {
       name = n;
       ssid = id;
       start = s;
       finish = f;
   }


    long get_ssid()
    {
        return ssid;
    }

    // add a task to jobs vector
   void add_job(Task& to_add)
   {
       jobs.push_back(to_add);
       //cout << "done" << endl;
   }

   //clear the jobs from tasks of a specific day
   void clear_day(int month, int day)
   {
       vector<Task> temp;
       for(auto it = jobs.begin(); it != jobs.end(); ++it)
       {
           if(!((*it).get_month() == month && (*it).get_day() == day))
           {
                temp.push_back(*it);
           }
       }
       jobs.clear();
       for(auto it = temp.begin(); it != temp.end(); ++it)
        {
            jobs.push_back(*it);
        }
   }

   //print assigned tasks
   void print_tasks()
    {
        for(auto it = jobs.begin(); it != jobs.end(); ++it)
        {
            cout << (*it).get_title() << endl;
        }

    }

private:
    string name;
    long ssid;
    Time start;
    Time finish;
    vector<Task> jobs;
};



#endif // EMPLOYEE_H_INCLUDED
