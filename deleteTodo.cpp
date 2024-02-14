#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

//prototype functions
void addTodo(const string& filename, const vector<string>& entry);
void getUserInput(vector<map<string, string>>& data, const vector<string>& keys);
void reloadData(vector<map<string, string>>& data, const vector<string>& keys);
vector<string> tokens(string text,string delimiter);
void TodoList_table(vector<map<string,string>> data, vector<string> keys);
void deleteTodo(const string& filename, vector<map<string, string>>& data, const vector<string>& keys, const string& id);



int main()
{
    map<string,string> myMap;
    vector<map<string,string>> data; //เก็บ myMap แต่ละแถวไว้ใน data
    string textline;
    ifstream read;
    read.open("data.csv");
    getline(read,textline); //บรรทัดแรก (หัวข้อประเภท)
    vector<string> keys = tokens(textline, ","); //delimiter = ","
    vector<string> row;
    while (getline(read, textline)) { //อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline, ",");  //delimiter = ","
        myMap.clear(); //เคลียร์mapก่อนpair
        for (size_t i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap.insert(pair<string, string>(keys.at(i),row[i])); //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap);
    }
    TodoList_table(data,keys);
    string idToDelete;
    cout << "Enter ID of the To-Do entry you want to delete: ";
    getline(cin, idToDelete);
    deleteTodo("data.csv", data, keys, idToDelete);


    return 0;
}

void TodoList_table(vector<map<string, string>> data,vector<string> keys) { //data เก็บ myMap ทุกแถวไว้, keys เก็บหัวข้อของทุกประเภทไว้อยู่
    int data_count = data.size(); //จำนวนแถวข้อมูลทั้งหมด(จำนวนmyMap)
    int col_count = keys.size(); //จำนวนคอลัมน์ข้อมูล(จำนวนประเภทข้อมูล)
    vector<unsigned int> col_sizes(col_count);
    for (size_t i = 0; i < col_count; i++) { //หา column size ที่มากที่สุด ของแต่ละคอลัมน์
        col_sizes[i] = keys.at(i).length(); //ความยาวของข้อมูลที่ i
        for (size_t j = 0; j < data_count; j++) {
            if (col_sizes[i] < data[j][keys.at(i)].length()) {
                col_sizes[i] = data[j][keys.at(i)].length(); //ถ้ามากกว่าข้อมูลที่ i ให้แทนค่านั้นเป็น column size
            }
        }
    }
    //ขอบตารางบน----
    for (int i = 0; i < col_count; i++) {
            std::cout << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    std::cout << endl;
    //ประเภทข้อมูล(ข้อมูลแถวแรก)
    for (int i = 0; i < col_count; i++) {
        std::cout  << setw(col_sizes[i]) << left << keys.at(i)  << "|";
    }
    std::cout << endl;

    //sort by priority
    sort(data.begin(), data.end(), [&](const auto& a, const auto& b) {
    auto Check = [&](const auto& row) {
        return row.at(keys.back()) == "!";
    };
    bool isAPriority = Check(a);
    bool isBPriority = Check(b);

    bool isANonPriority = !isAPriority; 
    bool isBNonPriority = !isBPriority;

    if (isANonPriority && isBNonPriority) {
        // ถ้าไม่มีทั้งคู่ให้เรียงอันที่เพิ่มหลังมาทีหลัง
        return find(data.begin(), data.end(), a) < find(data.begin(), data.end(), b); //หาจนเจอ a,b แล้วเอาbมาหลังa (return true)
    } else if (isAPriority && !isBPriority) {
        return true;  // a มาก่อน b
    } else if (!isAPriority && isBPriority) {
        return false; // b มาก่อน a
    } else {
        // ถ้ามีทั้งคู่ให้เรียงตามลำดับเดิม
        return a.at(keys.back()) > b.at(keys.back());
    }});

    //ขอบตารางและข้อมูลในตาราง --|--
    for (int i = 0; i < data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        std::cout << endl;
        for (int j = 0; j < col_count; j++) {
            std::cout << setw(col_sizes[j]) << left << data[i][keys.at(j)] << "|";
        }
        std::cout << endl; 
    }
    //ขอบตารางล่าง----
    for (int i = 0; i < col_count; i++) {
            std::cout << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    std::cout << endl;
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

void deleteTodo(const string& filename, vector<map<string, string>>& data, const vector<string>& keys, const string& id) {
    // Find the index of the entry with the given ID
    auto it = find_if(data.begin(), data.end(), [&](const map<string, string>& entry) {
        return entry.at("ID") == id;
    });

    // If the ID was found, remove the entry from data
    if (it != data.end()) {
        data.erase(it);

        // Rewrite the updated data vector to data.csv
        ofstream file(filename);
        if (file.is_open()) {
            // Write headers
            for (size_t i = 0; i < keys.size(); ++i) {
                file << keys[i];
                if (i < keys.size() - 1) {
                    file << ",";
                }
            }
            file << endl;

            // Write data
            for (const auto& entry : data) {
                for (size_t i = 0; i < keys.size(); ++i) {
                    file << entry.at(keys[i]);
                    if (i < keys.size() - 1) {
                        file << ",";
                    }
                }
                file << endl;
            }
            file.close();
            cout << "To-Do entry with ID " << id << " deleted successfully." << endl;
        } else {
            cout << "Unable to open file to rewrite data." << endl;
        }
    } else {
        cout << "No To-Do entry found with ID " << id << "." << endl;
    }
}