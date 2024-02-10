#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string category;
void Viewalltdfromctgr(){
    cout << "All task that is not complete.";
    ifstream task;
    task.open("notcomplete.txt");
    string textline;
    while(getline(task,textline)){
        cout << textline;
    }
    task.close();
    
}

int main(){
    Viewalltdfromctgr();
}
    

