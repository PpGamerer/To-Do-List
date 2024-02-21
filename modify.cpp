#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Function prototypes
vector<string> tokens(string text, string delimiter);
void modifyTodo(vector<map<string, string>>& data, const vector<string>& keys);
void getUserInput(vector<map<string, string>>& data, const vector<string>& keys); // เพิ่มฟังก์ชั่น getUserInput

int main() {
    // Sample data
    vector<map<string, string>> data;
    vector<string> keys = {"ID", "Todo", "Status", "Category", "Due Date", "Remarks", "Important"};

    // Display the updated to-do list
    for (const auto& entry : data) {
        for (const auto& pair : entry) {
            cout << pair.first << ": " << pair.second << endl;
        }
        cout << endl;
    }

    // Edit an existing to-do entry
    modifyTodo(data, keys);

    return 0;
}

// Tokenize a string
vector<string> tokens(string text, string delimiter) {
    vector<string> key;
    size_t found;
    string token;
    while ((found = text.find(delimiter)) != string::npos) {
        token = text.substr(0, found);
        key.push_back(token);
        text.erase(0, found + delimiter.length());
    }
    key.push_back(text);
    return key;
}

void getUserInput(vector<map<string, string>>& data, const vector<string>& keys) {  
    vector<string> newEntry;

    // Get user input for each field
    string input;
    std::cout << "Enter ID: ";
    getline(cin, input);
    newEntry.push_back(input);

    std::cout << "Enter Todo: ";
    getline(cin, input);
    newEntry.push_back(input);

    input = "undone"; //status default is "undone"
    newEntry.push_back(input);

    std::cout << "Add a Category? (y/n) : ";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
    std::cout << "Enter Category: ";
    getline(cin, input);
    newEntry.push_back(input);
    break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = "No category";
        newEntry.push_back(input);
        break;
    }
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }

    std::cout << "Add a Due Date? (y/n) : ";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
    std::cout << "Ender a Due Date (y/m/d) : ";
    getline(cin, input);
    newEntry.push_back(input);
    break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = "No date";
        newEntry.push_back(input);
        break;
    }
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }

    std::cout << "Add a Remarks? (y/n) : ";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
    std::cout << "Enter Remarks: ";
    getline(cin, input);
    newEntry.push_back(input);
    break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = "None";
        newEntry.push_back(input);
        break;
    }
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    
    std::cout << "Mark as important? (y/n) : ";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
        input = "!";
        newEntry.push_back(input);
        break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = " ";
        newEntry.push_back(input);
        break;
    }
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }

}
void modifyTodo(vector<map<string, string>>& data, const vector<string>& keys) {
    string idToEdit;
    cout << "Enter the ID you want to modify: ";
    getline(cin, idToEdit);

    // Find the index of the entry with the specified ID
    auto it = find_if(data.begin(), data.end(), [&](const map<string, string>& entry) {
        return entry.at(keys[0]) == idToEdit; // Assuming ID is the first key
    });

    if (it != data.end()) {
        cout << "Editing entry with ID: " << idToEdit << endl;
        // Remove the existing entry
        data.erase(it);

        // Call getUserInput to get new data
        getUserInput(data, keys);

        // Write updated data to data.csv file
        ofstream outfile("data.csv");
        if (outfile.is_open()) {
            for (const auto& entry : data) {
                for (const auto& key : keys) {
                    // Use const_iterator to prevent modifications
                    auto it = entry.find(key);
                    if (it != entry.end()) {
                        outfile << it->second << ",";
                    } else {
                        outfile << ",";
                    }
                }
                outfile << endl;
            }
            outfile.close();
            cout << "Data edited successfully and saved to data.csv!" << endl;
        } else {
            cout << "Unable to open file for writing!" << endl;
        }
    } else {
        cout << "No entry found with ID: " << idToEdit << endl;
    }
}
