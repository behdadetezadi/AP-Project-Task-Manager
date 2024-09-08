#ifndef YEARBOOK_H_INCLUDED
#define YEARBOOK_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>


#include "Day.h"
#include "Month.h"
#include "Employee.h"

using namespace std;

class Yearbook
{
public:
    //constructor
    Yearbook()
    {
        //jan-mar-may-july
        for(int i = 1; i < 8; i += 2)
        {
            months[i].set_numberofdays(31);
        }
        //feb
        months[2].set_numberofdays(28);
        //aug
        months[8].set_numberofdays(31);
        //april
        months[4].set_numberofdays(30);
        //june
        months[6].set_numberofdays(30);
        //aug
        months[8].set_numberofdays(31);
        //sep
        months[9].set_numberofdays(30);
        //oct
        months[10].set_numberofdays(31);
        //nov
        months[11].set_numberofdays(30);
        //dec
        months[12].set_numberofdays(31);
        //read file and put
        read_file();
    }

    //destructor writing the tasks
    ~Yearbook()
    {
        write_file();
    }


    bool read_file()
    {

        ifstream rf("task.dat", ios::out | ios::binary);
        //check
        if(!rf){cout << "no file or error reading source file" << endl; return false;}
        Task to_write;
        while (true)
        {
            to_write.read(rf);
            if(rf.eof()){break;}
            months[to_write.get_month()][to_write.get_day()].add(to_write);
        }
        cout << "file read successfully" << endl;
        rf.close();
        return true;
    }



    bool write_file()
    {
        remove("task.dat");
        ofstream wf("task.dat", ios::out | ios:: binary);
        if(!wf){cout << "cannot open file to write" << endl; return false;}
        for(int i = 1; i <= 12; i++)
        {
            for(int j = 1; j < months[i].get_numberofdays(); j++)
            {
                if(!(months[i][j].get_vector().empty()))
                {
                    for(auto it = months[i][j].get_vector().begin(); it != months[i][j].get_vector().end(); ++it)
                    {
                        (*it).write(wf);
                    }
                }
            }
        }
        cout << "file writing successful" << endl;
        return true;
    }


    void add_task(Task &to_add)
    {
        months[to_add.get_month()][to_add.get_day()].add(to_add);
        cout << "done" << endl;
    }

    void free(int day, int month, int hour,int minute)
    {
        months[month][day].free_up(hour, minute);
    }


    void schedule(Employee& mr, int ruz, int mah)
    {
        //sort task based on finish time
        months[mah][ruz].tasks_sort();
        Task check[months[mah][ruz].get_vector().size()];
        int counter = 0;
        //add tasks to temp array
        for(auto it = months[mah][ruz].get_vector().begin(); it != months[mah][ruz].get_vector().end(); ++it)
        {
            check[counter] = *it;
            counter++;
        }
        //add the first task
        mr.add_job(check[0]);
        int temp = 0;
        //add task if doesnt overlaps
        for(int i = 1; i < counter; i++)
        {
            if(check[temp].get_finish() <= check[i].get_start())
            {
                mr.add_job(check[i]);
                temp = i;
            }
        }
        cout << "done" << endl;


    }
// dd-mm
    bool find_time(int h, int minute ,int aux_arg = 0)
    {
        //get current month and day and convert to int
        int m = 0; stringstream this_month(current_month()); this_month >> m;
        time_t now = time(0); char *date = ctime(& now); string day = ""; day += date[8]; day += date[9]; stringstream ruz(day); int d = 0; ruz >> d;
        int days_counter = months[m].get_numberofdays();

        //get current hour and minute and convert to int
        int today_hour; string t_hour = ""; t_hour += date[11]; t_hour += date[12]; stringstream hour_tostart(t_hour); hour_tostart >> today_hour;
        int today_minute; string t_minute = ""; t_minute += date[14]; t_minute += date[15]; stringstream minute_tostart(t_minute); minute_tostart >> today_minute;


        int start_time_minute ;
        int start_time_hour ;
        int finish_minute ;
        int finish_hour;
        bool check;
        int aux_h;

        Time start;
        Time finish;


        //search today
        for(int i = today_hour; i <= 23 - h; i++)
        {
            for(int j = 0; j <= 59; j++)
            {
                check = false;
                start_time_minute = j;
                start_time_hour = i;

                finish_minute =  start_time_minute + minute;
                finish_hour =  start_time_hour + h;

                //correct time format
                if (finish_minute > 59)
                {
                        finish_minute -= 60;
                        finish_hour += 1;
                }

                if (finish_hour > 23)
                {
                    break;
                }

                //check it isnt past
                if(i == today_hour && j < today_minute)
                {
                }
                else
                {
                    start.set_minute(start_time_minute); start.set_hour(start_time_hour);
                    finish.set_minute(finish_minute); finish.set_hour(finish_hour);
                    //check time has conflict with tasks
                    for(auto it = months[m][d].get_vector().begin(); it != months[m][d].get_vector().end(); ++it)
                    {
                        if(!(finish <= (*it).get_start() || start >= (*it).get_finish()))
                        {
                            check = true;
                            break;
                        }

                    }
                    //if time doesnt have conflict
                    if ((!check) && (aux_arg == 0))
                    {
                        cout << setfill('0') << setw(2) << d << "-"
                        << setfill('0') << setw(2) << m << " "
                        << "[" << setfill('0') << setw(2) << start_time_hour
                        << ':' << setfill('0') << setw(2) << start_time_minute
                        << " - " << setfill('0') << setw(2) << finish_hour
                        << ':' << setfill('0') << setw(2) << finish_minute
                        << "]" << endl;
                        return true;
                    }
                    //if given length wasnt found and shorter time doesnt have conflict
                    if((!check) && (aux_arg != 0))
                    {

                        if(aux_arg < 60)
                        {
                            cout << setfill('0') << setw(2) << d << "-"
                            << setfill('0') << setw(2) << m << " "
                            << "[" << setfill('0') << setw(2) << start_time_hour
                            << ':' << setfill('0') << setw(2) << start_time_minute
                            << " - " << setfill('0') << setw(2) << finish_hour
                            << ':' << setfill('0') << setw(2) << finish_minute
                            << "] + " << aux_arg << "minutes" << endl;
                        }
                        //correct time fomat
                        else
                        {
                            aux_h = 0;
                            int aux_arg2 = aux_arg;
                            while(aux_arg >= 60)
                            {
                                aux_arg2 -= 60;
                                aux_h++;
                            }
                            cout << setfill('0') << setw(2) << d << "-"
                            << setfill('0') << setw(2) << m << " "
                            << "[" << setfill('0') << setw(2) << start_time_hour
                            << ':' << setfill('0') << setw(2) << start_time_minute
                            << " - " << setfill('0') << setw(2) << finish_hour
                            << ':' << setfill('0') << setw(2) << finish_minute
                            << "] + " << aux_h << "hours and " << aux_arg2 << "minutes" << endl;
                        }
                    }
                }

            }
        }



        //search upcoming days of month
        for(int i = d + 1; i <= days_counter; i++)
        {
            for(int j = 0; j <= 23 - h; j++)
            {
                for(int k = 0; k <= 59; k++)
                {
                    check = false;
                    start_time_minute = k;
                    start_time_hour = j;

                    finish_minute =  start_time_minute + minute;
                    finish_hour =  start_time_hour + h;

                    if (finish_minute > 59)
                    {
                        finish_minute -= 60;
                        finish_hour += 1;
                    }

                    if (finish_hour > 23)
                    {
                        break;
                    }

                    else
                    {
                        start.set_minute(start_time_minute); start.set_hour(start_time_hour);
                        finish.set_minute(finish_minute); finish.set_hour(finish_hour);

                        for(auto it = months[m][i].get_vector().begin(); it != months[m][i].get_vector().end(); ++it)
                        {
                            if(!(finish <= (*it).get_start() || start >= (*it).get_finish()))
                            {
                                check = true;
                                break;
                            }

                        }

                        //if time doesnt have conflict
                        if ((!check) && (aux_arg == 0))
                        {
                            cout << setfill('0') << setw(2) << d << "-"
                            << setfill('0') << setw(2) << m << " "
                            << "[" << setfill('0') << setw(2) << start_time_hour
                            << ':' << setfill('0') << setw(2) << start_time_minute
                            << " - " << setfill('0') << setw(2) << finish_hour
                            << ':' << setfill('0') << setw(2) << finish_minute
                            << "]" << endl;
                            return true;
                        }
                        //if given length wasnt found and shorter time doesnt have conflict
                        if((!check) && (aux_arg != 0))
                        {

                            if(aux_arg < 60)
                            {
                                cout << setfill('0') << setw(2) << d << "-"
                                << setfill('0') << setw(2) << m << " "
                                << "[" << setfill('0') << setw(2) << start_time_hour
                                << ':' << setfill('0') << setw(2) << start_time_minute
                                << " - " << setfill('0') << setw(2) << finish_hour
                                << ':' << setfill('0') << setw(2) << finish_minute
                                << "] + " << aux_arg << "minute(s)" << endl;
                                return true;
                            }
                            //correct time fomat
                            else
                            {
                                aux_h = 0;
                                int aux_arg2 = aux_arg;
                                while(aux_arg >= 60)
                                {
                                    aux_arg2 -= 60;
                                    aux_h++;
                                }
                                cout << setfill('0') << setw(2) << d << "-"
                                << setfill('0') << setw(2) << m << " "
                                << "[" << setfill('0') << setw(2) << start_time_hour
                                << ':' << setfill('0') << setw(2) << start_time_minute
                                << " - " << setfill('0') << setw(2) << finish_hour
                                << ':' << setfill('0') << setw(2) << finish_minute
                                << "] + " << aux_h << "hour(s) and " << aux_arg2 << "minute(s)" << endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }

        //recursive func if given time wasnt found
        if(minute - 1 < 0)
        {
            return find_time(h - 1, 59, aux_arg + 1);
        }
        if(minute - 1 >= 0)
        {
            return find_time(h, minute - 1, aux_arg + 1);
        }
    }



    //look for a task based on title
    Task& find_task(string name)
    {
        int d;

        for(int i = 1; i < 13; i++)
        {
            d = months[i].get_numberofdays();
            for(int j = 1; j <= d; j++)
            {
                for(auto it = months[i][j].get_vector().begin(); it != months[i][j].get_vector().end(); ++it)
                {
                    if((*it).get_title() == name)
                        return (*it);
                }
            }
        }
        cout << "cant find task!" << endl;
    }

    bool task_available(string name)
    {
        int d;

        for(int i = 1; i < 13; i++)
        {
            d = months[i].get_numberofdays();
            for(int j = 1; j <= d; j++)
            {
                for(auto it = months[i][j].get_vector().begin(); it != months[i][j].get_vector().end(); ++it)
                {
                    if((*it).get_title() == name)
                        return true;
                }
            }
            return false;
        }
    }


    void today()
    {
        time_t now = time(0);
        char *date = ctime(& now);
        string day = "";
        day += date[8];
        day += date[9];
        stringstream ruz(day);
        int x = 0;
        ruz >> x;
        string m = current_month();
        stringstream this_month(m);
        int month = 0;
        this_month >> month;
        months[month][x].print_tasks();
    }
    void month()
    {
        string m = current_month();
        stringstream this_month(m);
        int the_month = 0;
        this_month >> the_month;

        int counter;

        int n = months[the_month].get_numberofdays();
        for(int i = 1; i <= n; i++)
        {
            counter = 1;
            for(auto it = months[the_month][i].get_vector().begin(); it != months[the_month][i].get_vector().end(); ++it)
                {
                    cout << "(" << counter << ") " <<
                        setfill('0') << setw(2) << (*it).get_day() << "-"
                        << setfill('0') << setw(2) << (*it).get_month() << " "
                        << "[" << setfill('0') << setw(2) << (*it).get_start().get_hour()
                        << ':' << setfill('0') << setw(2) << (*it).get_start().get_minute()
                        << " - " << setfill('0') << setw(2) << (*it).get_finish().get_hour()
                        << ':' << setfill('0') << setw(2) << (*it).get_finish().get_minute()
                        << "]" << endl;
                    counter++;
                }
        }

    }



    void now()
    {
        time_t now = time(0);
        char *date = ctime(& now);
        string day = "";
        string time = "";
        day += date[8];
        day += date[9];
        for(int i = 11; i < 16; i++)
            time+=date[i];
        cout << "   " << day << "-" << current_month() << " " << time << endl;
    }


    //give current months number based on initials
    string current_month()
    {
        time_t now = time(0);
        char *date = ctime(& now);
        string month;
        string m = "";
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
        return month;
    }
private:
    Month months[13];
};

#endif // YEARBOOK_H_INCLUDED
