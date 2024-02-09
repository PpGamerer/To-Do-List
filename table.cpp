#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

void TodoList_table(vector<map<string, string>> data, vector<string> keys) {
    int data_size = data.size();
    int column_count = keys.size();
    int* col_sizes = new int[column_count];
    for (int i = 0; i < column_count; i++) {
        col_sizes[i] = keys.at(i).length();
        for (int j = 0; j < data_size; j++) {
            if (col_sizes[i] < data[j][keys.at(i)].length()) {
                col_sizes[i] = data[j][keys.at(i)].length();
            }
        }
    }

    for (int i = 0; i < column_count; i++) {
        cout << setw(col_sizes[i]) << left << keys.at(i) << setw(1) << "|";
    }
    cout << endl;

    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < column_count; j++) {
            cout << setw(col_sizes[j]) << setfill('-') << "" << setw(1) << setfill(' ') << "|";
        }
        cout << endl;
        for (int j = 0; j < column_count; j++) {
            cout << setw(col_sizes[j]) <<left << data[i][keys.at(j)] << setw(1) << "|";
        }
        cout << endl;
    }

}

//["ID", "All To Dos", "Status", "Category", "Due Date", "Remarks"]
vector<string> tokens(string s, string delimiter) {
    vector<string> v;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        v.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
    return v;
}

int main()
{
    map<string, string> myMap;

    vector<map<string, string>> data;

    string text;
    ifstream read;
    read.open("data.csv");

    getline(read, text);
    vector<string> keys = tokens(text, ",");
    vector<string> row;
    while (!read.eof()) {
        getline(read, text);
        row = tokens(text, ",");
        myMap.clear();
        for (int i = 0; i < keys.size(); i++) {
            myMap.insert(pair<string, string>(keys.at(i), row[i]));
        }
        data.push_back(myMap);
    }

    TodoList_table(data, keys);
}