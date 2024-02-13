#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void Category(){
    system("cls");
    int ans;

    cout << "Category" << endl;
    cout << "---------------------" << endl;
    cout << "1. School" << endl;
    cout << "2. Housework" << endl;
    cout << "3. No category" << endl;
    cout << "---------------------" << endl;
    cout << "What category do you want to view? : ";   
}
void ReadData(){
    ifstream read;
    read.open("data.csv");
}
void Viewalltdfromctgr(){
    int ans;
    do{ 
        Category();
        cin >> ans;
        switch(ans){
        case 1:
                system("cls");
                cout << "School" << endl;
                ReadData();
                break;
            case 2:
                system("cls");
                cout << "Housework" << endl;
                ReadData();
                break;
            case 3:
                system("cls");
                cout << "No category" << endl;
                ReadData();
                break;
            default:
                cout << "There is no this category. Please try again." << endl;
                break;
    }
    cin.ignore();
    cin.get();
    }while(ans != 3);   
}

int main(){
    Viewalltdfromctgr();
}


    

