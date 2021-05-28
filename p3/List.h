#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>
#include <vector>
#include "Task.h"
using namespace std;

class List{
    friend ostream &operator<<(ostream &os, const List &l);
    protected:
        string name;
        vector<Task> tasks;
    public:
        List(string name);
        string getName() const;
        vector<Task> getTasks() const;
        unsigned getNumTasks() const;
        unsigned getNumDone() const;
        int getTimeTasks() const;
        int getTimeDone() const;
        int getPosTask(string name) const;
        bool setName(string name);
        void addTask(const Task &task);
        bool deleteTask(string name);
        bool toggleTask(string name);
};

#endif