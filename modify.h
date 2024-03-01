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
        while(newEntry.empty()){
            cout << "\033[1;32mPlease enter a ID." << endl;
            std::cout << "\033[1;32mEnter ID: ";
            cout << "\033[1;37m";
            getline(cin, newEntry["ID"]);
        }
        
    while (isDuplicateID(data, newEntry["ID"])) {
        cout << "\033[1;31mID already exists. Please enter a new ID.\n";
        cout << "\033[1;32mEnter ID: ";
        cout << "\033[1;37m";
        getline(cin, newEntry["ID"]);
    }
        cout << "\033[1;32mEnter Todo: ";
        cout << "\033[1;37m";
        getline(cin, newEntry["Todo"]);

    cout << "\033[1;32mStatus is done? (y/n): ";
    do {
    cout << "\033[1;37m";
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
        cout << "\033[1;37m";
        getline(cin, input);
        if (input == "y" || input == "Y") {
            cout << "\033[1;32mEnter Category: ";
            cout << "\033[1;37m";
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
        cout << "\033[1;37m";
        getline(cin, input);
        while (true) {
        if (input == "yes" || input == "y" || input == "Y" || input == "Yes") {
            // Ask whether to use today's date
            cout << "\033[1;32mUse today's date? (y/n): ";
            cout << "\033[1;37m";
            getline(cin, input);
            while(true){
                if(input == "yes" || input == "y" || input == "Y" || input == "Yes")
                {
                    /*std::cout << "\033[1;32mEnter Category: ";
                    cout << "\033[1;37m";
                    getline(cin, input);
                    newEntry.push_back(input);*/
                    break;
                }
                else if(input == "no" || input == "n" || input == "N" || input == "No")
                {
                    /*input = "No category";
                    newEntry.push_back(input);*/
                    break;
                }
                    cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n) : ";
                    cout << "\033[1;37m";
                    getline(cin, input);
            }

            while (true) {
                if (input == "yes" || input == "y" || input == "Y" || input == "Yes") {
                    // Get today's date
                    time_t now = time(0);
                    tm* ltm = localtime(&now);
                    string today = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);

                    newEntry["Due Date"] = today;
                    break;
                } else if (input == "no" || input == "n" || input == "N" || input == "No") {
                    while (true) 
                    {
                        // Get user input for date
                        cout << "\033[1;32mEnter the due date (dd/mm/yyyy): ";
                        cout << "\033[1;37m";
                        getline(cin, input);
                        // Validate user input for date format
                        vector<string> dateParts = tokens(input, "/");
                        if (dateParts.size() == 3) {
                            int day = stoi(dateParts[0]);   
                            int month = stoi(dateParts[1]);
                            int year = stoi(dateParts[2]);
                            if (year >= 1900 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                                newEntry["Due Date"] = input;
                                break;
                        }
                    }
                    cout << "\033[1;31mInvalid date format. Please enter date in dd/mm/yyyy format " << endl;
                    } 
                    break; 

                }
                cout << "\033[1;37m";
                getline(cin, newEntry["Due Date"]);
            } break;
        } else if (input == "no" || input == "n" || input == "N" || input == "No") {
            input = "No date";
            newEntry["Due Date"] = input;
            break;
        }
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n): ";
        cout << "\033[1;37m";
        getline(cin, newEntry["Due Date"]);
    }


        cout << "\033[1;32mAdd Remarks? (y/n): ";
        do{
        cout << "\033[1;37m";
        getline(cin, input);
        if (input == "yes" || input == "y" || input == "Y" || input == "Yes") {
            cout << "\033[1;32mEnter Remarks: ";
            cout << "\033[1;37m";
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
        cout << "\033[1;37m";
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
        cout << "\033[1;37m";
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