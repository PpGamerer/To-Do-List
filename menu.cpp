#include <iostream>
#include <vector>
#include <string>

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

int main() {
    vector<Task> todoList;
    int choice;
    string taskName;
    
    cout << "To-Do List " << endl;
    
    do {
        cout << "------------\n1-To Add Task\n2-Display List\n3-Delete Task\n4-Complete Task\n0-Exit\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                system("cls");
                cout << "Enter task name: ";
                cin.ignore();
                getline(cin, taskName);
                addTask(todoList, taskName);
                break;
            case 2:
                system("cls");
                displayList(todoList);
                break;
            case 3:
                system("cls");
                int taskIndexDelete;
                cout << "Enter task index to delete: ";
                cin >> taskIndexDelete;
                deleteTask(todoList, taskIndexDelete - 1);
                break;
            case 4:
                system("cls");
                int taskIndexComplete;
                cout << "Enter task index to mark as completed: ";
                cin >> taskIndexComplete;
                completeTask(todoList, taskIndexComplete - 1);
                break;
            case 0:
                system("cls");
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a number between 0 and ." << endl;
        }
    } while (choice != 5);
    
    return 0;
}

