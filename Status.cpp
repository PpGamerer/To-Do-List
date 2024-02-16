#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Prototype functions
vector<string> tokens(string text, string delimiter);
void Status_table(vector<map<string, string>> doneData, vector<map<string, string>> undoneData, vector<string> keys);
void findTodoDone(const vector<map<string, string>>& data, const vector<string>& keys);
void findTodoUndone(const vector<map<string, string>>& data, const vector<string>& keys);
void getUserChoiceLoop(const vector<map<string, string>>& data, const vector<string>& keys);
bool hasTextInColumn7(const std::string& row);

int main()
{
    map<string, string> myMap;
    vector<map<string, string>> data; // Store each row in myMap
    string textline;
    ifstream read;

    read.open("data.csv");
    getline(read, textline); // First line (column headers)
    vector<string> keys = tokens(textline, ",");
    vector<string> row;
    while (getline(read, textline)) {
        row = tokens(textline, ",");
        myMap.clear();
        for (int i = 0; i < keys.size(); i++) {
            myMap.insert(pair<string, string>(keys.at(i), row[i]));
        }
        data.push_back(myMap);
    }
    stable_partition(data.begin(), data.end(), [](const map<string, string>& row) {
    return hasTextInColumn7(row.at("!"));
});
    getUserChoiceLoop(data,keys);
}

void getUserChoiceLoop(const vector<map<string, string>>& data, const vector<string>& keys){
    while (true) {
        cout << "Enter 1 to find tasks with status 'done' \nEnter 2 to find tasks with status 'undone': ";
        string statusChoice;
        getline(cin, statusChoice);

        if (statusChoice == "1") {
            findTodoDone(data, keys);
            break;
        } else if (statusChoice == "2") {
            findTodoUndone(data, keys);
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}


// Function to display Todo List table
void Status_table(vector<map<string, string>> doneData, vector<map<string, string>> undoneData, vector<string> keys)
{
    int done_data_count = doneData.size();
    int undone_data_count = undoneData.size();
    int col_count = keys.size();
    vector<int> col_sizes(col_count);
    for (int i = 0; i < col_count; i++)
    {
        col_sizes[i] = keys.at(i).length();
        for (int j = 0; j < done_data_count; j++)
        {
            if (col_sizes[i] < doneData[j][keys.at(i)].length())
            {
                col_sizes[i] = doneData[j][keys.at(i)].length();
            }
        }
        for (int j = 0; j < undone_data_count; j++)
        {
            if (col_sizes[i] < undoneData[j][keys.at(i)].length())
            {
                col_sizes[i] = undoneData[j][keys.at(i)].length();
            }
        }
    }
    // Print headers for both sets of data
    for (int i = 0; i < col_count; i++) {
        std::cout << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
    }
    std::cout << endl;
    for (int i = 0; i < col_count; i++) {
        std::cout << setw(col_sizes[i]) << left << keys.at(i) << "|";
    }
    std::cout << endl;
    // Print data for "done" tasks
    for (int i = 0; i < done_data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        std::cout << endl;
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j] ) << left << doneData[i][keys.at(j)] << "|";
        }
        std::cout << endl;
    }
    // Print data for "undone" tasks
    for (int i = 0; i < undone_data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        std::cout << endl;
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j] ) << left << undoneData[i][keys.at(j)] << "|";
        }
        std::cout << endl;

    }
    for (int i = 0; i < col_count; i++) {
            std::cout << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    std::cout << endl;
}

// Function to tokenize a string
vector<string> tokens(string text, string delimiter)
{
    vector<string> key;
    size_t found;
    string token;
    while ((found = text.find(delimiter)) != string::npos)
    {
        token = text.substr(0, found);
        key.push_back(token);
        text.erase(0, found + delimiter.length());
    }
    key.push_back(text);
    return key;
}

// Function to find and display tasks with status "done"
void findTodoDone(const vector<map<string, string>>& data, const vector<string>& keys)
{
    vector<map<string, string>> doneData;

    for (const auto& todo : data)
    {
        if (todo.at("Status") == "done") // Change to check "done"
        {
            doneData.push_back(todo);
        }
    }

    Status_table(doneData, vector<map<string, string>>(), keys); // Send only the vector of "done" data
}

// Function to find and display tasks with status "undone"
void findTodoUndone(const vector<map<string, string>>& data, const vector<string>& keys)
{
    vector<map<string, string>> undoneData;

    for (const auto& todo : data)
    {
        if (todo.at("Status") == "undone") // Change to check "undone"
        {
            undoneData.push_back(todo);
        }
    }

    Status_table(vector<map<string, string>>(), undoneData, keys); // Send only the vector of "undone" data
}

bool hasTextInColumn7(const string& row) {
    istringstream iss(row);
    string column7;
    for (int i = 0; i < 7; ++i) {
        getline(iss, column7, ',');
    }
    return !column7.empty();
}