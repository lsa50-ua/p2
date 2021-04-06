// DNI 48804855M SIMÓN ALBARRÁN, LUIS 

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

const int MAXEXPECTEDTIME = 180;
const int MINEXPECTEDTIME = 1;
const int DICIEMBRE = 12;
const int ENERO = 1;
const int MAXYEAR = 2100;
const int MINYEAR = 2000;
const int BORRAR = 1;
const int TOGGLE = 2;
const int KMAXNAME = 20;
const int KMAXDESC = 40;

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

struct BinTask{
char name[KMAXNAME];
Date deadline;
bool isDone;
int time;
};

struct BinList{
char name[KMAXNAME];
unsigned numTasks;
};

struct BinProject{
char name[KMAXNAME];
char description[KMAXDESC];
unsigned numLists;
};

struct BinToDo{
char name[KMAXNAME];
unsigned numProjects;
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
  if(pos != -1)
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

void deleteProject(ToDo &ProjectManagement){
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

char imprimirIsDone(bool hecho){  
  char estado;

  if (hecho == true)
  {
    estado = 'T';
  }
  else
  {
    estado = 'F';
  }
  return estado;
}

void exportarTareas(Task tareas, ofstream &fichero){  // funcion que complementa a exportarProyecto, para escribir tareas
  char estado;

  estado = imprimirIsDone(tareas.isDone);
  fichero << tareas.name << "|";
  fichero << tareas.deadline.day << "/";
  fichero << tareas.deadline.month;
  fichero << "/" << tareas.deadline.year;
  fichero << "|" << estado;
  fichero << "|" << tareas.time << endl;
}

void exportarProyecto(Project proyecto, ofstream &fichero){ // funcion que escribe el proyecto seleccionado en el formato pedido a fichero
  int i, j;
  i = 0;
  j = 0;

  fichero << "<" << endl;
  fichero << "#" << proyecto.name << endl;     
  if (proyecto.description != "")
  {
   fichero << "*" << proyecto.description << endl;
  }
  for (i = 0; i < (int) proyecto.lists.size(); i++)
  {
    fichero << "@" << proyecto.lists[i].name << endl;
    for (j = 0; j < (int) proyecto.lists[i].tasks.size(); j++)
    {
      exportarTareas(proyecto.lists[i].tasks[j], fichero);
    }
  }
  fichero << ">" << endl;  
}

string pedirNombreFichero(){
  string nombre;

  cout << "Enter filename: ";
  getline(cin, nombre);
  
  return nombre;
}

void exportOne(const ToDo &ProjectManagement){  // funcion que exporta, pidiendo el id del proyecto, un proyecto a un fichero llamando a la funcion exportarProyecto
  int pos;
  string nombreFich;
  ofstream fichero;

  pos = PedirYComprobarId(ProjectManagement.projects);
  if (pos == -1)
  {
    error(ERR_ID);
  }
  else
  {
    nombreFich = pedirNombreFichero();
    fichero.open(nombreFich.c_str());
    if (fichero.is_open() == false)
    {
      error(ERR_FILE);
    }
    else
    {
      exportarProyecto(ProjectManagement.projects[pos], fichero);
      fichero.close();
    } 
  }
}

void exportarTodos(const vector<Project> &projects){  // funcion que exporta todos los proyectos del programa a un fichero, llamando dentro de un bucle a la funcion exportarProyecto
  int i;
  string nombreFich;
  ofstream fichero;

  nombreFich = pedirNombreFichero();
  fichero.open(nombreFich.c_str());
  if (fichero.is_open() == false)
  {
    error(ERR_FILE);
  }
  else
  {
    for (i = 0; i < (int) projects.size(); i++)
    {
      exportarProyecto(projects[i], fichero);
    }
    fichero.close();
  } 
}

void exportProjects(ToDo &ProjectManagement){
  char respuesta;
  
  do
  {
    cout << "Save all projects [Y/N]?: ";
    cin >> respuesta;
    cin.get();
  } while (respuesta != 'n' && respuesta != 'N' && respuesta != 'y' && respuesta != 'Y');
  if (respuesta == 'n' || respuesta == 'N')
  {
    exportOne(ProjectManagement);
  }
  else
  {
    exportarTodos(ProjectManagement.projects);
  }
}

bool leerTareaFichero(string linea, Task &tarea, int projectRep){ // capta las variables de la tarea leida del fichero
  char separador, isDone;
  bool verificador = false;
  stringstream bufferear(linea);

  getline(bufferear, tarea.name, '|');
  bufferear >> tarea.deadline.day >> separador
            >> tarea.deadline.month >> separador >> tarea.deadline.year 
            >> separador >> isDone >> separador >> tarea.time;
  if (isDone == 'T')
  {
    tarea.isDone = true;
  }
  else
  {
    tarea.isDone = false;
  }
  if (ComprobarFecha(tarea.deadline) == false && projectRep == -1)
  {
    error(ERR_DATE);
  }
  else
  {
    if ((tarea.time < MINEXPECTEDTIME || tarea.time > MAXEXPECTEDTIME) && projectRep == -1)
    {
      error(ERR_TIME);
    }
    else
    {
      verificador = true;
    }
  }
  return verificador;
}

void importProjects(ToDo &ProjectManagament, string nombreFich, bool &abierto){
  ifstream fichero;
  string linea, name, description;
  Project project;
  List list;
  Task task;
  int projectRep;
  bool outMainMenu = false;
  abierto = true;

  if (nombreFich != "")
  {
    fichero.open(nombreFich.c_str());
    outMainMenu = true;
  }
  else
  {
    nombreFich = pedirNombreFichero();
    fichero.open(nombreFich.c_str());
  }
  if (fichero.is_open() == false)
  {
    if (outMainMenu == false)
    {
      error(ERR_FILE);
    }
    abierto = false;
  }
  else
  {
    while(getline(fichero, linea)){
      project.lists.clear();
      getline(fichero, name);
      name.erase(name.begin());
      projectRep = ComprobarNombreProyecto(ProjectManagament.projects, name);
      if (projectRep != -1)
      {
        error(ERR_PROJECT_NAME);
      }
      getline(fichero, linea);
      if(linea[0] == '*')
      {
        linea.erase(linea.begin());
        description = linea;
        getline(fichero, linea);
      }
      else
      {
        description = "";
      }
      if (linea[0] != '>')
      {
        while (linea[0] == '@')
        {
          list.tasks.clear();
          list.name = linea;
          list.name.erase(list.name.begin());
          getline(fichero, linea);
          while (linea[0] != '>' && linea[0] != '@')
          {
            if(leerTareaFichero(linea, task, projectRep) == true)
            {
              list.tasks.push_back(task);
            }
            getline(fichero, linea);
          }
          project.lists.push_back(list);
        } 
      }
      if (projectRep == -1)
      {
        project.name = name;
        project.description = description;
        project.id = ProjectManagament.nextId;
        ProjectManagament.nextId ++;
        ProjectManagament.projects.push_back(project);
      }
    }
    fichero.close();
  }
}

void contarTareas(const vector<List> &lists, int &tareasTotales, int &tareasHechas){  //cuenta las tareas totales y hechas de todas las listas del proyecto
  int i, j;
  tareasTotales = 0;
  tareasHechas = 0;

  for (i = 0; i < (int) lists.size(); i++)
  {
    for (j = 0; j < (int) lists[i].tasks.size(); j++)
    {
      tareasTotales ++;
      if (lists[i].tasks[j].isDone == true)
      {
        tareasHechas ++;
      }
    }
  }
}

void summary(const vector<Project> &projects){
  int i, totalTasks, tasksDone;

  for (i = 0; i < (int) projects.size(); i++)
  {
    cout << "(" << projects[i].id << ") " << projects[i].name;
    contarTareas(projects[i].lists, totalTasks, tasksDone);
    cout << " [" << tasksDone << "/" << totalTasks << "]" << endl;
  }
}

void copiarNombreACadenayComprobarFinalDeCadena(string origen, char destino[KMAXNAME]){
  strncpy(destino, origen.c_str(), KMAXNAME);
  if (origen.length() > KMAXNAME - 1)
  {
    destino[KMAXNAME - 1] = '\0';
  }
}

void CopiarDatosEnFicheroBinario(const ToDo &ProjectManagement, ofstream &fichero){
  int i, j, k;
  BinToDo toDoB;
  BinProject project;
  BinList lista;
  BinTask tarea;

  copiarNombreACadenayComprobarFinalDeCadena(ProjectManagement.name, toDoB.name);
  toDoB.numProjects = ProjectManagement.projects.size();
  fichero.write((const char *) &toDoB, sizeof(toDoB));
  for (i = 0; i < (int) ProjectManagement.projects.size(); i++)
  {
    copiarNombreACadenayComprobarFinalDeCadena(ProjectManagement.projects[i].name, project.name);
    strncpy(project.description, ProjectManagement.projects[i].description.c_str(), KMAXDESC);
    if (ProjectManagement.projects[i].description.length() > KMAXDESC - 1)
    {
      project.description[KMAXDESC - 1] = '\0';
    }
    project.numLists = ProjectManagement.projects[i].lists.size();
    fichero.write((const char*) &project, sizeof(project));
    for (j = 0; j < (int) ProjectManagement.projects[i].lists.size(); j++)
    {
      copiarNombreACadenayComprobarFinalDeCadena(ProjectManagement.projects[i].lists[j].name, lista.name);
      lista.numTasks = ProjectManagement.projects[i].lists[j].tasks.size();
      fichero.write((const char*) &lista, sizeof(lista));
      for (k = 0; k < (int) ProjectManagement.projects[i].lists[j].tasks.size(); k++)
      {
        copiarNombreACadenayComprobarFinalDeCadena(ProjectManagement.projects[i].lists[j].tasks[k].name, tarea.name);
        tarea.deadline = ProjectManagement.projects[i].lists[j].tasks[k].deadline;
        tarea.isDone = ProjectManagement.projects[i].lists[j].tasks[k].isDone;
        tarea.time = ProjectManagement.projects[i].lists[j].tasks[k].time;
        fichero.write((const char *) &tarea, sizeof(tarea));
      } 
    } 
  }
}

void saveData(const ToDo &ProjectManagement){
  ofstream fichero;
  string nombreFich;

  nombreFich = pedirNombreFichero();
  fichero.open(nombreFich.c_str(), ios::binary);
  if (fichero.is_open() == false)
  {
    error(ERR_FILE);
  }
  else
  {
    CopiarDatosEnFicheroBinario(ProjectManagement, fichero);
    fichero.close();
  }
}

void cargarFicheroBinario(ToDo &ProjectManagement, ifstream &fichero){
  unsigned i, j, k;
  BinToDo toDo;
  BinProject projectbin;
  BinList listbin;
  BinTask taskbin;
  Project project;
  List list;
  Task task;

  ProjectManagement.projects.clear();
  fichero.read((char *) &toDo, sizeof(toDo));
  ProjectManagement.name = toDo.name;
  ProjectManagement.nextId = 1;
  for (i = 0; i < toDo.numProjects; i++)
  {
    fichero.read((char *) &projectbin, sizeof(projectbin));
    project.name = projectbin.name;
    project.description = projectbin.description;
    project.id = ProjectManagement.nextId;
    ProjectManagement.nextId ++;
    for (j = 0; j < projectbin.numLists; j++)
    {
      fichero.read((char *) &listbin, sizeof(listbin));
      list.name = listbin.name;
      for (k = 0; k < listbin.numTasks; k++)
      {
        fichero.read((char *) &taskbin, sizeof(taskbin));
        task.name = taskbin.name;
        task.deadline = taskbin.deadline;
        task.isDone = taskbin.isDone;
        task.time = taskbin.time;
        list.tasks.push_back(task);
      }
      project.lists.push_back(list);
      list.tasks.clear();
    }
    ProjectManagement.projects.push_back(project);
    project.lists.clear();
  } 
}

void loadData(ToDo &ProjectManagement, string nombreFichAux, bool &abierto){
  char respuesta;
  ifstream fichero;
  string nombreFich;
  bool outMainMenu = false;
  abierto = true;
  
  if (nombreFichAux != "")
  {
    fichero.open(nombreFichAux.c_str(), ios::binary);
    outMainMenu = true;
  }
  else
  {
    nombreFich = pedirNombreFichero();
    fichero.open(nombreFich.c_str(), ios::binary);
  }
  if (fichero.is_open() == false)
  {
    if (outMainMenu == false)
    {
      error(ERR_FILE);
    }
    abierto = false;
  }
  else
  {
    if (nombreFichAux == "")
    {
      do
      {
        cout << "Confirm [Y/N]?: ";
        cin >> respuesta;
        respuesta = tolower(respuesta);
      } while (respuesta != 'y' && respuesta != 'n');
    }
    else
    {
      respuesta = 'y';
    }
    if (respuesta == 'y')
    {
      cargarFicheroBinario(ProjectManagement, fichero);
    }  
    fichero.close(); 
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

bool comprobarArgumentos(int argc, char *argv[], string &namefich_text, string &namefich_bin){
  bool comprobar = true;
  int i, contador_arg_l, contador_arg_i;
  namefich_text = "";
  namefich_bin = ""; 
  contador_arg_l = 0;
  contador_arg_i = 0;

  for (i = 1; i < argc && comprobar == true; i++)
  {
    if(strcmp(argv[i], "-l") == 0 && contador_arg_l == 0)
    {
      if ((i + 1) >= argc)
      {
        comprobar = false;
      }
      else
      {
        namefich_bin = argv[i + 1];
        i++;
        contador_arg_l ++;
      } 
    }
    else
    {
      if (strcmp(argv[i], "-i") == 0 && contador_arg_i == 0)
      {
        if ((i + 1) >= argc)
        {
          comprobar = false;
        }
        else
        {
          namefich_text = argv[i + 1];
          i++;
          contador_arg_i ++;
        }
      }
      else
      {
        comprobar = false;
      }
    }
  }
  return comprobar;
}

int main(int argc, char *argv[]){
  ToDo ProjectManagement;
  ProjectManagement.name = "My ToDo list";
  ProjectManagement.nextId = 1;
  string namefich_txt, namefich_bin;
  bool comprobacion, isOpen;
  char option;
  isOpen = true;
  
  comprobacion = comprobarArgumentos(argc, argv, namefich_txt, namefich_bin);
  if (comprobacion == false)
  {
    error(ERR_ARGS);
  }
  else
  {
    if (namefich_bin != "")
    {
      loadData(ProjectManagement, namefich_bin, isOpen);
    }
    if (isOpen == true)
    {
      if (namefich_txt != "")
      {
        importProjects(ProjectManagement, namefich_txt, isOpen);
      }
    }
    if (isOpen == false)
    {
      error(ERR_FILE);
    }
    else
    {
      do{
        showMainMenu();
        cin >> option;
        cin.get();
        
        switch(option){
          case '1': ProjectMenu(ProjectManagement);
                    break;
          case '2': addProject(ProjectManagement);
                    break;
          case '3': deleteProject(ProjectManagement);
                    break;
          case '4': importProjects(ProjectManagement, "", isOpen);
                    break;
          case '5': exportProjects(ProjectManagement);
                    break;
          case '6': loadData(ProjectManagement, "", isOpen);
                    break;
          case '7': saveData(ProjectManagement);
                    break;
          case '8': summary(ProjectManagement.projects);
                    break;
          case 'q': break;
          default: error(ERR_OPTION);
        }
      }while(option!='q');
    }
  }
  return 0;    
}

