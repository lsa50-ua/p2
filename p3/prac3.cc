#include <iostream>
#include "Util.h"
#include "ToDo.h"
#include "Project.h"

using namespace std;

void showMainMenu(){
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Summary" << endl
       << "q- Quit" << endl
       << "Option: ";
}

int main(int argc,char *argv[]){
  // Hay una relación de agregación entre "ToDo" y "Project"
  // Por esta razón definimos un vector "listProjects" aquí, para que los proyectos no se destruyan si se destruye ToDo
  vector<Project*> listProjects;
  ToDo program("My ToDo list");
  string name,description;
  char option;

  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': // Project menu
                program.projectMenu();
                break;
      case '2': // Add project
                do{
                  cout << "Enter project name: ";
                  getline(cin,name);
                  try{
                    // Creamos el proyecto y lo añadimos al programa
                    // Si alguna de estas dos tareas falla, se lanzará una excepción
                    Project *newProject=new Project(name);
                    program.addProject(newProject);
                    // Añadimos la descripción
                    cout << "Enter project description: ";
                    getline(cin,description);
                    program.setProjectDescription(name,description);
                    newProject->setDescription(description);
                    // Añadimos el nuevo Project al vector "listProjects"
                    // De esta manera, aunque se destruya "ToDo" los proyectos seguirán existiendo en este vector
                    // Esto se hace porque existe una relación de "agregación" entre "ToDo" y "Project"
                    listProjects.push_back(newProject);
                  }
                  catch(Error e){
                    Util::error(e);
                  }
                }while(name=="");
                break;
      case '3': // Delete project
                program.deleteProject();
                break;
      case '4': // Summary
                cout << program << endl;
                break;
      case 'q': break;
      default: Util::error(ERR_OPTION);
    }
  }while(option!='q');

  // Liberamos la memoria reservada para los proyectos
  for(int i=0;(unsigned)i<listProjects.size();i++){
    delete listProjects[i];
  }

  return 0;
}
