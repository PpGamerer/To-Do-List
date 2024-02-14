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
vector<string> tokens(string text, string delimiter);
void addTodo(const string& filename, const vector<string>& entry);
void getUserInput(vector<map<string, string>>& data, const vector<string>& keys);
void reloadData(vector<map<string, string>>& data, const vector<string>& keys);
void TodoList_table(vector<map<string, string>> doneData, vector<map<string, string>> undoneData, vector<string> keys);
void findTodoDone(const vector<map<string, string>>& data, const vector<string>& keys);
void findTodoUndone(const vector<map<string, string>>& data, const vector<string>& keys);
void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys, const string& category); // Added category parameter
void getUserChoiceLoop(const vector<map<string, string>>& data, const vector<string>& keys);


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

    getUserChoiceLoop(data,keys);
}

// Function to get user choice and execute actions
void getUserChoiceLoop(const vector<map<string, string>>& data, const vector<string>& keys) {
    string choice;
    do {
        cout << "Enter 1 to find tasks with status 'done'\nEnter 2 to find tasks with status 'undone'\nEnter 3 to find tasks by category\n: ";
        getline(cin, choice);

        if (choice == "1") {
            findTodoDone(data, keys);
        }
        else if (choice == "2") {
            findTodoUndone(data, keys);
        }
        else if (choice == "3") {
            cout << "Categories available:" << endl;
            set<string> categories; // Use a set to avoid duplicates
            for (const auto& todo : data) {
                categories.insert(todo.at("Category"));
            }
            for (const auto& category : categories) {
                cout << category << endl;
            }

            string category;
            bool categoryFound = false;
            do {
                cout << "Enter the category: ";
                getline(cin, category);
                categoryFound = false;
                for (const auto& todo : data) {
                    if (todo.at("Category") == category) {
                        categoryFound = true;
                        break;
                    }
                }
                if (!categoryFound) {
                    cout << "No tasks found for category: " << category << endl;
                }
            } while (!categoryFound);
            findTodoByCategory(data, keys, category); // Pass category to the function
        }
        else {
            cout << "Please enter the correct answer" << endl;
        }
    } while (choice != "1" && choice != "2" && choice != "3");
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
    sort(doneData.begin(), doneData.end(), [&](const auto& a, const auto& b) {
    auto Check = [&](const auto& row) {
        return row.at(keys.back()) == "!";
    };
    bool isAPriority = Check(a);
    bool isBPriority = Check(b);

    bool isANonPriority = !isAPriority; 
    bool isBNonPriority = !isBPriority;

    if (isANonPriority && isBNonPriority) {
        // ถ้าไม่มีทั้งคู่ให้เรียงอันที่เพิ่มหลังมาทีหลัง
        return find(doneData.begin(), doneData.end(), a) < find(doneData.begin(), doneData.end(), b); //หาจนเจอ a,b แล้วเอาbมาหลังa (return true)
    } else if (isAPriority && !isBPriority) {
        return true;  // a มาก่อน b
    } else if (!isAPriority && isBPriority) {
        return false; // b มาก่อน a
    } else {
        // ถ้ามีทั้งคู่ให้เรียงตามลำดับเดิม
        return a.at(keys.back()) > b.at(keys.back());
    }});

    sort(undoneData.begin(), undoneData.end(), [&](const auto& a, const auto& b) {
    auto Check = [&](const auto& row) {
        return row.at(keys.back()) == "!";
    };
    bool isAPriority = Check(a);
    bool isBPriority = Check(b);

    bool isANonPriority = !isAPriority; 
    bool isBNonPriority = !isBPriority;

    if (isANonPriority && isBNonPriority) {
        // ถ้าไม่มีทั้งคู่ให้เรียงอันที่เพิ่มหลังมาทีหลัง
        return find(undoneData.begin(), undoneData.end(), a) < find(undoneData.begin(), undoneData.end(), b); //หาจนเจอ a,b แล้วเอาbมาหลังa (return true)
    } else if (isAPriority && !isBPriority) {
        return true;  // a มาก่อน b
    } else if (!isAPriority && isBPriority) {
        return false; // b มาก่อน a
    } else {
        // ถ้ามีทั้งคู่ให้เรียงตามลำดับเดิม
        return a.at(keys.back()) > b.at(keys.back());
    }});

    
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
void findTodoByCategory(const vector<map<string, string>>& data, const vector<string>& keys, const string& category)
{
    vector<map<string, string>> categoryUndoneData; // สร้างเวกเตอร์เพื่อเก็บงานที่ยังไม่เสร็จสิ้นในหมวดหมู่ที่กำหนด

    // เก็บงานที่ยังไม่เสร็จสิ้นในหมวดหมู่ที่ระบุ
    for (const auto& todo : data)
    {
        if (todo.at("Category") == category && todo.at("Status") == "undone") // ตรวจสอบว่างานอยู่ในหมวดหมู่และยังไม่เสร็จสิ้น
        {
            categoryUndoneData.push_back(todo);
        }
    }

    // แสดงงานที่ยังไม่เสร็จสิ้นในหมวดหมู่ที่กำหนด
    if (categoryUndoneData.empty())
    {
        cout << "No undone tasks found for category: " << category << endl;
    }
    else
    {
        TodoList_table(categoryUndoneData, vector<map<string, string>>(), keys);
    }
}


void addTodo(const string& filename, const vector<string>& entry) {
    // Open the file in append mode
    ofstream file(filename, ios::app);
    // Write the entry to the file
    for (size_t i = 0; i < entry.size(); ++i) {
        file << entry[i];
        if (i < entry.size()-1) {
            file << ","; //เพิ่ม , ถ้าไม่ใช่ข้อมูลสุดท้าย
        }}
    file << endl;
    file.close();

    std::cout << "New entry added to To-Do List successfully." << endl;
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
    std::cout << "Ender a Due Date : ";
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

    // Add the new entry to the data.csv file
    addTodo("data.csv", newEntry);
    reloadData(data,keys);
}

void reloadData(vector<map<string, string>>& data, const vector<string>& keys){
    data.clear(); //เคลียร์ไฟล์ data.csv
    string textline;
    ifstream read;
    read.open("data.csv");
    getline(read,textline);  //บรรทัดแรก (หัวข้อประเภท)
    vector<string> row;
    while (getline(read, textline)) { // อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline, ",");  // Extract data for each row
        map<string, string> myMap;
        for (size_t i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap.insert(pair<string, string>(keys.at(i), row[i])); //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap); 
    }
    read.close();
}