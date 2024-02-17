#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

//prototype functions
void TodoList_table(vector<map<string,string>> data, vector<string> keys);
bool hasTextInColumn7(const std::string& row);
void stablePartitionByColumn7(vector<map<string, string>>& data);

void TodoList_table(vector<map<string, string>> data,vector<string> keys) { //data เก็บ myMap ทุกแถวไว้, keys เก็บหัวข้อของทุกประเภทไว้อยู่
    size_t data_count = data.size(); //จำนวนแถวข้อมูลทั้งหมด(จำนวนmyMap)
    size_t col_count = keys.size(); //จำนวนคอลัมน์ข้อมูล(จำนวนประเภทข้อมูล)
    vector<size_t> col_sizes(col_count);
    for (size_t i = 0; static_cast<int>(i) < col_count; i++) { //หา column size ที่มากที่สุด ของแต่ละคอลัมน์
        col_sizes[i] = keys.at(i).length(); //ความยาวของข้อมูลที่ i
        for (size_t j = 0; static_cast<int>(j) < data_count; j++) {
            if (col_sizes[i] < data[j][keys.at(i)].length()) {
                col_sizes[i] = data[j][keys.at(i)].length(); //ถ้ามากกว่าข้อมูลที่ i ให้แทนค่านั้นเป็น column size
            }
        }
    }
    //ขอบตารางบน----
    for (int i = 0; i < col_count; i++) {
            cout << "\033[1;37m" << setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    cout << endl;
    stablePartitionByColumn7(data);
    //ประเภทข้อมูล(ข้อมูลแถวแรก)
    for (int i = 0; i < col_count; i++) {
        cout << "\033[1;33m" << setw(col_sizes[i]) << left << keys.at(i)  << "\033[1;37m" << "|";
    }
    cout << endl;

    //ขอบตารางและข้อมูลในตาราง --|--
    for (int i = 0; i < data_count; i++) {
        for (int j = 0; j < col_count; j++) {
            cout << "\033[1;37m" << setw(col_sizes[j]) << setfill('-') << "" << setfill(' ') << "|";
        }
        cout << endl;
        for (int j = 0; j < col_count; j++) {
            cout << "\033[1;33m" << setw(col_sizes[j]) << left << data[i][keys.at(j)] << "\033[1;37m" <<  "|";
        }
        cout << endl; 
    }
    //ขอบตารางล่าง----
    for (int i = 0; i < col_count; i++) {
            cout << "\033[1;37m" <<  setw(col_sizes[i]) << setfill('-') << "" << setfill(' ') << "-";
        } 
    cout << endl << "\033[1;32m";
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
void stablePartitionByColumn7(vector<map<string, string>>& data) {
    stable_partition(data.begin(), data.end(), [](const map<string, string>& row) {
        if (row.find("!") != row.end()) {
            return row.at("!") == "!"; // Move important entries to the front
        } else {
            return true; // Maintain the order of non-important entries
        }
    });
}