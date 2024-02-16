#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
vector<string> tokens(string text,string delimiter);
void TodoList_table(vector<map<string,string>> data, vector<string> keys);
bool hasTextInColumn7(const std::string& row);


int main() {
    ifstream inputFile("C:\\Users\\Asus\\Documents\\To-Do-List-1\\data.csv");
    ofstream outputFile("C:\\Users\\Asus\\Documents\\To-Do-List-1\\keep.csv");
    string textline;
    vector<string> rows;

    // อ่านข้อมูลและเก็บไว้ใน vector
    while (getline(inputFile, textline)) {
        rows.push_back(textline);
    }

    // เรียงลำดับแถวตามเงื่อนไขที่กำหนด
    stable_partition(rows.begin(), rows.end(), hasTextInColumn7);

    // เขียนข้อมูลที่ถูกเรียงลงไฟล์ keep.csv
    for (const auto& row : rows) {
        outputFile << row << "\n";
    }

    cout << "comple" << endl;

    //inputFile.close();
    outputFile.close();
    return 0;
    //แสดงตาราง
    map<string,string> myMap;
    vector<map<string,string>> data; //เก็บ myMap แต่ละแถวไว้ใน data
    string textline2;
    ifstream read;
    read.open("C:\\Users\\Asus\\Documents\\To-Do-List-1\\keep.csv");
    getline(read,textline2); //บรรทัดแรก (หัวข้อประเภท)
    vector<string> keys = tokens(textline2, ","); //delimiter = ","
    vector<string> row;
    while (getline(read, textline2)) { //อ่านทีละแถวจนหมดไฟล์
        row = tokens(textline2, ",");  //delimiter = ","
        myMap.clear(); //เคลียร์mapก่อนpair
        for (size_t i = 0; i < keys.size(); i++) { //ทำจนครบทุกคอลัมน์
            myMap.insert(pair<string, string>(keys.at(i),row[i])); //ใส่ค่า row[i] ลงคู่กับ keys.at(i) ตามคอลัมน์
        }
        data.push_back(myMap);
    }
    TodoList_table(data,keys);
}

void addic(){
    vector<string> newEntry;
    string input;
    std::cout << "Add a Category? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N" && input!="YES" && input!="Yes" && input!="yes" && input!="NO" && input!="No" && input!="no"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y" || input == "YES" || input == "Yes" || input == "yes"){
    std::cout << "Enter Category: ";
    getline(cin, input);
    newEntry.push_back(input);
    }else if(input=="n" || input == "N" || input == "NO" || input == "No" || input == "no"){
        input = "No category";
        newEntry.push_back(input);
    }

    std::cout << "Mark as important? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N" && input!="YES" && input!="Yes" && input!="yes" && input!="NO" && input!="No" && input!="no"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y" || input == "YES" || input == "Yes" || input == "yes"){
        input = "!";
        newEntry.push_back(input);
    }else if(input=="n" || input == "N" || input == "NO" || input == "No" || input == "no"){
        input = " ";
        newEntry.push_back(input);
    }
}
// ฟังก์ชันตรวจสอบว่าในคอลัมน์ที่ 7 มีข้อความหรือไม่
bool hasTextInColumn7(const string& row) {
    istringstream iss(row);
    string column7;
    for (int i = 0; i < 7; ++i) {
        getline(iss, column7, ',');
    }
    return !column7.empty();
}

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


