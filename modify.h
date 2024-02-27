#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Function prototypes
void modifyTodo(vector<map<string, string>>& data, const vector<string>& keys);
string selectIDToModify(const vector<map<string, string>>& data);

void modifyTodo(vector<map<string, string>>& data, const vector<string>& keys) {
    string inputId = selectIDToModify(data);
    string input;
    // Find the entry with the given ID
    auto entryToUpdate = find_if(data.begin(), data.end(), [&inputId](const map<string, string>& entry) {
        return entry.at("ID") == inputId;
    });

    if (entryToUpdate != data.end()) {
        // Get user input for each field
        map<string, string> newEntry;
        std::cout << "\033[1;32mEnter ID: ";
        getline(cin, newEntry["ID"]);

        cout << "\033[1;32mEnter Todo: ";
        getline(cin, newEntry["Todo"]);

    cout << "\033[1;32mStatus is done? (y/n): ";
    do {
    getline(cin, input);
    if (input == "y" || input == "Y") {
        newEntry["Status"] = "done";
        break;
    } else if (input == "no" || input == "n" || input == "N" || input == "No") {
        newEntry["Status"] = "undone";
        break;
    } else {
        cout << "\033[1;31mInvalid input." << endl;
        cout << "\033[1;32mStatus is done? (y/n): " ;
    }
} while (true);

        cout << "\033[1;32mAdd a Category? (y/n): ";
        do{
        getline(cin, input);
        if (input == "y" || input == "Y") {
            cout << "\033[1;32mEnter Category: ";
            getline(cin, newEntry["Category"]);
            break;
        } else if (input == "no" || input == "n" || input == "N" || input == "No") {
            newEntry["Category"] = "No category";
            break;
        }else {
        cout << "\033[1;31mInvalid input." << endl;
        cout << "\033[1;32mAdd a Category? (y/n): ";
    }
        }while (true);

        cout << "\033[1;32mAdd a Due Date? (y/n): ";
        do{
        getline(cin, input);
        if (input == "y" || input == "Y" ) {
            cout << "\033[1;32mEnter Due Date (y/m/d): ";
            getline(cin, newEntry["Due Date"]);
            break;
        } else if (input == "no" || input == "n" || input == "N" || input == "No") {
            newEntry["Due Date"] = "No date";
            break;
        }else {
        cout << "\033[1;31mInvalid input." << endl;
        cout << "\033[1;32mAdd a Due Date? (y/n): ";
    }
        }while (true);

        cout << "\033[1;32mAdd Remarks? (y/n): ";
        do{
        getline(cin, input);
        if (input == "yes" || input == "y" || input == "Y" || input == "Yes") {
            cout << "\033[1;32mEnter Remarks: ";
            getline(cin, newEntry["Remarks"]);
            break;
        } else if (input == "no" || input == "n" || input == "N" || input == "No"){
            newEntry["Remarks"] = "None";
            break;
        }else {
        cout << "\033[1;31mInvalid input." << endl;
        cout << "\033[1;32mAdd Remarks? (y/n): ";
    }
        }while (true);

        cout << "\033[1;32mMark as important? (y/n): ";
        do{
        getline(cin, input);
        if (input == "yes" || input == "y" || input == "Y" || input == "Yes") {
        newEntry["!"] = "!";
        break;
        } else if (input == "no" || input == "n" || input == "N" || input == "No") {
        newEntry["!"] = " ";
        break;
    } else {
        cout << "\033[1;31mInvalid input." << endl;
        cout << "\033[1;32mMark as important? (y/n): " ;
    }
    } while (true);

        // Replace old entry with new entry
        *entryToUpdate = newEntry;

        // Write updated data to data.csv file
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

        cout << "\033[1;32mTo-do edited successfully!" << endl;
    } else {
        cout << "\033[1;31mUnable to open file for writing!" << endl;
}
    } else {
        cout << "\033[1;31mNo entry found with ID " << inputId << endl;
    }
}

string selectIDToModify(const vector<map<string, string>>& data) {
    string findIDTomodify;
    bool idFound = false;
    do {
        cout << "\033[1;32mEnter ID of the To-Do you want to modify: ";
        getline(cin, findIDTomodify);
         if (findIDTomodify.empty()) {
            cout << "\033[1;32mPlease enter an exist ID." << endl;
            continue;
        }
        idFound = false;
        for (const auto& todo : data) {
            if (todo.at("ID") == findIDTomodify) {
                idFound = true;
                break;
            }
        }
        if (!idFound) {
            cout << "\033[1;31mThis ID was not found: " << findIDTomodify << endl;
        }
    } while (!idFound);


    return findIDTomodify;
}