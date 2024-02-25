#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;

// Prototype functions
void TodoList_table(vector<map<string, string>> doneData, vector<map<string, string>> undoneData, vector<string> keys);
void findTodoDone(const vector<map<string, string>>& data, const vector<string>& keys);
void findTodoUndone(const vector<map<string, string>>& data, const vector<string>& keys);
void displayAvailableCategories(const vector<map<string, string>>& data);
string selectCategory(const vector<map<string, string>>& data);
void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys, const string& category); // Added category parameter


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
        std::cout << "\033[1;37m" << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
    }
    std::cout << endl;
    for (int i = 0; i < col_count; i++) {
        std::cout << "\033[1;33m"<< setw(col_sizes[i]) << left << keys.at(i) << "\033[1;37m" << "|";
    }
    std::cout << endl;

    // Print data for "done" tasks
    for (int i = 0; i < done_data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            std::cout << "\033[1;37m" << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        std::cout << endl;
        for (int j = 0; j < col_count; j++) {
            std::cout << "\033[1;33m" << setw(col_sizes[j] ) << left << doneData[i][keys.at(j)] << "\033[1;37m" << "|";
        }
        std::cout << endl;
    }
    // Print data for "undone" tasks
    for (int i = 0; i < undone_data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            std::cout << "\033[1;37m" << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        std::cout << endl;
        for (int j = 0; j < col_count; j++) {
            std::cout << "\033[1;33m" << setw(col_sizes[j] ) << left << undoneData[i][keys.at(j)] <<"\033[1;37m" << "|";
        }
        std::cout << endl;
    }
    for (int i = 0; i < col_count; i++) {
        std::cout <<"\033[1;37m" << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
    } 
    std::cout << endl << "\033[1;32m"; 

    // ไม่ทำการเรียงลำดับข้อมูล

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

void displayAvailableCategories(const vector<map<string, string>>& data) {
    cout << "Categories available:" << endl;
    set<string> categories; // Use a set to avoid duplicates
    for (const auto& todo : data) {
        if (todo.at("Status") == "undone") { // Check if the task is undone
            categories.insert(todo.at("Category"));
        }
    }
    for (const auto& category : categories) {
        cout << " - " << category << endl;
    }
}


string selectCategory(const vector<map<string, string>>& data) {
    string findcategory;
    bool categoryFound = false;
    do {
        cout << "\033[1;32mEnter the category: ";
        getline(cin, findcategory);
        // Convert the user input to lowercase
        transform(findcategory.begin(), findcategory.end(), findcategory.begin(), ::tolower);
        if (findcategory.empty()) {
            cout << "\033[1;32mPlease enter a category." << endl;
            continue;
        }
        // Allow "no category" as a valid option
        if (findcategory == "no category") {
            categoryFound = true;
            break;
        }
        categoryFound = false;
        // Convert categories from data to lowercase for comparison
        for (const auto& todo : data) {
            string category = todo.at("Category");
            transform(category.begin(), category.end(), category.begin(), ::tolower);
            if (category == findcategory) {
                categoryFound = true;
                break;
            }
        }
        if (!categoryFound) {
            cout << "\033[1;31mThis category was not found. Please try again." << endl;
        }
    } while (!categoryFound);

    return findcategory;
}


void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys, const string& categoryToFind) {          
    vector<map<string, string>> categoryUndoneData; // Vector to store undone tasks in the specified category

    // Search for undone tasks with the specified category or "no category"
    for (const auto& todo : data) {
        // Include tasks with the specified category or "no category" that are undone
        if ((todo.at("Category") == categoryToFind || categoryToFind == "no category") && todo.at("Status") == "undone") {
            categoryUndoneData.push_back(todo);
        }
    }

    // Display the tasks found
    if (categoryUndoneData.empty()) {
        cout << "\033[1;31mNo undone tasks found for category: " << categoryToFind << endl;
    } else {
        TodoList_table(categoryUndoneData, vector<map<string, string>>(), keys);
    }
<<<<<<< HEAD
}
=======
}



>>>>>>> 77749a82453333e6a0c3fa2a293f34d95803e2ef
