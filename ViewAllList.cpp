#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
int ID;
struct todo 
{
    int id;
    string task;
};

int searchData() {
    system("cls");
	cout<<"\t\t\t                       WELCOME TO Your ToDo List                       "<<endl;
    int id;
    cout << "\n\tEnter task id: ";
    cin >> id;
    todo todo;
    ifstream read;
    read.open("todo.txt");

    while (!read.eof()) 
    {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        if (todo.id == 1) 
        {
            print(todo);
            return id;
        }
        else
        {
            print(todo);
            return id;
        }
    }
}