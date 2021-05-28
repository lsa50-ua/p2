#include "Task.h"
#include "Util.h"
#include <sstream>

Task::Task(string name){
    this->name = name;
    deadline.day = 1;
    deadline.month = 1;
    deadline.year = 2000;
    isDone = false;
}

string Task::getName() const{
    return name;
}

Date Task::getDeadline() const{
    return deadline;
}

bool Task::getIsDone() const{
    return isDone;
}

int Task::getTime() const{
    return time;
}

void Task::setName(string name){
    this->name = name;
}

bool Task::setDeadline(string deadline){
    bool isSet = false;
    Date fechaAComprobar;
    char separador;
    stringstream bufferear(deadline);
    bufferear >> fechaAComprobar.day >> separador >> fechaAComprobar.month >> separador >> fechaAComprobar.year; 
    if (CorrectDate(fechaAComprobar) == true)
    {
        this->deadline = fechaAComprobar;
        isSet = true;
    }
    else
    {
        Util::error(ERR_DATE);
    }

    return isSet;
}

bool Task::setTime(int time){
    bool isSet = false;
    if (time < 1 || time > 180)
    {
        Util::error(ERR_TIME);
    }
    else
    {
        isSet = true;
        this -> time = time;
    }
    return isSet;
}
void Task::toggle(){
    if (isDone == false)
    {
        isDone = true;
    }
    else
    {
        isDone = false;
    }
}

bool Task::CorrectDate(Date date){
    bool verificador;
    verificador = true;
    int dias_mes[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};

    if (date.year < 2000 || date.year > 2100)
    {
        verificador =  false;
    }
    if(verificador == true && ((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0)){
        dias_mes[1]++;
    }
    if (verificador == true && (date.month < 1 || date.month > 12))
    {
        verificador = false;
    }
    else{
        if (verificador == true)
        {
            date.month --;
            if (date.day < 1 || date.day > dias_mes[date.month])
            {
                verificador = false;
            }   
        }
    }
    return verificador;
}

ostream &operator<<(ostream &os, const Task &t){
    char marcar;
    if (t.isDone == true)
    {
        marcar = 'X';
    }
    else
    {
        marcar = ' ';
    }
    os << "[" << marcar << "] " << "(" << t.time << ") "  << t.deadline.year << "-" << t.deadline.month << "-" << t.deadline.day << " : " << t.name;
    
    return os;
}

