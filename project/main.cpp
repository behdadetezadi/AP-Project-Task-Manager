#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;


#include "Yearbook.h"
#include "Month.h"
#include "Day.h"
#include "Employee.h"
#include "Time.h"
#include "task.h"

int main()
{
    //get instance of type yearbook
    Yearbook year2021;

    //make vector of type employee to keep employee data
    vector<Employee> employees;

    //uncomment for alternate file read
    /*/
        fstream rf("task.dat",ios::in | ios::out | ios::binary);
        if(!rf){cout << "cannot open"; return 1;}
        rf.read(reinterpret_cast<char*> (&year2021), sizeof(Yearbook);
        rf.close();
    /*/

    //take command
    while(true)
    {
        // read line for command
        string input;
        getline(cin, input, '\n');

        //break out of loop with command exit
        if(input == "exit")
            break;

        //adding task
        if(input == "add task")
        {
            string title;
            string starting_time;
            string end_time;

            //get title
            cout << "title is ";
            cin >> title;

            //get start date and time
            cout << "starts at ";
            fflush (stdin); //empty buffer
            getline(cin, starting_time, '\n');

            //get finish date and time
            cout << "ends at ";
            fflush (stdin); //empty buffer
            getline(cin, end_time, '\n');

            //tasks start and end in the same day

            //get task moth
            string month = "";
            month += starting_time[3];
            month += starting_time[4];

            //get task day
            string day = "";
            day += starting_time[0];
            day += starting_time[1];

            //read the start and finish hour from input
            string start = "";
            string finish = "";
            for(int i = 6; i <= 10; i++)
            {
                start += starting_time[i];
                finish += end_time[i];
            }

            //make a task with given info
            Task input_task(title, day, month, start, finish);

            // add the task to yearbook
            year2021.add_task(input_task);
        }

        //adding a new employee
        else if(input == "add employee")
        {
            //get employee name
            string name;
            cout << "name is ";
            fflush (stdin); //empty buffer
            getline(cin, name, '\n');

            //get employee id
            string id;
            cout << "ssid is ";
            fflush (stdin);
            getline(cin, id, '\n');
            //cast given ssid to type long
            long code = std::stol(id);

            //get start hour
            string work_start = "";
            cout << "starts at ";
            fflush (stdin);//empty buffer
            getline(cin, work_start, '\n');

            //get finishing hour
            string work_end = "";
            cout << "ends at ";
            fflush (stdin);//empty buffer
            getline(cin, work_end, '\n');

            //read the input string for finish and start time and make a Time(type)
            Time s;
            string s_hour = ""; s_hour += work_start[0]; s_hour += work_start[1]; stringstream start_work_hour(s_hour); int x; start_work_hour >> x; s.set_hour(x);
            string s_minute = ""; s_minute += work_start[3]; s_minute += work_start[4]; stringstream start_work_minute(s_minute); x = 0; start_work_minute >> x; s.set_minute(x);
            Time f; string f_hour = ""; f_hour += work_end[0]; f_hour += work_end[1]; stringstream end_work_hour(f_hour); x = 0; end_work_hour >> x; f.set_hour(x);
            string f_minute = ""; f_minute += work_end[3]; f_minute += work_end[4]; stringstream end_work_minute(f_minute); x = 0; end_work_minute >> x; f.set_minute(x);

            //make an employee with given info
            Employee to_add(name, code, s, f);

            //add the new employee to the employee vector
            employees.push_back(to_add);
            cout << "done" << endl;

        }

        //show systems current time
        else if(input == "now")
        {
            year2021.now();
        }

        // free a given time
        else if(input[0] == 'f' && input[1] == 'r' && input[2] == 'e' && input[3] == 'e')
        {
            //read the day to free and convert to int
            string day_free = ""; day_free += input[5]; day_free += input[6]; stringstream ruz_free(day_free); int x = 0; ruz_free >> x;
            //read the month and convert to int
            string month_free = ""; month_free += input[8]; month_free += input[9]; stringstream mah_free(month_free); int y = 0; mah_free >> y;
            //read the hour and convert to int
            string hour_free = ""; hour_free += input[11]; hour_free += input[12]; stringstream saat_free(hour_free); int z = 0; saat_free >> z;
            //read the minute and convert to int
            string minute_free = ""; minute_free += input[14]; minute_free += input[15]; stringstream daghighe_free(minute_free); int w = 0; daghighe_free >> w;

            //use the free function in class yearbook with given info
            year2021.free(x, y, z, w);
        }

        //assign a task to an employee
        else if(input == "assign task")
        {
            //get the ssid of employee
            cout << "ssid is ";
            string code;
            fflush (stdin); // empty buffer
            getline(cin, code, '\n');
            long id = 0; stringstream ssid_code(code); ssid_code >> id; // convert to long

            // get task to assign
            cout << "task is ";
            string task_name;
            fflush (stdin); // empty buffer
            getline(cin, task_name, '\n');

            // uncomment for checking if the task exists
            //if(year2021.task_available(task_name))
            //{
                //find employee from vector
                for(auto it = employees.begin(); it != employees.end(); ++it)
                {
                    if((*it).get_ssid() == id)
                    {
                        //assign the task
                        (*it).add_job(year2021.find_task(task_name));
                        break;
                    }

                }
           // }

            cout << "done" << endl;
        }

        // print todays tasks
        else if(input == "today")
        {
            year2021.today();
        }

        //print this months tasks
        else if(input == "month")
        {
            year2021.month();
        }


        else if(input == "schedule")
        {
            //get date and convert month and day to type int
            string date;
            cout << "date is ";
            fflush (stdin);
            getline(cin, date, '\n');
            string temp = "";
            int d; temp += date[0]; temp += date[1]; stringstream day_free(temp); day_free >> d;
            int m; temp = ""; temp += date[3]; temp += date[4]; stringstream month_free(temp); month_free >> m;

            //get employee ssid
            long emplo_id;
            cout << "ssid is ";
            fflush (stdin);
            cin >> emplo_id;



            //find employee from vector
            for(auto it = employees.begin(); it != employees.end(); ++it)
            {
                if((*it).get_ssid() == emplo_id)
                {
                    //free employees day
                    (*it).clear_day(m, d);

                    //assign the most possible tasks with no overlap
                    year2021.schedule(*it, d, m);
                    break;
                }

            }
        }


        //find time command
        else
        {

            //check if input starts with find time
            string input2 = "";
            for(int i = 0; i < 9; i++)
                input2 += input[i];

            if(input2 == "find time")
            {
                //get hour and minute and convert to int
                string find_minute = ""; find_minute += input[13]; find_minute += input[14]; int mm = 0; stringstream minute_tofind(find_minute); minute_tofind >> mm;
                string find_hour = ""; find_hour += input[10]; find_hour += input[11]; int hh = 0; stringstream hour_tofind(find_hour); hour_tofind >> hh;

                //use find time function with given info
                year2021.find_time(hh, mm);
            }
        }
    }

    //uncomment for alternate file write
    /*/
    ofstream wf("task.dat", ios::out | ios:: binary);
    if(!wf){cout << "cannot open file" << endl; return 1;}
    wf.write(reinterpret_cast<char*> (&year2021), sizeof(Yearbook);
    wf.close();
    /*/

    return 0;
}
