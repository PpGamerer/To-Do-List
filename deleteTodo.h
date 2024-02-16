#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

//prototype functions
void deleteTodo(const string& filename, vector<map<string, string>>& data, const vector<string>& keys, const string& id);
string selectIDToDelete(const vector<map<string, string>>& data);

string selectIDToDelete(const vector<map<string, string>>& data) {
    string findIDToDelete;
    bool idFound = false;
    do {
        cout << "Enter ID of the To-Do entry you want to delete: ";
        getline(cin, findIDToDelete);
         if (findIDToDelete.empty()) {
            cout << "Please enter an exist ID." << endl;
            continue;
        }
        idFound = false;
        for (const auto& todo : data) {
            if (todo.at("ID") == findIDToDelete) {
                idFound = true;
                break;
            }
        }
        if (!idFound) {
            cout << "This ID was not found: " << findIDToDelete << endl;
        }
    } while (!idFound);


    return findIDToDelete;
}

void deleteTodo(const string& filename, vector<map<string, string>>& data, const vector<string>& keys, const string& id) {
    // Find the index of the entry with the given ID
    auto it = find_if(data.begin(), data.end(), [&](const map<string, string>& entry) {
        return entry.at("ID") == id;
    });

    // If the ID was found, remove the entry from data
    if (it != data.end()) {
        data.erase(it);

        // Rewrite the updated data vector to data.csv
        ofstream file(filename);
        if (file.is_open()) {
            // Write headers
            for (size_t i = 0; i < keys.size(); ++i) {
                file << keys[i];
                if (i < keys.size() - 1) {
                    file << ",";
                }
            }
            file << endl;

            // Write data
            for (const auto& entry : data) {
                for (size_t i = 0; i < keys.size(); ++i) {
                    file << entry.at(keys[i]);
                    if (i < keys.size() - 1) {
                        file << ",";
                    }
                }
                file << endl;
            }
            file.close();
            system("cls");
            cout << "To-Do entry with ID " << id << " deleted successfully." << endl;
        } else {
            cout << "Unable to open file to rewrite data." << endl;
        }
    } else {
        cout << "No To-Do entry found with ID " << id << "." << endl;
    }
}