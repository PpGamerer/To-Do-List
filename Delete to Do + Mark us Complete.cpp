#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ใน Task เก็บ name และ completed
struct Task {
    string name;
    bool completed;
};
// Function to delete a task from the to-do list
void deleteTask(vector<Task> &todoList, int taskIndex) {
    if (taskIndex >= 0 && taskIndex < todoList.size()) {
        cout << "Task deleted: " << todoList[taskIndex].name << endl;
        todoList.erase(todoList.begin() + taskIndex);
    } else {
        cout << "Invalid task index!" << endl;
    }
}
// Function to mark a task as completed
void completeTask(vector<Task> &todoList, int taskIndex) {
    if (taskIndex >= 0 && taskIndex < todoList.size()) {
        todoList[taskIndex].completed = true;
        cout << "Task mark as completed: " << todoList[taskIndex].name << endl;
    } else {
        cout << "Invalid task index!" << endl;
    }
}

int main() {
    vector<Task> todoList;
    int choice;
    string taskName;
    
    cout << "Tasks To Do " << endl;
    
    do {
        cout << "------------\n3-Delete Task\n4-Complete Task\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
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
            default:
                system("cls");
                cout << "Invalid choice! Please enter a number between 3 and 4." << endl;
        }
    } while (choice != 3 && choice != 4);
    
    return 0;
}

