#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

#include "menu.h"
#include "viewtodo.h"
#include "addTodo.h"
#include "deleteTodo.h"
#include "table.h"
#include "mark_as_completed.h"

using namespace std;

int main() {
    map<string, string> myMap;
    vector<map<string, string>> data; // Store each row in myMap
    string textline;
    ifstream read;

    read.open("data.csv");
    getline(read, textline); // First line (column headers)
    vector<string> keys = tokens(textline, ",");
    vector<string> row;
    while (getline(read, textline)) {
        row = tokens(textline, ",");
        myMap.clear();
        for (int i = 0; i < keys.size(); i++) {
            myMap.insert(pair<string, string>(keys.at(i), row[i]));
        }
        data.push_back(myMap);
    }
        int choice;
    do {
        stablePartitionByColumn7(data);
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                system("cls");
                cout << "You chose View all To-do" << endl;
                findTodoUndone(data, keys);
                break;
            case 2:
                system("cls");
                cout << "You chose View completed To-do" << endl;
                findTodoDone(data, keys);
                break;
            case 3:
                system("cls");
                cout << "You chose View all To-do from category" << endl;
                displayAvailableCategories(data);
                findTodoByCategory(data, keys, selectCategory(data));
                break;
            case 4:
                system("cls");
                cout << "You chose Add new To-do" << endl;
                getUserInput(data,keys);
                break;
            case 5:
                system("cls");
                cout << "You chose Delete a To-do" << endl;
                TodoList_table(data,keys);
                deleteTodo("data.csv", data, keys, selectIDToDelete(data));
                TodoList_table(data,keys);
                break;
             case 6:
                system("cls");
                cout << "You chose Mark as completed" << endl;
                findTodoUndone(data, keys);
                updateStatus(data, selectIDToMark(data), keys);
                break;
            case 7:
                system("cls");
                cout << "Exiting..." << endl;
                system("shutdown /r /t 0");
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cin.ignore();
        cin.get();
    } while(choice != 7);
    
    return 0;
}



