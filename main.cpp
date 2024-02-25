#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "menu.h"
#include "viewtodo.h"
#include "addTodo.h"
#include "deleteTodo.h"
#include "table.h"
#include "mark_as_completed.h"
#include "modify.h"

using namespace std;
void delay(int sec);

int main() {
    map<string, string> myMap;
    vector<map<string, string>> data; //เก็บ myMap แต่ละแถวไว้ใน data
    string textline;
    ifstream read;

    read.open("data.csv");
    std::getline(read, textline); //บรรทัดแรก (หัวข้อประเภท)
    vector<string> keys = tokens(textline, ","); //แยกตามหัวข้อ ใช้delimiter = ","
    vector<string> row;
    while (std::getline(read, textline)) { //อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline, ",");  //delimiter = ","
        myMap.clear(); //เคลียร์mapก่อนpair
        for (size_t i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap.insert(pair<string, string>(keys.at(i), row[i])); //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap); //ใส่ทุกคู่ลงใน data
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
                std::cout << "\033[1;33mYou chose View all To-do" << endl << "\033[1;33m" ;
                findTodoUndone(data, keys);
                break;
            case 2:
                system("cls");
                std::cout << "\033[1;33mYou chose View completed To-do" << endl;
                findTodoDone(data, keys);
                break;
            case 3:
                system("cls");
                std::cout << "\033[1;33mYou chose View all To-do from category" << endl;
                displayAvailableCategories(data);
                findTodoByCategory(data, keys, selectCategory(data));
                break;
            case 4:
                system("cls");
                std::cout << "\033[1;33mYou chose Add new To-do" << endl;
                getUserInput(data,keys);
                break;
            case 5:
                system("cls");
                std::cout << "\033[1;33mYou chose Delete a To-do" << endl;
                TodoList_table(data,keys);
                deleteTodo("data.csv", data, keys, selectIDToDelete(data));
                TodoList_table(data,keys);
                break;
             case 6:
                system("cls");
                std::cout << "\033[1;33mYou chose Mark as completed" << endl;
                findTodoUndone(data, keys);
                updateStatus(data, selectIDToMark(data), keys);
                break;
            case 7:
                system("cls");
                std::cout << "\033[1;33mYou chose Modify a To-do" << endl;
                TodoList_table(data,keys);
                modifyTodo(data, keys);
                break;
            case 8:
                system("cls");
                std::cout << "\033[1;31mExiting..." << endl;
                exit(EXIT_SUCCESS);
                break;
            default:
                std::cout << "\033[1;31mInvalid choice. Please try again." << endl;
                delay(1.5);
                continue;
        }
        cin.ignore();
        cin.get(); // รอกดEnter
    } while(choice != 7);
    
    return 0;
}

void delay(int seconds) {
    clock_t start_time = clock(); // Get the initial clock time
    while (clock() < start_time + seconds * CLOCKS_PER_SEC) {
        // Loop until the current clock time exceeds the specified delay
    }
}
