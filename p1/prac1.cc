// DNI 48804855M SIMÓN ALBARRÁN, LUIS 



#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}
void ComprobarCadenaVacia(string name){
  
  if (name == "")
  {
    error(ERR_EMPTY);
  }

}

void editProject(Project &toDoList){
  
  do
  {
    cout << "Enter project name: ";
    getline(cin, toDoList.name);
    ComprobarCadenaVacia(toDoList.name);   
  } while (toDoList.name == "");
  
  cout << "Enter project description: ";
  getline(cin, toDoList.description);
  

  
}
int ComprobarNombresListas(Project toDoList, string nombre){
  int pos, i;
  pos = -1;
  for (i = 0; i < (int) toDoList.lists.size() && pos == -1; i++)
  {
    if (toDoList.lists[i].name == nombre)
    {
      pos = i;
    }
    
  }
  return pos;
  
}

void addList(Project &toDoList){
  List nueva;
  int comprobacion;
  
  do
  {  
    cout << "Enter list name: ";
    getline(cin, nueva.name);
    ComprobarCadenaVacia(nueva.name);
  } while (nueva.name == "");
  
  comprobacion = ComprobarNombresListas(toDoList, nueva.name);
  if (comprobacion != -1)
  {
    error(ERR_LIST_NAME);
  }
  else
  {
    toDoList.lists.push_back(nueva);
  }
      
}

void deleteList(Project &toDoList){
  string listname;
  int comprobacion;
  do
  {  
    cout << "Enter list name: ";
    getline(cin, listname);
    ComprobarCadenaVacia(listname);
  } while (listname == "");
  
  comprobacion = ComprobarNombresListas(toDoList, listname);
  if (comprobacion == -1)
  {
    error(ERR_LIST_NAME);
  }
  else
  {
    toDoList.lists.erase(toDoList.lists.begin() + comprobacion);
  }
  
}

bool ComprobarFecha(Date deadline){
  int dias_mes[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};

  if (deadline.year < 2000 || deadline.year > 2100)
  {
    return false;
  }

  if((deadline.year % 4 == 0 && deadline.year % 100 != 0) || deadline.year % 400 == 0){
    dias_mes[1]++;
  }

  if (deadline.month < 1 || deadline.month > 12)
  {
    return false;
  }

  deadline.month --;
  if (deadline.day < 1 || deadline.day > dias_mes[deadline.month])
  {
    return false;
  }

  return true;
    
}

void addTask(Project &toDoList){
  string listname;
  Task newtask;
  int comprobacionName;
  char simbolo;
  do
  {  
    cout << "Enter list name: ";
    getline(cin, listname);
    ComprobarCadenaVacia(listname);
  } while (listname == "");
  
  comprobacionName = ComprobarNombresListas(toDoList, listname);
  if (comprobacionName == -1)
  {
    error(ERR_LIST_NAME);
  }
  else
  {
    cout << "Enter task name: ";
    getline(cin, newtask.name);
    cout << "Enter deadline: ";
    cin >> newtask.deadline.day >> simbolo >> newtask.deadline.month >> simbolo >> newtask.deadline.year;
    cin.get();

    if (ComprobarFecha(newtask.deadline) == false)
    {
      error(ERR_DATE);
    }
    else
    {
      cout << "Enter expected time: ";
      cin >> newtask.time;
      cin.get();
      if (newtask.time < 1 || newtask.time > 180)
      {
        error(ERR_TIME);
      }
      else
      {
        newtask.isDone = false;
        toDoList.lists[comprobacionName].tasks.push_back(newtask);
      }
      
    }
    
  }
}
void ComprobarYEliminarTasks(Project &toDoList, string nombre, int marcadorLista ){
  int i, pos, veces;
  bool repetido;
  repetido = true;
  veces = 0;

  while (repetido == true)
  {
    repetido = false;
    pos = -1;
    for (i = 0; i < (int) toDoList.lists[marcadorLista].tasks.size() && pos == -1; i++)
    {
      if (nombre == toDoList.lists[marcadorLista].tasks[i].name)
      {
        pos = i;
        repetido = true;
        veces ++;
        toDoList.lists[marcadorLista].tasks.erase(toDoList.lists[marcadorLista].tasks.begin() + pos);
      }
    }
  }
  if (veces == 0)
  {
    error(ERR_TASK_NAME);
  }
  
}
void deleteTask(Project &toDoList){
  string listname, taskname;
  int comprobacionLista;
  do
  {  
    cout << "Enter list name: ";
    getline(cin, listname);
    ComprobarCadenaVacia(listname);
  } while (listname == "");
  
  comprobacionLista = ComprobarNombresListas(toDoList, listname);
  if (comprobacionLista == -1)
  {
    error(ERR_LIST_NAME);
  }
  else{
    cout << "Enter task name: ";
    getline(cin, taskname);
    ComprobarYEliminarTasks(toDoList, taskname, comprobacionLista);
  }
}

void toggleTask(Project &toDoList){
}

void report(const Project &toDoList){
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}

// toDoList.lists.erase(toDoList.lists.begin() + pos)