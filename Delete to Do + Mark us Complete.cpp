#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Task {
    string name;
    bool completed;
};

int main() {
    map<string,string> myMap;
    vector<map<string,string>> data; // Store myMap for each row in data
    string textline;
    ifstream read;

    read.open("data.csv");
    getline(read,textline); // First line (column headers)
    vector<string> keys = tokens(textline, ",");
    vector<string> row;
    while (getline(read, textline)) { // Read each line until end of file
        row = tokens(textline, ",");  
        myMap.clear(); // Clear map before adding new pairs
        for (size_t i = 0; i < keys.size(); i++) {
            myMap.insert(pair<string, string>(keys.at(i),row[i]));
        }
        data.push_back(myMap);
    }
    TodoList_table(data,keys);

    int choice;
    cout << "\n1. Delete Task\n2. Mark Task as Complete\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: { // Delete to Do
            int taskIndex;
            cout << "Enter task index to delete: ";
            cin >> taskIndex;
            if (taskIndex >= 1 && taskIndex <= data.size()) {
                data.erase(data.begin() + taskIndex - 1); // Remove task from data
                // Update IDs in data vector
                for (size_t i = taskIndex - 1; i < data.size(); ++i) {
                    data[i]["ID"] = to_string(i + 1);
                }
                // Update CSV file
                ofstream file("data.csv");
                file << "ID,All To Dos,Status,Category,Due Date,Remarks" << endl; // Rewrite headers
                for (const auto& entry : data) {
                    for (const auto& pair : entry) {
                        file << pair.second << ",";
                    }
                    file << endl;
                }
                cout << "Task deleted successfully." << endl;
            } else {
                cout << "Invalid task index!" << endl;
            }
            break;
        }
        case 2: {
            int taskIndex;
            cout << "Enter task index to mark as complete: ";
            cin >> taskIndex;
            if (taskIndex >= 1 && taskIndex <= data.size()) {
                data[taskIndex - 1]["Status"] = "completed";
                // Update CSV file
                ofstream file("data.csv");
                file << "ID,All To Dos,Status,Category,Due Date,Remarks" << endl; // Rewrite headers
                for (const auto& entry : data) {
                    for (const auto& pair : entry) {
                        file << pair.second << ",";
                    }
                    file << endl;
                }
                cout << "Task marked as complete successfully." << endl;
            } else {
                cout << "Invalid task index!" << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}

