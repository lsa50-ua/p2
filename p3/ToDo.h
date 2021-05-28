#ifndef _TODO_H_
#define _TODO_H_
#include <iostream>
#include "Util.h"
#include "Project.h"
#include "List.h"
#include "Task.h"
using namespace std;

class ToDo{
    friend ostream &operator<<(ostream &os, const ToDo &t);
    protected:
        static int nextId;
        string name;
        vector<Project *> projects;
        int getPosProject(string name) const;
        int getPosProject(int id) const;
    public:
        ToDo(string name);
        string getName() const;
        bool setName(string name);
        void addProject(Project *project);
        void deleteProject(int id = 0);
        void setProjectDescription(string name, string description);
        void projectMenu(int id = 0);
};

#endif