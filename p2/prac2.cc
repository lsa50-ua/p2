// DNI 48804855M SIMÓN ALBARRÁN, LUIS 

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXEXPECTEDTIME = 180;
const int MINEXPECTEDTIME = 1;
const int DICIEMBRE = 12;
const int ENERO = 1;
const int MAXYEAR = 2100;
const int MINYEAR = 2000;
const int BORRAR = 1;
const int TOGGLE = 2;

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

struct ToDo{
int nextId;
string name;
vector<Project> projects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
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

void IntroducirNombreLista(string &nombre){
  do
  {  
    cout << "Enter list name: ";
    getline(cin, nombre);
    ComprobarCadenaVacia(nombre);
  } while (nombre == "");
}

void addList(Project &toDoList){
  List nueva;
  int comprobacion; 

  IntroducirNombreLista(nueva.name);
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
  
  IntroducirNombreLista(listname);
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
  bool verificador;
  verificador = true;
  int dias_mes[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};

  if (deadline.year < MINYEAR || deadline.year > MAXYEAR)
  {
    verificador =  false;
  }

  if(verificador == true && ((deadline.year % 4 == 0 && deadline.year % 100 != 0) || deadline.year % 400 == 0)){
    dias_mes[1]++;
  }

  if (verificador == true && (deadline.month < ENERO || deadline.month > DICIEMBRE))
  {
    verificador = false;
  }
  else{
    if (verificador == true)
    {
      deadline.month --;
      if (deadline.day < 1 || deadline.day > dias_mes[deadline.month])
      {
        verificador = false;
      }   
    }
  }
  
  return verificador;
}

void addTask(Project &toDoList){
  string listname;
  Task newtask;
  int comprobacionName;
  char simbolo;
  
  IntroducirNombreLista(listname);
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
      if (newtask.time < MINEXPECTEDTIME || newtask.time > MAXEXPECTEDTIME)
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

void ComprobarYHacerFuncionTask(Project &toDoList, string nombre, int marcadorLista, int funcion){
  int i, veces;
  veces = 0;

    for (i = 0; i < (int) toDoList.lists[marcadorLista].tasks.size(); i++)
    {
      if (nombre == toDoList.lists[marcadorLista].tasks[i].name)
      {
        veces ++;
        if (funcion == BORRAR)
        {
          toDoList.lists[marcadorLista].tasks.erase(toDoList.lists[marcadorLista].tasks.begin() + i);
          i--;          
          /* El i-- sirve para cuando hay dos tareas con el mismo nombre seguidas, ya que se modifica el size del vector al borrar
          y si no lo pusiera se saltaria la segunda.*/ 
        }
        else{
          if (funcion == TOGGLE)
          {
            if (toDoList.lists[marcadorLista].tasks[i].isDone == false)
            {
              toDoList.lists[marcadorLista].tasks[i].isDone = true;
            }
            else
            {
              toDoList.lists[marcadorLista].tasks[i].isDone = false;
            }  
          }
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
  
  IntroducirNombreLista(listname);
  comprobacionLista = ComprobarNombresListas(toDoList, listname);
  if (comprobacionLista == -1)
  {
    error(ERR_LIST_NAME);
  }
  else{
    cout << "Enter task name: ";
    getline(cin, taskname);
    ComprobarYHacerFuncionTask(toDoList, taskname, comprobacionLista, BORRAR);
  }
}

void toggleTask(Project &toDoList){
  int ComprobacionLista;
  string listname, taskname;

  IntroducirNombreLista(listname);
  ComprobacionLista = ComprobarNombresListas(toDoList, listname);
  if (ComprobacionLista == -1)
  {
    error(ERR_LIST_NAME);
  }
  else
  {
    cout << "Enter task name: ";
    getline(cin, taskname);
    ComprobarYHacerFuncionTask(toDoList, taskname, ComprobacionLista, TOGGLE);
  }
}

char XTasks(const Project &toDoList, int i, int j){
  int marcador;

  if (toDoList.lists[i].tasks[j].isDone == true)
  {
    marcador = 'X';
  }
  else
  {
    marcador = ' ';
  }
  return marcador;
}

void ImprimirInformacionTareas(const Project &toDoList, int i, int j){
  char marcador;
  marcador = XTasks(toDoList, i, j);

  cout << "[" << marcador << "] ";
  cout << "(" << toDoList.lists[i].tasks[j].time << ") ";
  cout << toDoList.lists[i].tasks[j].deadline.year << "-" << toDoList.lists[i].tasks[j].deadline.month << "-" << toDoList.lists[i].tasks[j].deadline.day;
  cout << " : " << toDoList.lists[i].tasks[j].name << endl;
}

void HighestPriority(const Project &toDoList, int &posi, int &posj, int i, int j){
  if (toDoList.lists[i].tasks[j].deadline.year < toDoList.lists[posi].tasks[posj].deadline.year)
  {
    posi = i;
    posj = j;
  }
  else
  {
    if (toDoList.lists[i].tasks[j].deadline.year == toDoList.lists[posi].tasks[posj].deadline.year)
    {
      if (toDoList.lists[i].tasks[j].deadline.month < toDoList.lists[posi].tasks[posj].deadline.month)
      {
        posi = i;
        posj = j;
      }
      else
      {
        if (toDoList.lists[i].tasks[j].deadline.month == toDoList.lists[posi].tasks[posj].deadline.month)
        {
          if (toDoList.lists[i].tasks[j].deadline.day < toDoList.lists[posi].tasks[posj].deadline.day)
          {
            posi = i;
            posj = j;
          } 
        }
      } 
    } 
  } 
}

void InformacionListas(const Project &toDoList){
  int i, j, posi, posj, vecesPendientes, vecesHechas, totalLeft, totalDone;
  totalLeft = 0;
  totalDone = 0;
  vecesHechas = 0;
  vecesPendientes = 0;

  for (i = 0; i < (int) toDoList.lists.size(); i++)
  {
    cout << toDoList.lists[i].name << endl;
    for (j = 0; j < (int) toDoList.lists[i].tasks.size(); j++)
    {
      if (toDoList.lists[i].tasks[j].isDone == false)
      {
        ImprimirInformacionTareas(toDoList, i, j);
        totalLeft = totalLeft + toDoList.lists[i].tasks[j].time;
        vecesPendientes ++;
        if (vecesPendientes == 1)     //Coje la posicion de la primera tarea pendiente que encuentra, si la hay.
        {
          posi = i;
          posj = j;
        }
        else
        {
          HighestPriority(toDoList, posi, posj, i, j);  //Si hay mas de una tarea pendiente compara las fechas de la que va encontrando, 
        }                                               //para encontrar la de mayor prioridad.
      }
    }
    for (j = 0; j < (int) toDoList.lists[i].tasks.size(); j++)
    {
      if (toDoList.lists[i].tasks[j].isDone == true)
      {
        ImprimirInformacionTareas(toDoList, i, j);
        totalDone = totalDone + toDoList.lists[i].tasks[j].time;
        vecesHechas ++;
      }
    }      
  }
  cout << "Total left: " << vecesPendientes << " (" << totalLeft << " minutes)" << endl;
  cout << "Total done: " << vecesHechas << " (" << totalDone << " minutes)" << endl;
  if (vecesPendientes > 0)
  {
    cout << "Highest priority: " << toDoList.lists[posi].tasks[posj].name;
    cout << " (" << toDoList.lists[posi].tasks[posj].deadline.year << "-" << toDoList.lists[posi].tasks[posj].deadline.month;
    cout << "-" << toDoList.lists[posi].tasks[posj].deadline.day << ")" << endl;
  }
}

void report(const Project &toDoList){
  cout << "Name: " << toDoList.name << endl;

  if (toDoList.description != "")
  {
    cout << "Description: " << toDoList.description << endl;
  }

  InformacionListas(toDoList);
}

void showProjectMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

int PedirYComprobarId(const vector<Project> &projects){
  int id, pos, i;
  pos = -1;

  cout << "Enter project id: ";
  cin >> id;
  cin.get();

  for (i = 0; i < (int) projects.size() && pos == -1; i++)
  {
    if (projects[i].id == id)
    {
      pos = i;
    }
  }

  return pos;
}

void ProjectMenu(ToDo &ProjectManagement){
  char option;
  int pos;

  pos = PedirYComprobarId(ProjectManagement.projects);
  if (pos == -1)
  {
    error(ERR_ID);
  }
  else
  {
    do
    {
      showProjectMenu();
      cin >> option;
      cin.get();
      switch(option){
        case '1': editProject(ProjectManagement.projects[pos]);
                  break;
        case '2': addList(ProjectManagement.projects[pos]);
                  break;
        case '3': deleteList(ProjectManagement.projects[pos]);
                  break;
        case '4': addTask(ProjectManagement.projects[pos]);
                  break;
        case '5': deleteTask(ProjectManagement.projects[pos]);
                  break;
        case '6': toggleTask(ProjectManagement.projects[pos]);
                  break;
        case '7': report(ProjectManagement.projects[pos]);
                  break;
        case 'b': break;
        default: error(ERR_OPTION);
      }  
    }while(option != 'b');    
  } 
}

int ComprobarNombreProyecto(const vector<Project> &projects, string name){
  int i, pos;
  pos = -1;
  for (i = 0; i < (int) projects.size() && pos == -1; i++)
  {
    if (projects[i].name == name)
    {
      pos = i;
    }
  }
  return pos;
}

void addProject(ToDo &ProjectManagement){
  Project nuevo;
  do
  {
    cout << "Enter project name: ";
    getline(cin, nuevo.name);
    ComprobarCadenaVacia(nuevo.name);   
  } while (nuevo.name == "");
  
  if (ComprobarNombreProyecto(ProjectManagement.projects, nuevo.name) != -1)
  {
    error(ERR_PROJECT_NAME);
  }
  else
  {
    cout << "Enter project description: ";
    getline(cin, nuevo.description);
    nuevo.id = ProjectManagement.nextId;
    ProjectManagement.projects.push_back(nuevo);
    ProjectManagement.nextId ++;
  }
}

void removeProject(ToDo &ProjectManagement){
  int pos;
  pos = PedirYComprobarId(ProjectManagement.projects);

  if (pos == -1)
  {
    error(ERR_ID);
  }
  else
  {
    ProjectManagement.projects.erase(ProjectManagement.projects.begin() + pos);
  } 
}

void showMainMenu(){
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary" << endl
       << "q- Quit" << endl
       << "Option: ";
}

int main(){
  ToDo ProjectManagement;
  ProjectManagement.name = "My ToDo list";
  ProjectManagement.nextId = 1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': ProjectMenu(ProjectManagement);
                break;
      case '2': addProject(ProjectManagement);
                break;
      case '3': removeProject(ProjectManagement);
                break;
      case '4': 
                break;
      case '5': 
                break;
      case '6': 
                break;
      case '7': 
                break;
      case '8':
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}

