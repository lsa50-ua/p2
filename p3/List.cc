#include "Util.h"
#include "List.h"

List::List(string name){
    if (name != "")
    {
        this -> name = name;
    }
    else
    {
        throw ERR_EMPTY;
    }
}

string List::getName() const{
    return name;
}

vector<Task> List::getTasks() const{
    return tasks;
}

unsigned List::getNumTasks() const{
    return tasks.size();
}

unsigned List::getNumDone() const{
    unsigned hechas = 0;
    for (unsigned i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getIsDone() == true)
        {
            hechas ++;
        }
    }
    return hechas;
}

int List::getTimeTasks() const{
    int tiempototal = 0;
    for (unsigned i = 0; i < tasks.size(); i++)
    {
        tiempototal = tiempototal + tasks[i].getTime();
    }
    
    return tiempototal;
}
int List::getTimeDone() const{
    int tiempototal = 0;
    for (unsigned i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getIsDone()==true)
        {
            tiempototal = tiempototal + tasks[i].getTime();
        }  
    }
    return tiempototal;
}

int List::getPosTask(string name) const{
    int pos = -1;
    for (unsigned i = 0; i < tasks.size() && pos == -1; i++)
    {
        if (tasks[i].getName() == name)
        {
            pos = i;
        }  
    }
    return pos;
}

bool List::setName(string name){
    bool cambiado = false;
    if (name == "")
    {
        Util::error(ERR_EMPTY);
    }
    else
    {
        this->name = name;
        cambiado = true;
    }

    return cambiado;
}

void List::addTask(const Task &task){
    tasks.push_back(task);
}

bool List::deleteTask(string name){
    bool deleted = false;
    for (unsigned i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getName() == name)
        {
            deleted = true;
            tasks.erase(tasks.begin() + i);
            i--;
        }  
    }
    if (deleted == false)
    {
        Util::error(ERR_TASK_NAME);
    }

    return deleted;
}

bool List::toggleTask(string name){
    bool encontrado = false;
    for (unsigned i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getName() == name)
        {
            encontrado = true;
            tasks[i].toggle();
        }  
    }
    if (encontrado == false)
    {
        Util::error(ERR_TASK_NAME);
    }

    return encontrado;
}

ostream &operator<<(ostream &os, const List &l){
    os << l.name << endl;
    for (unsigned i = 0; i < l.tasks.size(); i++)
    {
        if (l.tasks[i].getIsDone() == false)
        {
            os << l.tasks[i] << endl;
        }   
    }
    for (unsigned i = 0; i < l.tasks.size(); i++)
    {
        if (l.tasks[i].getIsDone() == true)
        {
            os << l.tasks[i] << endl;
        }  
    }  

    return os;
}