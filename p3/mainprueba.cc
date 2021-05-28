#include "ToDo.h"
#include <iostream>
using namespace std;

int main(){
    List list("lista1");
    Task t1("Task 1"), t2("Task 2"), t3("Task 3");
    list.addTask(t1);
    list.addTask(t2);
    list.addTask(t3);
    list.deleteTask("Task 2");
    cout << list << endl;
    cout << list.getTimeTasks() << endl;
    return 0;
}