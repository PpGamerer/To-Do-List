#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;

void displayMenu(){
    system("cls");
    cout << "\033[1;31m+=================================+" << endl;
    cout << "|            \033[1;33mTo do List           \033[1;31m|" << endl;
    cout << "\033[1;31m+=================================+" << endl;
    cout << "\033[1;31m|                                 \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 1. View all to do               \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 2. View completed to do         \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 3. View all to do from category \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 4. Add new to do                \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 5. Delete a To-do               \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 6. Mark as completed            \033[1;31m|" << endl;
    cout << "\033[1;31m|\033[1;33m 7. Exit                         \033[1;31m|" << endl;
    cout << "\033[1;31m|                                 \033[1;31m|" << endl;
    cout << "\033[1;31m***********************************" << endl;
    cout << "\033[1;32m  Enter your choice: ";
}

