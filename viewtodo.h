#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <set>
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
        categories.insert(todo.at("Category"));
    }
    for (const auto& category : categories) {
        cout << category << endl;
    }
}
string selectCategory(const vector<map<string, string>>& data) {
    string findcategory;
    bool categoryFound = false;
    do {
        cout << "Enter the category: ";
        getline(cin, findcategory);
         if (findcategory.empty()) {
            cout << "Please enter a category." << endl;
            continue;
        }
        categoryFound = false;
        for (const auto& todo : data) {
            if (todo.at("Category") == findcategory) {
                categoryFound = true;
                break;
            }
        }
        if (!categoryFound) {
            cout << "This category was not found. Please try again." << endl;
        }
    } while (!categoryFound);


    return findcategory;
} 

void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys, const string& categoryToFind){          
    vector<map<string, string>> categoryUndoneData; // สร้างเวกเตอร์เพื่อเก็บงานที่ยังไม่เสร็จสิ้นในหมวดหมู่ที่กำหนด

    // เก็บงานที่ยังไม่เสร็จสิ้นในหมวดหมู่ที่ระบุ
    for (const auto& todo : data)
    {
        if (todo.at("Category") == categoryToFind && todo.at("Status") == "undone") // ตรวจสอบว่างานอยู่ในหมวดหมู่และยังไม่เสร็จสิ้น
        {
            categoryUndoneData.push_back(todo);
        }
    }

    // แสดงงานที่ยังไม่เสร็จสิ้นในหมวดหมู่ที่กำหนด
    if (categoryUndoneData.empty())
    {
        cout << "No undone tasks found for category: " << categoryToFind << endl;
    }
    else
    {
        TodoList_table(categoryUndoneData, vector<map<string, string>>(), keys);
    }
}
