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
void TodoList_table(vector<map<string, string>> doneData, vector<map<string, string>> undoneData, vector<string> keys);
void findTodoDone(const vector<map<string, string>>& data, const vector<string>& keys);
void findTodoUndone(const vector<map<string, string>>& data, const vector<string>& keys);
void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys);

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

    cout << "Enter 1 to find tasks with status 'done', 2 to find tasks with status 'undone', or 3 to find tasks by category: ";
    string choice;
    getline(cin, choice);

    if (choice == "1") {
        findTodoDone(data, keys);
        findTodoByCategory(data, keys);
    }
    else if (choice == "2") {
        findTodoUndone(data, keys);
        findTodoByCategory(data, keys);
    }
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}

// Function to display Todo List table
void TodoList_table(vector<map<string, string>> doneData, vector<map<string, string>> undoneData, vector<string> keys)
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

void findTodoDone(const vector<map<string, string>>& data, const vector<string>& keys)
{
    vector<map<string, string>> doneData;

    for (const auto& todo : data)
    {
        if (todo.at("Status") == "done")
        {
            doneData.push_back(todo);
        }
    }

    TodoList_table(doneData, vector<map<string, string>>(), keys);
}

void findTodoUndone(const vector<map<string, string>>& data, const vector<string>& keys)
{
    vector<map<string, string>> undoneData;

    for (const auto& todo : data)
    {
        if (todo.at("Status") == "undone")
        {
            undoneData.push_back(todo);
        }
    }

    TodoList_table(vector<map<string, string>>(), undoneData, keys);
}

// Function to find and display tasks by category
void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys)
{
    map<string, vector<map<string, string>>> categoryData;

    // Group tasks by category
    for (const auto& todo : data)
    {
        string category = todo.at("Category");
        categoryData[category].push_back(todo);
    }

    // Print tasks for each category
    for (const auto& entry : categoryData)
    {
        cout << "Category: " << entry.first << endl;
        TodoList_table(entry.second, vector<map<string, string>>(), keys);
    }
}
