#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

void Addcategory(){
    string ans,x[5],name;
    cout << "Add a category? y/n"<< endl;
    cin >> ans;
    if(ans == "y"){
        cout << "1.Work"<< endl;
        cout << "2.School"<< endl;
        cout << "3.Personal"<< endl;
        cout << "4.Etc"<< endl;
        cin >> ans;
        if(ans == "1")  x[5] = "Work";
        else if(ans == "2") x[5] = "School";
        else if(ans == "3") x[5] = "Personal";
        else{ 
            cout << "Add a category name " ;
            cin >> name ;
            x[5] = name ;
        }
    }

}
int main(){
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