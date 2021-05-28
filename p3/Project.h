#ifndef _PROJECT_H_
#define _PROJECT_H_
#include <iostream>
#include "Util.h"
#include "Task.h"
#include "List.h"
#include <vector>
using namespace std;

class Project{
    friend ostream &operator<<(ostream &os, const Project &p);
    protected:
        int id;
        string name;
        string description;
        int getPosList(string name) const;
        vector<List> lists;
        bool esMenor(const Date &date1, const Date &date2) const;
    public:
        Project(string name, string description = "");
        int getId() const;
        string getName() const;
        string getDescription() const;
        bool setId(int id);
        bool setName(string name);
        void setDescription(string description);
        void edit(string name = "", string description = "");
        void addList(string name = "");
        void deleteList(string name = "");
        void addTaskToList(string name = "");
        void deleteTaskFromList(string name = "");
        void toggleTaskFromList(string name = "");
        void menu();
        string summary() const;
        
};

#endif
