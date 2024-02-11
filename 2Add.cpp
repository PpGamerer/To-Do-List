#include<iostream>
#include<string>
using namespace std;


int main()
{
    //เพิ่มรายละเอียดเพิ่มเติม
    string input;
    cout << "Add a Remarks? y/n : ";
    getline(cin,input);
   
    for(int i = 0 ; i < 1000 ; i++)
    {
       
        if(input == "yes" || input == "y" || input == "Y" || input == "Yes")
        {
            cout << "Add a Remarks : ";
            getline(cin,input);
            break;
            newEntry.push_back(input);

        }
        else if (input == "no" || input == "n" || input == "N" || input == "No")
        {
            cout << "None";
            break;
            newEntry.push_back(input);

        }
        else 
        {
             cout << "Add a Remarks? y/n : ";
            getline(cin,input);
        }
        
    }


//เพิ่มวันที่มเดดไลน์
    string input;
    cout << "Add a Due Date? y/n : ";
    getline(cin,input);
   
    for(int j = 0 ; j < 1000 ; j++)
    {
       

        if(input == "yes" || input == "y" || input == "Y" || input == "Yes")
        {
            cout << "Add a Due Date  : ";
            getline(cin,input);
            break;
            newEntry.push_back(input);

        }
        else if (input == "no" || input == "n" || input == "N" || input == "No")
        {
            cout << "No date";
            break;
            newEntry.push_back(input);

        }
        else 
        {
            cout << "Add a Due Date? y/n : ";
            getline(cin,input);
        }
        

        
    }

}


/*std::cout << "Add a Due Date? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y"){
    std::cout << "Ender a Due Date : ";
    getline(cin, input);
    newEntry.push_back(input);
    }else if(input=="n" || input == "N"){
        input = "No date";
        newEntry.push_back(input);
    }

    std::cout << "Add a Remarks? (y/n) : ";
    getline(cin, input);
    while(input!="y" && input!="Y" && input!="n" && input!="N"){
        cout << "Please enter only 'y' for yes or 'n' for no. (y/n) : ";
        getline(cin, input);
    }
    if(input=="y" || input == "Y"){
    std::cout << "Enter Remarks: ";
    getline(cin, input);
    newEntry.push_back(input);
    }else if(input=="n" || input == "N"){
        input = "None";
        newEntry.push_back(input);




    }
    */
    