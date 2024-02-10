#include <iostream>
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
    Addcategory();
}