#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Prototype functions
void updateStatus(vector<map<string, string>>& data, const string& id, const vector<string>& keys);
string selectIDToMark(const vector<map<string, string>>& data);

string selectIDToMark(const vector<map<string, string>>& data) {
    string taskId;
    bool idFound = false;
    do {
        cout << "\033[1;32mEnter the ID of the task you want to mark as done: ";
        cout << "\033[1;37m";
        getline(cin, taskId);
         if (taskId.empty()) {
            cout << "\033[1;32mPlease enter an exist ID." << endl;
            continue;
        }
        idFound = false;
        for (const auto& todo : data) {
            if (todo.at("ID") == taskId) {
                if(todo.at("Status") == "undone"){
                idFound = true;}
                break;
            }
        }
        if (!idFound) {
            cout << "\033[1;31mThis ID was not found: " << taskId << endl;
        }
    } while (!idFound);


    return taskId;
}

// Function to update the status of a task
void updateStatus(vector<map<string, string>>& data, const string& id, const vector<string>& keys) {
    for (auto& todo : data) {
        if (todo["ID"] == id) {
            if (todo["Status"] == "undone") {
                todo["Status"] = "done";
                system("cls");
                cout << "Task with ID " << id << " is marked as done." << endl;
                findTodoDone(data,keys);
            }
            // Write the updated data back to the file
            ofstream file("data.csv");
            if (file.is_open()) {
                // Write column headers
                for (size_t i = 0; i < keys.size(); ++i) {
                    file << keys[i];
                    if (i != keys.size() - 1) file << ",";
                    else file << "\n";
                }
                // Write each row of data
                for (const auto& row : data) {
                    for (size_t i = 0; i < keys.size(); ++i) {
                        file << row.at(keys[i]);
                        if (i != keys.size() - 1) file << ",";
                        else file << "\n";
                    }
                }
                file.close();
            } else {
                cout << "\033[1;31mUnable to open file." << endl;
            }
            return;
        }
    }
    cout << "\033[1;31mTask with ID " << id << " \033[1;31mnot found." << endl;
} 
