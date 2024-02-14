#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>


using namespace std;

// ใน Task เก็บค่า name และ completed
struct Task {
    string name;
    bool completed;
};

// Function to add a task to the to-do list
void addTask(vector<Task> &todoList, const string &taskName) {
    Task newTask = {taskName, false};
    todoList.push_back(newTask);
    cout << "Task added: " << taskName << endl;
}

// Function to mark a task as completed
void completeTask(vector<Task> &todoList, int taskIndex) {
    if (taskIndex >= 0 && taskIndex < todoList.size()) {
        todoList[taskIndex].completed = true;
        cout << "Task marked as completed: " << todoList[taskIndex].name << endl;
    } else {
        cout << "Invalid task index!" << endl;
    }
}

// Function to delete a task from the to-do list
void deleteTask(vector<Task> &todoList, int taskIndex) {
    if (taskIndex >= 0 && taskIndex < todoList.size()) {
        cout << "Task deleted: " << todoList[taskIndex].name << endl;
        todoList.erase(todoList.begin() + taskIndex);
    } else {
        cout << "Invalid task index!" << endl;
    }
}

// Function to display the to-do list
void displayList(const vector<Task> &todoList) {
    cout << "To-Do List:" << endl;
    for (int i = 0; i < todoList.size(); ++i) {
        cout << i + 1 << ". ";
        if (todoList[i].completed) {
            cout << "[X] ";
        } else {
            cout << "[ ] ";
        }
        cout << todoList[i].name << endl;
    }
}



void addTodo(const string& filename, const vector<string>& entry) {
    // Open the file in append mode
    ofstream file(filename, ios::app);
    // Write the entry to the file
    for (const auto& field : entry) {
        file << field << ",";
    }
    file << endl;
    file.close();

    std::cout << "New entry added to " << filename << " successfully." << endl;
}


void displayMenu(){
    system("cls");
    cout << "\033[1;31m*=================================*" << endl;
    cout << "|            \033[1;33mTo do List           \033[1;31m|" << endl;
    cout << "\033[1;31m*=================================*" << endl;
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

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                system("cls");
                cout << "You chose View all to do" << endl;
            
                break;
            case 2:
                system("cls");
                cout << "You chose View completed to do" << endl;
            
                break;
            case 3:
                system("cls");
                cout << "You chose View all to do from category" << endl;
                
                break;
            case 4:
                system("cls");
                cout << "You chose Add new to do" << endl;
                
                break;
            case 5:
                system("cls");
                cout << "You chose Delete a To-do" << endl;
                break;
             case 6:
                system("cls");
                cout << "You chose Mark as completed" << endl;
                break;
            case 7:
                system("cls");
                cout << "Exiting..." << endl;
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



