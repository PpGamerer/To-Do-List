#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void Viewalltdfromctgr(){
    string notcompletetask;
    cout << "What category do you want to view? : ";
    cin >> notcompletetask; //ประเภทที่ยังไม่เสร็จทั้งหมด
    cout << "This is all task that is not complete." << endl;
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
    

