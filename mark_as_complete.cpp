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
void updateStatus(vector<map<string, string>>& data, const string& id, const vector<string>& keys);

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
    cout << "Enter 1 to find tasks with status 'done' \nEnter 2 to find tasks with status 'undone' \nEnter 3 to update status 'done'\n";
    string statusChoice;
    getline(cin, statusChoice);

    // Determine which function to call based on user input
    if (statusChoice == "1") {
        findTodoDone(data, keys);
    }
    else if (statusChoice == "2") {
        findTodoUndone(data, keys);
    } 
    else if (statusChoice == "3") {
        findTodoUndone(data, keys); // แสดงตารางข้อมูล "undone"
        cout << "Enter the ID of the task you want to mark as done/undone: ";
        string taskId;
        getline(cin, taskId);
        updateStatus(data, taskId, keys); // ทำการอัปเดตสถานะ
    // ไม่ต้องแสดงตารางอีกครั้ง เนื่องจากตาราง "undone" จะถูกแสดงใหม่ในฟังก์ชัน updateStatus
        if (statusChoice == "1") {
            findTodoDone(data, keys);
        } else if (statusChoice == "2") {
            findTodoUndone(data, keys);
        }
    } 
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
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

// Function to update the status of a task
void updateStatus(vector<map<string, string>>& data, const string& id, const vector<string>& keys) {
    for (auto& todo : data) {
        if (todo["ID"] == id) {
            if (todo["Status"] == "undone") {
                todo["Status"] = "done";
                cout << "Task with ID " << id << " is marked as done." << endl;
                findTodoDone(data,keys);
            } else {
                todo["Status"] = "undone";
                cout << "Task with ID " << id << " is marked as undone." << endl;
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
                cout << "Unable to open file." << endl;
            }
            return;
        }
    }
    cout << "Task with ID " << id << " not found." << endl;
} 
