// Luis Simón Albarrán
// DNI: 48804855



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

void editProject(Project &toDoList){
  
  do
  {
    cout << "Enter project name: ";
    getline(cin,toDoList.name);
    if (toDoList.name == "")
    {
      error(ERR_EMPTY);
    }
    
  } while (toDoList.name == "");
  
  cout << "Enter project description: ";
  getline(cin, toDoList.description);
  cin.get();

  
}
int ComprobarNombresListas(Project toDoList, List nueva){
  int pos, i;
  pos = -1;
  for (i = 0; i < toDoList.lists.size(); i++)
  {
    if (toDoList.lists[i].name == nueva.name)
    {
      pos = i;
    }
    
  }
  return pos;
  
}

void addList(Project &toDoList){
  List nueva;
  int comprobacion;
  comprobacion = ComprobarNombresListas(toDoList, nueva);
  do
  {
    cout << "Enter list name: ";
    getline(cin, nueva.name);
    if (nueva.name == "")
    {
      error(ERR_EMPTY);
    }
    else
    {
      if (comprobacion != -1)
      {
        error(ERR_LIST_NAME);
      }
      else
      {
        toDoList.lists.push_back(nueva);
      }
      
    }
    
  } while (nueva.name == "" || comprobacion != -1);
  
  
  
}

void deleteList(Project &toDoList){
}

void addTask(Project &toDoList){
}

void deleteTask(Project &toDoList){
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
