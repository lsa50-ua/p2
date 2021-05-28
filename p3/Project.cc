#include "Project.h"
#include <iostream>

using namespace std;


Project::Project(string name, string description){
    if (name != "")
    {
        this -> name = name;
    }
    else
    {
        throw ERR_EMPTY;
    }
    
    this -> description = description;
    id = 0; 
}

int Project::getId() const{
    return id;
}

string Project::getName() const{
    return name;
}

string Project::getDescription() const{
    return description;
}

int Project::getPosList(string name) const{
    int pos = -1;
    for (unsigned i = 0; i < lists.size() && pos == -1; i++)
    {
        if (lists[i].getName() == name )
        {
            pos = i;
        }
        
    }

    return pos;    
}

bool Project::setId(int id){
    bool idcorrecto = false;
    if (id >= 0)
    {
        this -> id = id;
        idcorrecto = true;
    }
    else
    {
        Util::error(ERR_ID);
    }
    
    return idcorrecto;
}

bool Project::setName(string name){
    bool namecorrecto = false;

    if (name != "")
    {
        this -> name = name;
        namecorrecto = true;
    }
    else
    {
        Util::error(ERR_EMPTY);
    }

    return namecorrecto;
}

void Project::setDescription(string description){
    this -> description = description;
}

void Project::edit(string name, string description){
    if (name == "")
    {
        do
        {
            cout << "Enter project name: ";
            getline(cin, name);
            if (name == "")
            {
                Util::error(ERR_EMPTY);
            }
            
        } while (name == "");
        
    }
    if (description == "")
    {
        cout << "Enter project description: ";
        getline(cin, description);
    }
    this->name = name;
    this->description = description;

}

void Project::addList(string name){

    if (name == "")
    {
        do
        {
            cout << "Enter list name: ";
            getline(cin, name);
            if (name == "")
            {
                Util::error(ERR_EMPTY);
            }
            
        } while (name == "");
    }
    
    if (getPosList(name) != -1)
    {
        Util::error(ERR_LIST_NAME);
    }
    else
    {
        List nueva(name);
        lists.push_back(nueva);
    }    
}

void Project::deleteList(string name){
    int posicion;

    if (name == "")
    {
        do
        {
            cout << "Enter list name: ";
            getline(cin, name);
            if (name == "")
            {
                Util::error(ERR_EMPTY);
            }
            
        } while (name == "");
    }
    
    posicion = getPosList(name);
    if (getPosList(name) == -1)
    {
        Util::error(ERR_LIST_NAME);
    }
    else
    {
        lists.erase(lists.begin() + posicion);
    }
}

void Project::addTaskToList(string name){
    string taskname, deadline;
    bool fechacomprobada, tiempocomprobado;
    int comprobacionName, time;

    if (name == "")
    {
        do
        {
            cout << "Enter list name: ";
            getline(cin, name);
            if (name == "")
            {
                Util::error(ERR_EMPTY);
            }
            
        } while (name == "");
    }
    comprobacionName = getPosList(name);
    if (comprobacionName == -1)
    {
        Util::error(ERR_LIST_NAME);
    }
    else
    {
        cout << "Enter task name: ";
        getline(cin, taskname);
        Task nueva(taskname);
        cout << "Enter deadline: ";
        getline(cin, deadline);
        fechacomprobada = nueva.setDeadline(deadline);
        if (fechacomprobada == true)
        {
            cout << "Enter expected time: ";
            cin >> time;
            cin.get();
            tiempocomprobado = nueva.setTime(time);
            if (tiempocomprobado == true)
            {
                lists[comprobacionName].addTask(nueva);
            } 
        } 
    }
}

void Project::deleteTaskFromList(string name){
    string taskname;
    int comprobacionLista;
  
    if (name == "")
    {
        do
        {
            cout << "Enter list name: ";
            getline(cin, name);
            if (name == "")
            {
                Util::error(ERR_EMPTY);
            }
            
        } while (name == "");
    }
    comprobacionLista = getPosList(name);
    if (comprobacionLista == -1)
    {
        Util::error(ERR_LIST_NAME);
    }
    else
    {
        cout << "Enter task name: ";
        getline(cin, taskname);
        lists[comprobacionLista].deleteTask(taskname);
    }
}

void Project::toggleTaskFromList(string name){
    string taskname;
    int comprobacionLista;
  
    if (name == "")
    {
        do
        {
            cout << "Enter list name: ";
            getline(cin, name);
            if (name == "")
            {
                Util::error(ERR_EMPTY);
            }
            
        } while (name == "");
    }
    comprobacionLista = getPosList(name);
    if (comprobacionLista == -1)
    {
        Util::error(ERR_LIST_NAME);
    }
    else
    {
        cout << "Enter task name: ";
        getline(cin, taskname);
        lists[comprobacionLista].toggleTask(taskname);
    }
}

void Project::menu(){
    char opcion;
    do
    {
        cout << "1- Edit project" << endl
            << "2- Add list" << endl
            << "3- Delete list" << endl 
            << "4- Add task" << endl
            << "5- Delete task" << endl
            << "6- Toggle task" << endl
            << "7- Report" << endl
            << "b- Back to main menu" << endl
            << "Option: ";
        cin >> opcion;
        cin.get();
        switch (opcion)
        {
            case '1': edit();
                    break;
            case '2': addList();
                    break;
            case '3': deleteList();
                    break;
            case '4': addTaskToList();
                    break;
            case '5': deleteTaskFromList();
                    break;
            case '6': toggleTaskFromList();
                    break;
            case '7': cout << *this << endl;
                    break;
            case 'b': break;
            default: Util::error(ERR_OPTION);
        }
    } while (opcion != 'b');
    
}

string Project::summary() const{
    string summarystring;
    int hechas = 0, totales = 0;
    for (unsigned i = 0; i < lists.size(); i++)
    {
        totales = totales + lists[i].getNumTasks();
        hechas = hechas + lists[i].getNumDone();
    }
    
    summarystring = "(" + to_string(id) + ") " + name + " [" + to_string(hechas) + "/" + to_string(totales) + "]";

    return summarystring;
}

ostream &operator<<(ostream &os, const Project &p){
    int posi, posj, vecesPendientes, vecesHechas, totalLeft, totalDone, conteo;
    vector <Task> tareas;
    Date deadline, hpriorityFecha;
    conteo = 0;
    totalLeft = 0;
    totalDone = 0;
    vecesHechas = 0;
    vecesPendientes = 0;
    posi = -1;
    posj = -1;

    os << "Name: " << p.name << endl;
    if (p.description != "")
    {
        os << "Description: "<< p.description << endl;
    }
    for (unsigned i = 0; i < p.lists.size(); i++)
    {
        os << p.lists[i];
        totalLeft = totalLeft + p.lists[i].getTimeTasks() - p.lists[i].getTimeDone();
        totalDone = totalDone + p.lists[i].getTimeDone();
        vecesHechas = vecesHechas + p.lists[i].getNumDone();
        vecesPendientes = vecesPendientes + p.lists[i].getNumTasks() - p.lists[i].getNumDone();
        tareas = p.lists[i].getTasks();
        for (unsigned j = 0; j < tareas.size(); j++)
        {   
            if (tareas[j].getIsDone() == false)
            {
                conteo ++;
                deadline = tareas[j].getDeadline();
                if (conteo == 1)
                {
                    posi = i;
                    posj = j;
                    hpriorityFecha.year = deadline.year;
                    hpriorityFecha.month = deadline.month;
                    hpriorityFecha.day = deadline.day;
                }
                else
                {
                    
                    if (deadline.year < hpriorityFecha.year)
                    {
                        posi = i;
                        posj = j;
                        hpriorityFecha.year = deadline.year;
                        hpriorityFecha.month = deadline.month;
                        hpriorityFecha.day = deadline.day;
                    }
                    else
                    {
                        if (deadline.year == hpriorityFecha.year)
                        {
                            if (deadline.month < hpriorityFecha.month)
                            {
                                posi = i;
                                posj = j;
                                hpriorityFecha.year = deadline.year;
                                hpriorityFecha.month = deadline.month;
                                hpriorityFecha.day = deadline.day;
                            }
                            else
                            {
                                if (deadline.month == hpriorityFecha.month)
                                {
                                    if (deadline.day < hpriorityFecha.day)
                                    {
                                        posi = i;
                                        posj = j;
                                        hpriorityFecha.year = deadline.year;
                                        hpriorityFecha.month = deadline.month;
                                        hpriorityFecha.day = deadline.day;                                        
                                    } 
                                }
                            } 
                        } 
                    }
                }    
            } 
        }    
    }
    
    
    os << "Total left: " << vecesPendientes << " (" << totalLeft << " minutes)" << endl;
    os << "Total done: " << vecesHechas << " (" << totalDone << " minutes)" << endl;
    if (conteo > 0)
    {
        tareas = p.lists[posi].getTasks();
        os << "Highest priority: " << tareas[posj].getName();
        os << " (" << hpriorityFecha.year << "-" << hpriorityFecha.month;
        os << "-" << hpriorityFecha.day << ")";
    }
    return os;
}
        