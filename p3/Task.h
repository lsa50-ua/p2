#ifndef _TASK_H_
#define _TASK_H_
#include<iostream>
using namespace std;

struct Date{
    int day, month, year;
};

class Task{
    friend ostream &operator<<(ostream &os, const Task &t);
    protected:
        string name;
        Date deadline;
        bool isDone;
        int time;
        bool CorrectDate(Date date);
    public:
        Task(string name);
        string getName() const;
        Date getDeadline() const;
        bool getIsDone() const;
        int getTime() const;
        void setName(string name);
        bool setDeadline(string deadline);
        bool setTime(int time);
        void toggle();
        
};

#endif