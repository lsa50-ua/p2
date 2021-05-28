#include "List.h"
#include <iostream>
using namespace std;

int main(){
    Task t("tarea1");
    List l("compra");

    cout << l << endl;

    l.addTask(t);

    cout << l << endl;

    l.toggleTask("tarea1");

    cout << l << endl;

    return 0;
}