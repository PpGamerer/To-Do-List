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
void addTodo(const string& filename, const vector<string>& entry);
void getUserInput(vector<map<string, string>>& data, const vector<string>& keys);
void reloadData(vector<map<string, string>>& data, const vector<string>& keys);


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

    std::cout << "\033[1;32mNew entry added to To-Do List successfully." << endl;
}

void getUserInput(vector<map<string, string>>& data, const vector<string>& keys) {  
    vector<string> newEntry;

    // Get user input for each field
    string input;
    std::cout << "\033[1;32mEnter ID: ";
    cout << "\033[1;37m";
    getline(cin, input);
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
        input = "\033[1;31mNo category";
        newEntry.push_back(input);
        break;
    }
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n) : ";
        cout << "\033[1;37m";
        getline(cin, input);
    }

    std::cout << "\033[1;32mAdd a Due Date? (y/n) : ";
    cout << "\033[1;37m";
    getline(cin, input);
    while(true){
    if(input == "yes" || input == "y" || input == "Y" || input == "Yes"){
    std::cout << "\033[1;32mEnder a Due Date : ";
    cout << "\033[1;37m";
    getline(cin, input);
    newEntry.push_back(input);
    break;
    }else if(input == "no" || input == "n" || input == "N" || input == "No"){
        input = "\033[1;31mNo date";
        newEntry.push_back(input);
        break;
    }
        cout << "\033[1;31mPlease enter only 'y' for yes or 'n' for no. (y/n) : ";
        cout << "\033[1;37m";
        getline(cin, input);
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
        input = "\033[1;31mNone";
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
        input = "\033[1;31m!";
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
    addTodo("data.csv", newEntry);
    reloadData(data,keys);
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