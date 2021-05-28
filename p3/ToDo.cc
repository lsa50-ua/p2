#include "ToDo.h"

int ToDo::nextId = 1;

ToDo::ToDo(string name){
    if (name == "")
    {
        throw ERR_EMPTY;
    }
    this->name = name;
}

string ToDo::getName() const{
    return name;
}

int ToDo::getPosProject(string name) const{
    int pos = -1;
    for (unsigned i = 0; i < projects.size() && pos == -1; i++)
    {
        if (projects[i]->getName() == name)
        {
            pos = i;
        }
        
    }
    return pos;
}

int ToDo::getPosProject(int id) const{
    int pos = -1;
    for (unsigned i = 0; i < projects.size() && pos == -1; i++)
    {
        if (projects[i]->getId() == id)
        {
            pos = i;
        }
        
    }
    return pos;
}

bool ToDo::setName(string name){
    bool correct = false;
    if (name == "")
    {
        Util::error(ERR_EMPTY);
    }
    else
    {
        correct = true;
        this->name = name;
    }
    
    return correct;
}

void ToDo::addProject(Project *project){
    int pos;
    pos = getPosProject(project->getName());
    if (pos != -1)
    {
        throw ERR_PROJECT_NAME;
    }
    else
    {
        project->setId(nextId);
        nextId ++;
        projects.push_back(project);
    }
}

void ToDo::deleteProject(int id = 0){

    if (id == 0)
    {
        cout << "Enter project id: ";
        cin >> id;
    }
    if (getPosProject(id) == -1)
    {
        Util::error(ERR_ID);
    }
    else
    {
        projects.erase(projects.begin() + getPosProject(id));
    }
}

void ToDo::setProjectDescription(string name, string description){

}

void ToDo::projectMenu(int id = 0){

}