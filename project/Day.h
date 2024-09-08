#ifndef DAY_H_INCLUDED
#define DAY_H_INCLUDED

#include <vector>
#include <algorithm>
#include "Time.h"
#include "task.h"


class Day
{
public:


    //print tasks of day
    void print_tasks()
    {
        //counter for number of tasks
        int counter = 1;
        for(auto it = tasks.begin(); it != tasks.end(); ++it)
        {
            //print tasks with given format
            cout << "(" << counter << ") " << "\"" << (*it).get_title() << "\" ["
            << setfill('0') << setw(2) << (*it).get_start().get_hour() << ":" << setfill('0') << setw(2) << (*it).get_start().get_minute()
            << " - " << setfill('0') << setw(2) << (*it).get_finish().get_hour() << ":" << setfill('0') << setw(2) << (*it).get_finish().get_minute() << "]" << endl;
            counter++;
        }
    }


    vector<Task>& get_vector()
    {
        return tasks;
    }

    //add a task to vector
    void add(Task &task)
    {
        tasks.push_back(task);
    }


    //sort task base on finish time
    void tasks_sort()
    {
        //have an array of tasks form vector
       Task task_arr[tasks.size()];
       int counter = 0;
        for(auto it = tasks.begin(); it != tasks.end(); ++it)
        {
            task_arr[counter] = *it;
            counter++;
        }


        //bubble sort for tasks finish time
        for(int i = 0; i < tasks.size() - 1; i++)
        {
            for(int j = 0; j < tasks.size() - i - 1; j++)
            {
                if(task_arr[j].get_finish() > task_arr[j + 1].get_finish())
                {
                    Task temp = task_arr[j];
                    task_arr[j] = task_arr[j + 1];
                    task_arr[j + 1] = temp;
                }
            }
        }

        //clear vector
        tasks.clear();

        //the sorted array objects in vector
        for(int i = 0; i < counter; i++)
        {
            tasks.push_back(task_arr[i]);
        }
    }



    void free_up(int h, int m)
    {
        //have a new vector like the tasks vector
        vector <Task> temp;
        Time check;
        Time s;
        Time f;
        check.set_hour(h);
        check.set_minute(m);
       for(auto it = tasks.begin(); it != tasks.end(); ++it)
       {
            s = (*it).get_start();
            f = (*it).get_finish();
            //if time has conflict dont add to new vector
            if(!(s <= check && f > check))
            {
                temp.push_back(*it);
            }
       }

       //empty tasks vector to replace
       tasks.clear();
       for(auto it = temp.begin(); it != temp.end(); ++it)
       {
           tasks.push_back(*it);
       }
        cout << "done" << endl;
    }


private:
    vector<Task> tasks;


};

#endif // DAY_H_INCLUDED
