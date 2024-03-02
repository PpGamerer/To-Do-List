#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

//prototype functions
vector<string> tokens(string text,string delimiter);
void addTodo(const string& filename, const vector<string>& entry,vector<map<string, string>>& data,const vector<string>& keys);
void getUserInput(vector<map<string, string>>& data, const vector<string>& keys);
bool isDuplicateID(const vector<map<string, string>>& data, const string& id);

void addTodo(const string& filename, const vector<string>& entry,vector<map<string, string>>& data,const vector<string>& keys) {
    ofstream file(filename, ios::app); //append
    // Write the entry to the file
    for (size_t i = 0; i < entry.size(); ++i) {
        file << entry[i];
        if (i < entry.size()-1)
            file << ","; //เพิ่ม , ถ้าไม่ใช่ข้อมูลสุดท้าย
        }
    file << endl;
    file.close();
    
    map<string, string> newMapEntry;
    for (size_t i = 0; i < keys.size(); ++i) {
        newMapEntry[keys[i]] = entry[i];
    }
    data.push_back(newMapEntry);
    std::cout << "\033[1;32mNew entry added to To-Do List successfully." << endl;
}

bool isDuplicateID(const vector<map<string, string>>& data, const string& id){ 
    for (const auto& entry : data) 
    {
        if (entry.count("ID") && entry.at("ID") == id) 
        {
            return true; // พบ ID ที่ซ้ำกัน
        }
    }
    return false; // ไม่พบ ID ที่ซ้ำกัน
   }

void getUserInput(vector<map<string, string>>& data, const vector<string>& keys) {  
    vector<string> newEntry;

    // Get user input for each field
    string input;
    std::cout << "\033[1;32mEnter ID: ";
    cout << "\033[1;37m";
    getline(cin, input);
    while(input.empty()){
            cout << "\033[1;32mPlease enter a ID." << endl;
            std::cout << "\033[1;32mEnter ID: ";
            cout << "\033[1;37m";
            getline(cin, input);
        }
        
    while (isDuplicateID(data, input)) {
        cout << "\033[1;31mID already exists. Please enter a new ID.\n";
        cout << "\033[1;32mEnter ID: ";
        cout << "\033[1;37m";
        getline(cin, input);
    }
    newEntry.push_back(input);

    std::cout << "\033[1;32mEnter Todo: ";
    cout << "\033[1;37m";
    getline(cin, input);
    newEntry.push_back(input);

    input = "undone"; //status default is "undone"
    newEntry.push_back(input);

    std::cout << "\033[1;32mAdd a Category? (y/n) : ";
    cout << "\033[1;37m";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
    std::cout << "\033[1;32mEnter Category: ";
    cout << "\033[1;37m";
    getline(cin, input);
    newEntry.push_back(input);
    break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = "No category";
        newEntry.push_back(input);
        break;
    }
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n) : ";
        cout << "\033[1;37m";
        getline(cin, input);
    }

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

                    newEntry.push_back(today);
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
                                newEntry.push_back(input);
                                break;
                        }
                    }
                    cout << "\033[1;31mInvalid date format. Please enter date in dd/mm/yyyy format " << endl;
                    } 
                    break; 

                }
                cout << "\033[1;37m";
                getline(cin, input);
            }
            break;
        } else if (input == "no" || input == "n" || input == "N" || input == "No") {
            input = "No date";
            newEntry.push_back(input);
            break;
        }
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n): ";
        cout << "\033[1;37m";
        getline(cin, input);
    }

    // Add the new entry to the data vector
    map<string, string> entryMap;
    for (size_t i = 0; i < keys.size(); ++i) {
        if (keys[i] == "Due Date") {
            entryMap[keys[i]] = newEntry.empty() ? "No date" : newEntry[0];
        } else {
            // For other fields, you can prompt the user or use existing methods
            // For example, you might have other fields like "Title", "Description", etc.
            // You can prompt the user similarly as for "Due Date" and store the input.
        }
    }
    
    std::cout << "\033[1;32mAdd a Remarks? (y/n) : ";
    cout << "\033[1;37m";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
    std::cout << "\033[1;32mEnter Remarks: ";
    cout << "\033[1;37m";
    getline(cin, input);
    newEntry.push_back(input);
    break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = "None";
        newEntry.push_back(input);
        break;
    }
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n) : ";
        cout << "\033[1;37m";
        getline(cin, input);
    }
    
    std::cout << "\033[1;32mMark as important? (y/n) : ";
    cout << "\033[1;37m";
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
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n) : ";
        cout << "\033[1;37m";
        getline(cin, input);
    }

    // Add the new entry to the data.csv file
    addTodo("data.csv", newEntry, data, keys);
}

//["ID", "All To Dos", "Status", "Category", "Due Date", "Remarks", "!"]
vector<string> tokens(string text,string delimiter) { //แยกข้อมูลตามตัวคั่น (delimiter)
    vector<string> key;
    size_t found;
    string token;
    while ((found = text.find(delimiter)) != string::npos) { //หาจนเจอ delimiter(",")
        token = text.substr(0,found); //ดึงtextตำแหน่ง0ถึงตำแหน่งที่พบ","
        key.push_back(token); //นำข้อมูลที่ดึงมาใส่ไปใน key
        text.erase(0,found + delimiter.length()); //ลบข้อมูลกับ,ที่เจอ
    }
    key.push_back(text); //ข้อมูลสุดท้าย
    return key;
}